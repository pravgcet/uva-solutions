#include <iostream>
#include <utility>

using namespace std;

const int MAX = 20 + 1;

int main() {
    // int v[MAX][MAX][MAX];
    long long q[MAX][MAX][MAX];
    int tcc;
    cin >> tcc;
    for (int tc = 1; tc <= tcc; tc++) {
        if (tc != 1) printf("\n");
        int a, b, c;
        cin >> a >> b >> c;
        for (int i = 0; i <= a; i++)
        for (int j = 0; j <= b; j++)
        for (int k = 0; k <= c; k++) {
            if (i * j * k == 0) {
                q[i][j][k] = 0;
                continue;
            }
            int v;
            cin >> q[i][j][k];
            q[i][j][k] += q[i-1][j][k] + q[i][j-1][k] + q[i][j][k-1];
            q[i][j][k] += q[i-1][j-1][k-1];
            q[i][j][k] -= q[i-1][j-1][k] + q[i-1][j][k-1] + q[i][j-1][k-1];
        }
        long long m = q[1][1][1];
        for (int i = 0; i < a; i++)
        for (int j = 0; j < b; j++)
        for (int k = 0; k < c; k++)
        for (int x = i + 1; x <= a; x++)
        for (int y = j + 1; y <= b; y++)
        for (int z = k + 1; z <= c; z++) {
            long long t = q[x][y][z];
            t -= q[i][j][k];
            t -= q[i][y][z] + q[x][j][z] + q[x][y][k];
            t += q[i][j][z] + q[i][y][k] + q[x][j][k];
            m = max(m, t);
        }
        printf("%lld\n", m);
    }
}
