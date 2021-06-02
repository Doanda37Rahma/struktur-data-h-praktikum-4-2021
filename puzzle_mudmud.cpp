#include <bits/stdc++.h>
using namespace std;
#define N 3

#define deb(x) cout << #x << " = " << x << endl
#define logg(x) cout << x << endl

struct Node
{
    Node* parent;
    int mat[N][N];
    int x, y;
};
 
Node* newNode(int mat[N][N], int x, int y, int newX,
              int newY, Node* parent)
{
    Node* node = new Node;
    node->parent = parent;
    memcpy(node->mat, mat, sizeof node->mat);
    swap(node->mat[x][y], node->mat[newX][newY]);
    node->x = newX;
    node->y = newY;
 
    return node;
}
 
// BFS: atas, bawah, kanan, kiri 
int row[] = { -1, 1, 0, 0 };
int col[] = { 0, 0, 1, -1 };
  
int isSafe(int x, int y)
{
    return (x >= 0 && x < N && y >= 0 && y < N);
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

void printPath(Node* root, bool isLast)
{
    if (root->parent == NULL)
        return;
    printPath(root->parent, false);
    printMatrix(root->mat);
    if (!isLast)
        printf("\n");
}

int minSteps(Node* root) 
{
    if (root->parent == NULL) return 0;
    return minSteps(root->parent) + 1;
}

void printMinSteps(Node* root)
{
    int ans = minSteps(root);
    cout << "Langkah minimum = " << ans << endl;
}

bool isMatched(int mata[N][N], int matb[N][N]) 
{   
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j) 
            if (mata[i][j] != matb[i][j])
                return false;
    return true;
}
 
// BFS
void solve(int initial[N][N], int x, int y,
           int final[N][N])
{
    queue<Node*> q;
 
    Node* root = newNode(initial, x, y, x, y, NULL);
 
    q.push(root);
    
    bool flag = true;

    while (!q.empty())
    {
        Node* min = q.front();
 
        q.pop();

        if (isMatched(min->mat, final)) {
            printMinSteps(min);
            printPath(min, true);
            return;
        }
 
        for (int i = 0; i < 4; i++)
        {
            if (isSafe(min->x + row[i], min->y + col[i]))
            {
                Node* child = newNode(min->mat, min->x,
                              min->y, min->x + row[i],
                              min->y + col[i], min);

                if (!flag) 
                    if (child->parent->parent->x == child->x && 
                        child->parent->parent->y == child->y)
                        continue;
                q.push(child);
            }
        }
        flag = false;
    }
}

 
int getInvCount(int arr[], int n)
{
    int inv_count = 0;
    for (int i = 0; i < n - 1; i++)
        for (int j = i + 1; j < n; j++)
            if (arr[i] > arr[j] && arr[i] != 0 && arr[j] != 0)
                inv_count++;
 
    return inv_count;
}

int main()
{
    char input[N][N];
    int initial[N][N];
    int lined[9];
    int x, y;
    int final[N][N] =
    {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 0}
    };

    while (scanf("%s", input[0]) != EOF) {
        scanf("%s", input[1]);
        scanf("%s", input[2]);

        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {

                initial[i][j] = input[i][j] - '0';

                if (initial[i][j] == 0) 
                    x = i, y = j;

                lined[i*3 + j] = initial[i][j];
            }
        }

        int invCount = getInvCount(lined, 9);

        if (invCount % 2 != 0) {
            cout << "Problem tidak dapat diselesaikan" << endl;
            continue;
        }

        solve(initial, x, y, final);
    }
    
    return 0;
}

