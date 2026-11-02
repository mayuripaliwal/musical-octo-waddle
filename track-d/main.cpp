#include <bits/stdc++.h>
#include <thread>
using namespace std;
class FastInput{
private:
    static constexpr size_t BUFFER_SIZE = 1<<20;
    FILE* file;
    char buffer[BUFFER_SIZE];
    size_t pos=0; size_t len=0;
    int readChar(){
        if(pos==len){
            len=fread(buffer, 1, BUFFER_SIZE, file);
            pos=0;
            if (len==0) return EOF;
        }
        return static_cast<unsigned char> (buffer[pos++]);
    }
public:
    FastInput(const char* filename){
        file=fopen(filename, "rb");
    }
    ~FastInput(){
        if (file) fclose(file);
    }
    bool readUInt(uint32_t& x){
        int c;
        do{
            c=readChar();
            if (c==EOF) return false;
        }
        while(c<=' ');
        x=0;
        while(c>='0' && c<='9'){
            x=x*10+(c-'0');
            c=readChar();
        }
        return true;
    }
};
long long shortestPath(const pair<int, int>& query,const vector<int>& offset, const vector<int>& edgesNeigh, const vector<uint32_t>& edgesWt,vector<long long>& bestDist, vector<uint16_t>& seenBy, const int& queryId){
    int source=query.first;
    int target=query.second;
    seenBy[source]=queryId;
    bestDist[source]=0;
    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>>pq;
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
    FastInput graph("/data/graph.txt");
    FastInput queries("/data/queries.txt");
    ofstream output("/out/distances.txt");
    uint32_t nraw; uint32_t mraw;
    if (!graph.readUInt(nraw) || !graph.readUInt(mraw)){
        return 1;
    }
    int n=static_cast<int>(nraw);
    int m=static_cast<int>(mraw);
    map<pair<int, int>, int>minEdgeWt;
    for (int i=0;i<m;++i){
        uint32_t uraw; uint32_t vraw; uint32_t w;
        if (!graph.readUInt(uraw) || !graph.readUInt(vraw) || !graph.readUInt(w)){
            return 1;
        }
        int u=static_cast<int>(uraw);
        int v=static_cast<int>(vraw);
        if (u==v) continue;
        auto it=minEdgeWt.find({u,v});
        if (it==minEdgeWt.end()) {
            minEdgeWt[{u,v}]=w;
        }
        else if (it->second>w){
            it->second=w;
        }
    }
    vector<bool>inDegree(n,false);
    vector<int>outDegree(n,0);
    vector<tuple<int, int, uint32_t>>edges;
    edges.reserve(minEdgeWt.size());
    for (auto &edge:minEdgeWt){
        outDegree[edge.first.first]++;
        if (!inDegree[edge.first.second]) inDegree[edge.first.second]=true;
        edges.emplace_back(edge.first.first,edge.first.second,edge.second);
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
    uint32_t uraw, vraw;
    while (queries.readUInt(uraw)){
        if (!queries.readUInt(vraw)) return -1;
        int u=static_cast<int>(uraw);
        int v=static_cast<int>(vraw);
        graphQueries[cnt]={u, v};
        cnt++;
    }
    int q=graphQueries.size();
    vector<long long>distances(q);
    atomic<int> nextQuery{0};
    auto worker=[&](){
        vector<long long>bestDist(n,LLONG_MAX);   
        vector<uint16_t> seenBy(n, UINT16_MAX); 
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
            distances[i]=shortestPath(graphQueries[i], offset, edgesNeigh, edgesWt, bestDist, seenBy, i);
        }
    };
    vector<thread> workers;
    int threadCount=4;
    for (int i=0;i<threadCount;++i) workers.emplace_back(worker);
    for (auto& t: workers) t.join();
    for (int i=0;i<q;++i) output<<distances[i]<<"\n";
    return 0;
}