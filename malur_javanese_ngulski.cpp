#include <bits/stdc++.h>
 
using namespace std;
 
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

double euclidean(double x1, double y1, double x2, double y2)
{
	double x = x1 - x2; 
	double y = y1 - y2;
	double dist;

	dist = x * x + y * y;       
	dist = sqrt(dist);                  

	return dist;
}
 
int main() {

    int V;
    cin >> V;
    double x[V], y[V], h[V];
    for (int i = 0; i < V; ++i) {
        cin >> x[i] >> y[i] >> h[i];
    }

    vector<vector<double>> houses(V, vector<double>(V, 0.0));

    for (int i = 0; i < V-1; ++i) {
        for (int j = i+1; j < V; ++j) {
            houses[i][j] = euclidean(x[i], y[i], x[j], y[j]) * fabs(h[j] - h[i]);
            houses[j][i] = houses[i][j];
        }
    }
    
    findCost(V, houses);
    return 0;
}

// https://www.geeksforgeeks.org/prims-minimum-spanning-tree-mst-greedy-algo-5/
// https://www.geeksforgeeks.org/minimum-cost-connect-cities/
