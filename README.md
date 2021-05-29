# struktur-data-h-praktikum-4-2021

mjn dv rsk cr s pm

## Malur Javanese Ngulski 
### Verdict
AC saat Praktikum
### Bukti
![BUKTI](https://github.com/Doanda37Rahma/struktur-data-h-praktikum-4-2021/blob/main/img/mjn_bukti.png)
### Penjelasan Soal
Diberikan `n` rumah (vertex) dengan properti  (`x`, `y`), lokasi kartesian tiap rumah, dan `h`, tingkat kerumitan. Program diminta menghitung biaya minimum untuk menghubungkan tiap rumah. Setiap jalan antara dua rumah dihitung dengan rumus `euclidian(x,y) * Δh`.

### Penjelasan Solusi
Solusinya adalah mencari `minimum spanning tree` dari graph yang dimaksud, kemudian menghitung total `weight` dari MST yang terbentuk.
Pertama program dengan rumus `euclidian(x,y) * Δh` menghitung edge weight antar rumah dan memasukkannya ke dalam adjacency matrix (karena setiap vertex terhubung dengan semua vertex lain/ dense graph).
Minimum Spanning Tree ditentukan menggunakan 

### Fungsi `euclidean()`
Menemukan jarak terdekat antara dua rumah dalam bidang kartesian
_______________
![Euclid](https://www.researchgate.net/profile/Young-Sun-Lee-2/publication/263889770/figure/fig1/AS:890653479284740@1589359745492/An-example-of-Euclidean-distance-between-two-objects-on-variables-X-and-Y.png)
```
double euclidean(double x1, double y1, double x2, double y2)
{
	double x = x1 - x2; 
	double y = y1 - y2;
	double dist;

	dist = x * x + y * y;       
	dist = sqrt(dist);                  

	return dist;
}
```

### Fungsi `findCost`
```
void findCost(int n, vector<vector<double>> houses) {
    
    int parent[n];
    
    double costToReach[n];
    
    bool isIn[n];
    
    for (int i = 0; i < n; i++) {
        costToReach[i] = numeric_limits<double>::max();
        isIn[i] = false;
    }
    
    parent[0] = -1;
    costToReach[0] = 0;
    
    for (int i = 0; i < n - 1; i++) {
    
        int u = nearestNode(n, costToReach, isIn);
    
        isIn[u] = true;
    
        for (int v = 0; v < n; v++) {
            if (houses[u][v] && isIn[v] == false &&
                houses[u][v] < costToReach[v]) {
                costToReach[v] = houses[u][v];
                parent[v] = u;
            }
        }
    }
    
    double cost = 0;

    for (int i = 1; i < n; i++)
        cost += houses[parent[i]][i];
    printf("%lf\n", cost);
}
```



### Visualisasi Solusi
Sample Input 
```
5
3434 5546 1058
1461 5000 3652
2941 5764 5711
3918 9476 1946
9467 7739 7082
```
Sample Output 
```
18801687.039806
```
![VISUAL](https://github.com/Doanda37Rahma/struktur-data-h-praktikum-4-2021/blob/main/img/mjn_visual.png)




## Distribusi Vaksin
### Verdict
AC saat Praktikum
### Bukti
![BUKTI](https://github.com/Doanda37Rahma/struktur-data-h-praktikum-4-2021/blob/main/img/dv_bukti.png)
### Penjelasan Soal
Diberikan sebuah graph dengan `V` rumah (vertex), `E` ruas jalan (edge), dan `Q` tujuan yang dilalui secara berurutan. Program diminta menentukan waktu minimum untuk mengirim semua vaksin secara berurutan ke semua tujuan, berawal dari Q1.
### Penjelasan Solusi
Waktu minimum adalah `cost of shortest path` antara dua vertex dalam graph.
Waktu minimum total dapat dihitung dengan menjumlahkan cost dari waktu minimum antara dua lokasi tujuan, jadi menghitung waktu minimum antara Q1 dan Q2, kemudian antara Q2 dan Q3, Q3 dan Q4, sampai Qn-1 dan Qn.
`Cost of shortest path` dapat dihitung menggunakan algoritma `Dijkstra`.

### Fungsi main()
```
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

```
### Fungsi shortestPath()
Penjelasan algoritma Dijkstra dapat dilihat [disini](https://github.com/Doanda37Rahma/struktur-data-h-asistensi-4-2021)
```
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
```
### Visualisasi Solusi
Sample Input
```
5 6 5
1 2 6
1 4 12
3 2 8
3 4 4
3 5 10
5 4 16
1
5
2
4
3
```
Sample Output
```
58
```


## Roy sang kurir 
### Verdict
AC saat Praktikum
### Bukti
![BUKTI](https://github.com/Doanda37Rahma/struktur-data-h-praktikum-4-2021/blob/main/img/rsk_bukti.png)
### Penjelasan Soal
Diberikan sebuah undirected graph, program diminta menentukan apakah graph memiliki cycle.
### Penjelasan Solusi
DFS dapat digunakan untuk menemukan cycle dalam undirected graph. Cara kerjanya adalah setiap node saat traversal DFS akan melihat node-node neighbor nya. Jika node neighbor tersebut sudah dilalui dan bukan parent dari node itu sendiri, maka terdapat cycle dalam graph.
### Fungsi main()
```
int main()
{
    int E;
    cin >> E;

    Graph g(100);
    int src, dest;
    while (E--) {
        cin >> src >> dest;
        g.addEdge(src, dest); // representasi adjacency list
    }
    g.isCyclic()?
       cout << "Ada Cycle!\n":
       cout << "Tidak Ada Cycle!\n";
 
    return 0;
}
```
### Fungsi isCyclic()
```
bool isCyclic()
{
    bool *visited = new bool[V];  // pada awal semua node unvisited
    for (int i = 0; i < V; i++)
        visited[i] = false;

    for (int u = 0; u < V; u++)  // DFS untuk setiap node 
    {
        if (!visited[u])    
            if (isCyclicUtil(u, visited, -1))  
            return true;
    }
    return false;
}

bool isCyclicUtil(int v, bool visited[], int parent)
{
    
    visited[v] = true;   // current node di tandai visited

    list<int>::iterator i;
    for (i = adj[v].begin(); i != adj[v].end(); ++i)  // untuk setiap neighbor
    {
        if (!visited[*i])   // jika belum visited, rekursi ke situ
        {
            if (isCyclicUtil(*i, visited, v))
                return true;
        }   
                               // jika sampai bagian ini maka menemukan neighbor yang sudah dikunjungi
        else if (*i != parent) // jika neighbor itu bukan parent nya sendiri, ditemukan cycle
            return true;
    }
    return false;
}

```

### Visualisasi Solusi
Sample Input 
```
5
1 0
0 2
2 1
0 3
3 4
```
Sample Output 
```
Ada Cycle!
```
![VISUAL cycle](https://s3.amazonaws.com/hr-assets/0/1621786763-8cf149ffb6-Annotation2021-05-23231854.png)


## Cayo Refreshing 
### Verdict
AC saat Praktikum
### Bukti
![BUKTI](https://github.com/Doanda37Rahma/struktur-data-h-praktikum-4-2021/blob/main/img/cr_bukti.png)
### Penjelasan Soal
### Penjelasan Solusi
### Visualisasi Solusi




## Sayonara   
### Verdict
AC saat Praktikum
### Bukti
![BUKTI](https://github.com/Doanda37Rahma/struktur-data-h-praktikum-4-2021/blob/main/img/s_bukti.png)
### Penjelasan Soal
### Penjelasan Solusi
### Visualisasi Solusi




## Puzzle MudMud 
### Verdict
AC saat Praktikum
### Bukti
![BUKTI](https://github.com/Doanda37Rahma/struktur-data-h-praktikum-4-2021/blob/main/img/pm_bukti.png)
### Penjelasan Soal
### Penjelasan Solusi
### Visualisasi Solusi
