#include <bits/stdc++.h>
using namespace std;

long long shortestPath(const pair<int, int>& query,const vector<vector<pair<int, uint32_t>>>& adj, vector<long long>& bestDist){
    int source=query.first;
    int target=query.second;

    if (source==target) return 0;
    int n=adj.size();
    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>>pq;

    pq.emplace(0, source);
    bestDist[source]=0;
    
    while(!pq.empty()){
        auto state=pq.top();
        pq.pop();

        int u=state.second;
        long long currWt=state.first;

        if (currWt>bestDist[u]) continue;

        if (u==target) return currWt;

        for (const auto &[v, wt]: adj[u]){
            long long nextWt=currWt+wt;
            if (nextWt>=bestDist[v]) continue;

            bestDist[v]=nextWt;

            pq.emplace(bestDist[v], v);
        }
    }

    return -1;

}

int main() {
    auto start=chrono::high_resolution_clock::now();
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // 1. Read input
    ifstream graph("/data/graph.txt");
    ifstream queries("/data/queries.txt");
    ofstream output("/out/distances.txt");

    if (!graph.is_open() || !queries.is_open() || !output.is_open()){
        cerr<<"File opening failed!\n";
        return 1;
    }

    //graph
    int n;
    int m;

    graph>>n>>m;
    graph.ignore();

    vector<vector<pair<int, uint32_t>>>adj(n);
    vector<int>inDegree(n,0);

    for (int i=0;i<m;i++){
        int u;
        int v;
        uint32_t w;

        graph>>u>>v>>w;
        adj[u].push_back({v,w});
        inDegree[v]++;
    }

    //queries
    vector<pair<int, int>>graphQueries;
    graphQueries.reserve(2000);

    int u;
    int v;

    while (queries>>u>>v){
        graphQueries.push_back({u, v});
    }

    int q=graphQueries.size();

    // 2. Process queries
    vector<long long>distances(q);

    vector<long long>bestDist(n,LLONG_MAX);

    
    for (int i=0;i<q;i++){
        if (graphQueries[i].first==graphQueries[i].second){
            distances[i]=0;
            continue;
        }
        if (inDegree[graphQueries[i].second]==0 || adj[graphQueries[i].first].size()==0) {
            distances[i]=-1;
            continue;
        }
        bestDist.assign(n, LLONG_MAX);
        distances[i]=shortestPath(graphQueries[i], adj, bestDist);
    }
    
    // 3. Write output
    for (int i=0;i<q;i++){
        output<<distances[i]<<"\n";
    }

    return 0;
}