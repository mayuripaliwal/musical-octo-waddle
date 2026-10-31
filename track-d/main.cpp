#include <bits/stdc++.h>
using namespace std;
priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>>pq;
long long shortestPath(const pair<int, int>& query,const vector<int>& offset, const vector<pair<int, uint32_t>>& edges, vector<long long>& bestDist, vector<int>& seenBy, const int& queryId){
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
        for (int j=offset[u];j<offset[u+1];j++){
            int neigh=edges[j].first;
            uint32_t wt=edges[j].second;     
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
    if (!graph.is_open() || !queries.is_open() || !output.is_open()){
        cerr<<"File opening failed!\n";
        return 1;
    }
    int n;
    int m;
    graph>>n>>m;
    graph.ignore();
    vector<int>inDegree(n,0);
    vector<int>outDegree(n,0);
    for (int i=0;i<m;i++){
        int u; int v; uint32_t w;
        graph>>u>>v>>w;
        outDegree[u]++;
        inDegree[v]++;
    }
    vector<int>offset(n+1,0);
    for (int i=1;i<=n;i++) offset[i]=offset[i-1]+outDegree[i-1];
    vector<pair<int, uint32_t>>edges(m);
    vector<int>cursor=offset;
    graph.clear();
    graph.seekg(0);
    graph>>n>>m;
    for (int i=0;i<m;i++){
        int u, v;uint32_t w;
        graph>>u>>v>>w;
        edges[cursor[u]]={v,w};
        cursor[u]++;
    }
    vector<pair<int, int>>graphQueries;
    graphQueries.reserve(2000);
    int u; int v;
    while (queries>>u>>v){
        graphQueries.push_back({u, v});
    }
    int q=graphQueries.size();
    vector<long long>distances(q);
    vector<long long>bestDist(n,LLONG_MAX);   
    vector<int> seenBy(n, -1); 
    for (int i=0;i<q;i++){
        if (graphQueries[i].first==graphQueries[i].second){
            distances[i]=0;
            continue;
        }
        if (outDegree[graphQueries[i].first]==0 || inDegree[graphQueries[i].second]==0){
            distances[i]=-1;
            continue;
        }
        pq=priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>>();
        distances[i]=shortestPath(graphQueries[i], offset, edges, bestDist, seenBy, i);
    }
    // 3. Write output
    for (int i=0;i<q;i++) output<<distances[i]<<"\n";
    return 0;
}