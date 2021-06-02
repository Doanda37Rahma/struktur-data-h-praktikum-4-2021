#include <iostream>
#include <list>
#include <limits.h>
using namespace std;
 
class Graph
{
    int V;  
    list<int> *adj; 

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
};



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