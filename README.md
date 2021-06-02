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

### Fungsi `findCost()`  
Fungsi findCost mengaplikasikan Prim's MST untuk mencari biaya minimum.

Setiap vertex memiliki 3 properti: 
- Parent node tersebut `parent[v]`
- Jarak untuk mencapai node tsb `costToReach[v]`
- Apakah node tsb sudah masuk dalam MST `isIn[v]`
Biaya minimum adalah jumlah jarak tiap node.

Reference:
- https://www.youtube.com/watch?v=cplfcGZmX7I
- https://www.geeksforgeeks.org/prims-minimum-spanning-tree-mst-greedy-algo-5/
```
void findCost(int n, vector<vector<double>> houses) {  
    
    int parent[n];
    
    double costToReach[n];	
    
    bool isIn[n]; 
    
    for (int i = 0; i < n; i++) {
        costToReach[i] = numeric_limits<double>::max();  // pertama inisialisasi semua jarak tak hingga
        isIn[i] = false;				 // belum ada yang dimasukkan ke MST
    }
    
    parent[0] = -1;   	// berawal dari vertex 0 yang tidak memiliki parent
    costToReach[0] = 0; // jarak dari vertex 0 ke 0 adalah 0
    
    for (int i = 0; i < n - 1; i++) {
    
        int u = nearestNode(n, costToReach, isIn);  // mencari node dengan costToReach terkecil yang belum masuk dalam MST
    
        isIn[u] = true;  // memasukkan vertex u (neighbor terdekat) kedalam MST
    
        for (int v = 0; v < n; v++) {			// cek tiap vertex (representasi adj.matrix)
            if (houses[u][v] && isIn[v] == false &&  	// jika menemukan neighbor dari u (v) yang belum masuk MST [menghindari cycle]
                houses[u][v] < costToReach[v]) {	// jika edge u-v < jarak ke v 
                costToReach[v] = houses[u][v];		// maka, jarak ke v = edge u-v	
                parent[v] = u;				// parent v adalah u
            }
        }
    }
    
    // mencari biaya minimum, menjumlahkan edge dari node dan parentnya
    double cost = 0;
    for (int i = 1; i < n; i++)  // mulai dari vertex 1 (v0 tidak punya parent)
        cost += houses[parent[i]][i]; 
    printf("%lf\n", cost); 	// output
}
```
### Fungsi `nearestNode()`
Prim's merupakan greedy algorithm, disini algoritma mengasumsikan bahwa untuk mencari hubungan dengan cost minimal, maka harus mengekspansi ke vertex dengan jarak minimum. (seperti dijkstra)
Fungsi ini menentukan vertex mana yang harus diekspansikan selanjutnya, mencari vertex yang belum ada dalam MST dengann costToReach minimum
```
double nearestNode(int n, double costToReach[], bool isIn[]) {
    double minDist = numeric_limits<double>::max(); 
    int minIndex;

    for (int i = 0; i < n; i++) {
        if (isIn[i] == false && costToReach[i] < minDist) {
            minDist = costToReach[i], minIndex = i;
        }
    }
    return minIndex;
}
```
### Visualisasi Solusi
Berikut contoh visualisasi Prim's MST Algorithm:
- Dengan euclidean distance:

![VISUAL](https://github.com/Doanda37Rahma/struktur-data-h-praktikum-4-2021/blob/main/img/PrimAlgDemo.gif)

- Dengan weighted graph:

![VISUAL](https://github.com/Doanda37Rahma/struktur-data-h-praktikum-4-2021/blob/main/img/prim_visual.gif)


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
Diberikan undirected unconnected graph dengan `T` vertex dan `L` edge yang direpresentasikan sebagai pulau dan jembatan yang menghubungkan. Program diminta mencari jumlah jembatan minimum untuk menghubungkan semua pulau.
### Penjelasan Solusi
Karena graph undirected dan tidak terhubung (unconnected) maka DFS dapat digunakan untuk menghitung banyak rumpun node (pulau) yang terhubung. Dengan begitu, jumlah jembatan minimum adalah jumlah rumpun node dikurangi satu.


### Visualisasi Solusi
Sample Input:
```
14 13 
1 2
1 3
2 4
3 4
3 6
5 6
5 7
6 8
7 8
9 10
11 12 
11 13
12 13
```
Sample Output:
```
3
```
![VISUAL]()

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
