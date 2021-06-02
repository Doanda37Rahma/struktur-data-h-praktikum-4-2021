#include <iostream>
#include <list>
#include <limits.h>
using namespace std;
 
class Graph
{
    int V;  
    list<int> *adj; 

    bool isCyclicUtil(int v, bool visited[], int parent)
    {
        
        visited[v] = true;
    
        list<int>::iterator i;
        for (i = adj[v].begin(); i != adj[v].end(); ++i)
        {
            if (!visited[*i])
            {
                if (isCyclicUtil(*i, visited, v))
                    return true;
            }   
    
            else if (*i != parent)
                return true;
        }
        return false;
    }

    

public:
    Graph(int V)
    {
        this->V = V;
        adj = new list<int>[V];
    }

    void addEdge(int v, int w)
    {
        adj[v].push_back(w);
        adj[w].push_back(v);
    }

    bool isCyclic()
    {
        bool *visited = new bool[V];  // pada awal semua node unvisited
        for (int i = 0; i < V; i++)
            visited[i] = false;
    
        for (int u = 0; u < V; u++)
        {
            if (!visited[u])    
                if (isCyclicUtil(u, visited, -1))
                return true;
        }
        return false;
    }
};
 
int main()
{
    int E;
    cin >> E;

    Graph g(100);
    int src, dest;
    while (E--) {
        cin >> src >> dest;
        g.addEdge(src, dest);
    }
    g.isCyclic()?
       cout << "Ada Cycle!\n":
       cout << "Tidak Ada Cycle!\n";
 
    return 0;
}

