#include <iostream>
#include <utility>

using namespace std;

int main() {
    long long v[200];
    while (scanf("%lld", v) == 1) {
        int n = 1;
        while (true) {
            scanf("%lld", v + n);
            if (v[n] == -999999) break;
            n++;
        }
        long long m = v[0];
        long long p = 1;
        for (int i = 0; i < n; i++) {
            p *= v[i];
            m = max(m, p);
            if (p == 0) p = 1;
        }
        p = 1;
        for (int i = n - 1; i >= 0; i--) {
            p *= v[i];
            m = max(m, p);
            if (p == 0) p = 1;
        }
        printf("%lld\n", m);
    }
}
