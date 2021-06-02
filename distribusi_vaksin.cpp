#include<bits/stdc++.h>
using namespace std;
#define INF 0x3f3f3f3f

#define debug(x)	cout << #x << '=' << x << endl;

typedef pair<int, int> iPair;
  
void addEdge(vector <pair<int, int> > adj[], int u,
                                     int v, int wt)
{
    adj[u].push_back(make_pair(v, wt));
    // Disable to make graph directed
    adj[v].push_back(make_pair(u, wt));
}

// Dijkstra  
int shortestPath(vector<pair<int,int> > adj[], int V, int src, int dest)
{
    priority_queue< iPair, vector <iPair> , greater<iPair> > pq;
  
    vector<int> dist(V, INF);
  
    pq.push(make_pair(0, src));
    dist[src] = 0;
  
    while (!pq.empty())
    {
        if (pq.top().second == dest) {
            return dist[dest];
        }

        int u = pq.top().second;
        pq.pop();
  
        for (auto x : adj[u])
        {
            int v = x.first;
            int weight = x.second;

            if (dist[v] > dist[u] + weight)
            {
                dist[v] = dist[u] + weight;
                pq.push(make_pair(dist[v], v));
            }
        }
    }
    
    return -1;
}
  
int main()
{
    int V, M, Q;
    cin >> V >> M >> Q;  // input 

    if ( V < 2 || Q < 2) {  // jika hanya 1 rumah atau 1 tujuan, waktu minimum = 0
        cout << 0 << endl;
        return 0;
    }
    
    vector<iPair > adj[V];  // adjacency list

    for (int i = 0; i < M; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        addEdge(adj, u-1, v-1, w);  // memasukkan edge (1 base index menjadi 0 base)
    }

    int query[Q];
    for (int i = 0; i < Q; ++i) {   
        cin >> query[i];
        query[i]--;     // memasukkan query (menjadi 0 base index)
    }
    int ans = 0;
    for (int i = 0; i < Q - 1; ++i) {       // menjumlah jarak minimum total antara tiap tujuan
        ans += shortestPath(adj, V, query[i], query[i+1]);  // Dijkstra shortest path algorithm
                                                            // antara dua node
    }
    cout << ans << endl;
    
    return 0;
}

