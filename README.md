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

### Fungsi `main()`
```
int main()
{
    int V, E;
    cin >> V >> E;

    Graph g(V);
    int src, dest;
    while (E--) {
        cin >> src >> dest;
        g.addEdge(src - 1, dest - 1);
    }
    int answer = g.countIsland() - 1;
    cout << answer << endl;
 
    return 0;
}
```
### Fungsi `countIsland`
Fungsi ini melakukan DFS / mencoba menginisialisasi DFS pada setiap vertex, \
Pada setiap satu DFS yang berawal dari vertex u, akan menandakan semua yang terhubung dengan vertex u itu visited.\
Maka `countIsland()` menghasilkan jumlah vertex group yang terisolasi
```
    int countIsland()
    {
        int result = 0;
        bool visited[V];
        for (int i = 0; i < V; i++)
            visited[i] = false;
    
        for (int u = 0; u < V; u++)
        {
            if (!visited[u]) {
                result += 1;
                countIslandUtil(u, visited);
            }
        }
        return result;
    }

    void countIslandUtil(int v, bool visited[])
    {
        
        visited[v] = true;
    
        list<int>::iterator i;
        for (i = adj[v].begin(); i != adj[v].end(); ++i)
        {
            if (!visited[*i])
            {
                countIslandUtil(*i, visited);
            }   
        }
    }
```


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
![VISUAL](https://github.com/Doanda37Rahma/struktur-data-h-praktikum-4-2021/blob/main/img/unconnected_graph.jpg)
![VISUAL](https://github.com/Doanda37Rahma/struktur-data-h-praktikum-4-2021/blob/main/img/unconnected_graph_1.jpg)





## Sayonara   
### Verdict
Wrong Answer
### Bukti
![BUKTI](https://github.com/Doanda37Rahma/struktur-data-h-praktikum-4-2021/blob/main/img/s_bukti.png)
### Penjelasan Soal
![VISUAL](https://github.com/Doanda37Rahma/struktur-data-h-praktikum-4-2021/blob/main/img/sayonara_table.png) \
Diberikan papan permainan seperti gambar. Program diminta mencetak langkah-langkah dari lokasi `P` ke `Q`. 
Setiap langkah dengan format xY, x adalah jarak ditempuh, Y adalah arah.
### Ide Solusi & Visualisasi
Lokasi P dan Q direpresentasikan menjadi `src` dan `dest`. 
Dalam papan tersebut, terbentuk dua deret aritmatika:

- Dari setiap corner (tikungan) kanan atas dan kiri bawah:

![VISUAL](https://github.com/Doanda37Rahma/struktur-data-h-praktikum-4-2021/blob/main/img/sayonara_deret.png)

- Dari corner kiri atas dan kanan bawah:

![VISUAL](https://github.com/Doanda37Rahma/struktur-data-h-praktikum-4-2021/blob/main/img/sayonara_deret 2.png)

Dari kedua deret tersebut, dapat ditentukan jarak yang ditempuh antar corner, serta arahnya (dari paritas/ ganjil genap n).
Kemudian membuat algoritme loop untuk mencetak output, yang berhenti setelah sampai `dest`.

## Puzzle MudMud 
### Verdict
AC saat Praktikum
### Bukti
![BUKTI](https://github.com/Doanda37Rahma/struktur-data-h-praktikum-4-2021/blob/main/img/pm_bukti.png)
### Penjelasan Soal
Diberikan beberapa 8 angka puzzle yang belum terselesaikan. \
Program diminta menentukan banyak langkah dan mencetak tiap langkah untuk menyelesaikan puzzle jika bisa, jika tidak keluarkan "Problem tidak dapat diselesaikan". \
Berikut contoh initial state dan final state.\
![VISUAL](https://github.com/Doanda37Rahma/struktur-data-h-praktikum-4-2021/blob/main/img/puzzle.png)

### Penjelasan Solusi
Setiap problem/puzzle direpresentasikan dengan 2d array
Pertama program menentukan apakah bisa menyelesaikan puzzle. 8 angka puzzle dapat diselesaikan hanya jika jumlah inversi(pasangan yang urutannya terbalik) dari angka-angka adalah genap, didapat dari `getInvCount()`. Kemudian menggunakan traversal BFS (fungsi `solve()`) untuk tiap langkah, menggeser blank dengan urutan langkah (atas, bawah, kanan , kiri) jika langkah legal (dengan func `isSafe()`). Pencarian dilakukan sampai final state. \
Setiap state/node puzzle memiliki beberapa atribut: \
- Reference ke parent node `Node* parent`
- 2d array yang merepresentasikan papan 3x3 `mat[3][3]`
- `x`, `y`, lokasi blank pada node 
Jika sudah menemukan final state dengan fungsi `isMatched()`, maka menentukan langkah minimum `printMinSteps()` dan mencetak langkah `printSteps()`.
### Fungsi `main()`
```
int main()
{
    char input[N][N];
    int initial[N][N];
    int lined[9];
    int x, y;
    int final[N][N] =	
    {
        {1, 2, 3},
        {4, 5, 6},	// final state
        {7, 8, 0}
    };

    while (scanf("%s", input[0]) != EOF) {  // input stops at EOF
        scanf("%s", input[1]);
        scanf("%s", input[2]);

        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {

                initial[i][j] = input[i][j] - '0';   // konversi input string to int

                if (initial[i][j] == 0) 
                    x = i, y = j;	// find loc of blank

                lined[i*3 + j] = initial[i][j];  // 2d to 1d array
            }
        }

        int invCount = getInvCount(lined, 9);  // count inversions

        if (invCount % 2 != 0) {   // jika tidak genap
            cout << "Problem tidak dapat diselesaikan" << endl;
            continue;
        }

        solve(initial, x, y, final); // jika genap, do BFS
    }
    
    return 0;
}

```

### Fungsi `getInvCount()` 
Mencari jumlah inversion.
```
int getInvCount(int arr[], int n)
{
    int inv_count = 0;
    for (int i = 0; i < n - 1; i++)
        for (int j = i + 1; j < n; j++)
            if (arr[i] > arr[j] && arr[i] != 0 && arr[j] != 0)
                inv_count++;
 
    return inv_count;
}
```
### Fungsi `solve()`
BFS untuk mencari final state.
```
// BFS: atas, bawah, kanan, kiri 
int row[] = { -1, 1, 0, 0 };
int col[] = { 0, 0, 1, -1 };
// BFS
void solve(int initial[N][N], int x, int y,
           int final[N][N])
{
    queue<Node*> q;  // queue, standard BFS
 
    Node* root = newNode(initial, x, y, x, y, NULL);   // inisialisasi initial state
 
    q.push(root);  
    
    bool flag = true;  // flag untuk menandakan node root/pertama, relevan dibawah

    while (!q.empty())
    {
        Node* min = q.front();   // node yang dikembangkan 
 
        q.pop();

        if (isMatched(min->mat, final)) {  // cek apakah current state = final state
            printMinSteps(min);
            printPath(min, true);
            return;
        }
 
        for (int i = 0; i < 4; i++)    // loop untuk mencoba menggeser blank dari current state ke 4 arah, 
        {
            if (isSafe(min->x + row[i], min->y + col[i]))  // memastikan state selalu legal, (menghindari array out of bounds error)
            {
                Node* child = newNode(min->mat, min->x,  // menciptakan node yang akan dikembangkan selanjutnya
                              min->y, min->x + row[i],	
                              min->y + col[i], min);

                if (!flag) 	// flag = 0 jika bukan node root, maka node memiliki parent (menghindari null pointer error)
                    if (child->parent->parent->x == child->x &&  // kita tidak mau traverse ke yang baru saja kita lewati (parent node),
                        child->parent->parent->y == child->y)    // maka cek koordinat current node's child and parent jika sama
                        continue;
                q.push(child);
            }
        }
        flag = false; // setelah root terlewati, turunkan flag
    }
}
```
### Fungsi `newNode()`
Menciptakan instance node/state dengan lokasi blank dan salah satu angka (atas/bawah/kanan/kirinya) tertukar
```
Node* newNode(int mat[N][N], int x, int y, int newX,
              int newY, Node* parent)
{
    Node* node = new Node;
    node->parent = parent;
    memcpy(node->mat, mat, sizeof node->mat);      // copy value parent dan alokasikan memori ke node baru
    swap(node->mat[x][y], node->mat[newX][newY]);  // tukar blank dengan angka
    node->x = newX;  
    node->y = newY;
 
    return node;
}
```
### Fungsi `isMatched()`
Mengecek apakah dua matrix 3x3 puzzle sama
```
bool isMatched(int mata[N][N], int matb[N][N]) 
{   
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j) 
            if (mata[i][j] != matb[i][j])
                return false;
    return true;
}
```
### Fungsi `printPath()` dan utility `printMatrix()`
Mencetak matrix mulai dari ***langkah pertama*** sampai
```
void printPath(Node* root, bool isLast)
{
    if (root->parent == NULL)   
        return;
    printPath(root->parent, false);  // rekur ke root child (seperti stack)  
    printMatrix(root->mat);	     // print dari top stack
    if (!isLast)
        printf("\n");
}

void printMatrix(int mat[N][N])
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
            printf("%d", mat[i][j]);
        printf("\n");
    }
}
```
### Fungsi `printMinSteps()` dan utility `minSteps()`
```
void printMinSteps(Node* root)
{
    int ans = minSteps(root);  //  linear traverse ke root, hitung banyak langkahnya 
    cout << "Langkah minimum = " << ans << endl;  // output
}

int minSteps(Node* root) 
{
    if (root->parent == NULL) return 0;
    return minSteps(root->parent) + 1;
}
```

### Visualisasi Solusi
Sample Input 0
```
123
456
078

012
345
687
```
Sample Output 0
```
Langkah minimum = 2
123
456
708

123
456
780
Problem tidak dapat diselesaikan
```
![VISUAL](https://github.com/Doanda37Rahma/struktur-data-h-praktikum-4-2021/blob/main/img/8puzzle.png)
