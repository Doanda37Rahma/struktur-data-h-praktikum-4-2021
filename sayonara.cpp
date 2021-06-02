#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define MEMLIM 1200

#define deb(x) cout << #x << "=" << x << endl
#define logg(x) cout << x << endl



void solve() 
{
    int src, dest;
    scanf("%d %d", &src, &dest);
    if (src > dest) swap(src,  dest);

    // deb(src);
    // deb(dest);

    double approx = ceil((1 + sqrt(1 + 4*src)) / 2 + 0.000000000001);
    int n = (int)approx;

    // deb(approx);
    // deb(n);

    int full = n*(n-1);
    int halfway = (n-1)*(n-1);
    // int prev = (n-1)*(n-2);
    // deb(full);
    // deb(halfway);
    // deb(prev);
    

    char dir[] = {'U', 'T', 'S', 'B'};

    int di;

    if (src < halfway) {
        di = n % 2? 2 : 0;
        if (dest <= halfway) {
            printf("%d%c -> \n", dest - src, dir[di]);
            // logg("case both under");
            return;
        }
        if (dest <= full) {
            printf("%d%c -> ", halfway - src, dir[di]);
            printf("%d%c\n", dest - halfway, dir[di+1]);
            // logg("case under above");
            return;
        }
        printf("%d%c -> ", halfway - src, dir[di]);
        printf("%d%c -> ", full - halfway, dir[di+1]);
        // logg("case under half");
        di += 2;
    }
    else {
        di = n % 2? 3 : 1;
        if (dest <= full) {
            printf("%d%c -> \n", dest - src, dir[di]);
            // logg("case both above");
            return;
        }
        printf("%d%c -> ", full - src, dir[di]);
        // logg("case above half");
        di += 1;
    }
    int diff = n;

    // int startingdist = dest - src;
    // int totalreached = 0;
    // totalreached += full - src;
    // deb(totalreached);

    src = full;

    int distance = dest - src;


    while (distance > 0) {
        if (diff >= distance) break;
        printf("%d%c -> ", diff, dir[di % 4]);
        
        // totalreached += diff;
        // deb(totalreached);

        distance -= diff;
        di++;

        if (diff >= distance) break;
        printf("%d%c -> ", diff, dir[di % 4]);

        // totalreached += diff;
        // deb(totalreached);

        distance -= diff;
        di++;
        diff++;
    }

    // totalreached += distance;
    // deb(totalreached);
    // deb(distance);
    // deb(dir[di%4]);
    // deb(diff);
    // deb(startingdist);
    // deb(totalreached);

    printf("%d%c \n", distance, dir[di % 4]);

    return;
}

int main() 
{
    int t;
    cin >> t;
    while (t--) solve();

    return 0;
}
