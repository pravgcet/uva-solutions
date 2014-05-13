#include <iostream>
#include <utility>

using namespace std;

int main() {
    int n;
    while (cin >> n, n) {
        int m = -999999;
        int s = 0;
        for (int i = 0; i < n; i++) {
            int v;
            cin >> v;
            s += v;
            m = max(m, s);
            s = max(s, 0);
        }
        if (s > 0) {
            printf("The maximum winning streak is %d.\n", s);
        } else {
            printf("Losing streak.\n");
        }
    }
}
