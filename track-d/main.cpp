#include <bits/stdc++.h>
#include <thread>
using namespace std;
long long shortestPath(const pair<int, int>& query,const vector<int>& offset, const vector<int>& edgesNeigh, const vector<uint32_t>& edgesWt,vector<long long>& bestDist, vector<uint16_t>& seenBy, const int& queryId, priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>>& pq){
    int source=query.first;
    int target=query.second;
    seenBy[source]=queryId;
    bestDist[source]=0;
    pq.emplace(0, source);
    while(!pq.empty()){
        auto state=pq.top();
        pq.pop();
        int u=state.second;
        long long currWt=state.first;
        if (currWt>bestDist[u]) continue;
        if (u==target) return currWt;
        for (int j=offset[u];j<offset[u+1];++j){
            int neigh=edgesNeigh[j];
            uint32_t wt=edgesWt[j];     
            long long nextWt=currWt+wt;
            if (seenBy[neigh]!=queryId){
                seenBy[neigh]=queryId;
                bestDist[neigh]=LLONG_MAX;
            }
            if (nextWt>=bestDist[neigh]) continue;
            bestDist[neigh]=nextWt;
            pq.emplace(bestDist[neigh], neigh);
        }
    }
    return -1;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    ifstream graph("/data/graph.txt");
    ifstream queries("/data/queries.txt");
    ofstream output("/out/distances.txt");
    int n; int m;
    graph>>n>>m;
    graph.ignore();
    vector<bool>inDegree(n,false);
    vector<int>outDegree(n,0);
    vector<tuple<int, int, uint32_t>>edges;
    edges.reserve(m);
    for (int i=0;i<m;++i){
        int u; int v; uint32_t w;
        graph>>u>>v>>w;
        if (u==v) continue;
        outDegree[u]++;
        if (!inDegree[v]) inDegree[v]=true;
        edges.emplace_back(u,v,w);
    }
    m=edges.size();
    vector<int>offset(n+1,0);
    for (int i=1;i<=n;++i) offset[i]=offset[i-1]+outDegree[i-1];
    vector<int>edgesNeigh(m);
    vector<uint32_t>edgesWt(m);
    vector<int>cursor=offset;
    for (int i=0;i<m;++i){
        int u=get<0>(edges[i]);
        edgesNeigh[cursor[u]]=get<1>(edges[i]);
        edgesWt[cursor[u]]=get<2>(edges[i]);
        cursor[u]++;
    }
    vector<tuple<int, int, uint32_t>>().swap(edges);
    vector<int>().swap(cursor);
    vector<pair<int, int>>graphQueries(2000);
    int u; int v; int cnt=0;
    while (queries>>u>>v){
        graphQueries[cnt]={u, v};
        cnt++;
    }
    queries.close();
    int q=graphQueries.size();
    vector<long long>distances(q);
    atomic<int> nextQuery{0};
    auto worker=[&](){
        vector<long long>bestDist(n,LLONG_MAX);   
        vector<uint16_t> seenBy(n, UINT16_MAX); 
        priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>>pq;
        while(true){
            int i=nextQuery.fetch_add(1, memory_order_relaxed);
            if (i>=q) break;
            if (graphQueries[i].first==graphQueries[i].second){
                distances[i]=0;
                continue;
            }
            if (outDegree[graphQueries[i].first]==0 || inDegree[graphQueries[i].second]==false){
                distances[i]=-1;
                continue;
            }
            pq=priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>>();
            distances[i]=shortestPath(graphQueries[i], offset, edgesNeigh, edgesWt, bestDist, seenBy, i, pq);
        }
    };
    vector<thread> workers;
    int threadCount=4;
    for (int i=0;i<threadCount;++i) workers.emplace_back(worker);
    for (auto& t: workers) t.join();
    for (int i=0;i<q;++i) output<<distances[i]<<"\n";
    return 0;
}