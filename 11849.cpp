#include <stdio.h>

int cds[1000001];

int main() {
    int m, n;
    while (scanf("%d%d", &n, &m), n != 0 && m !=0) {
        for (int i = 0; i < n; i++) {
            scanf("%d", cds + i);
        }
        int r = 0;
        int p = 0;
        while (m--) {
            int v;
            scanf("%d", &v);
            while (p < n && cds[p] < v) p++;
            if (cds[p] == v) r++;
            // int l = 0;
            // int t = n;
            // while (l < t) {
            //     int m = (l + t) / 2;
            //     if (cds[m] == v) {
            //         l = t = m;
            //         break;
            //     }
            //     if (cds[m] > v) {
            //         t = m;
            //         continue;
            //     }
            //     l = m + 1;
            // }
            // if (l == n || cds[l] != v) continue;
            // r++;
        }
        printf("%d\n", r);
    }
    return 0;
}
