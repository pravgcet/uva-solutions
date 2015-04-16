#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ii = pair<int,int>;
using ll = long long;
using llu = unsigned long long;
const int INF = numeric_limits<int>::max();

int main() {
  int m, n;
  int tc = 0;
  while (cin >> m >> n, m) {
    tc++; printf("Region %d\n", tc);
    vector<ll> levels(m * n);
    ll f = INF;
    for (int i = 0; i < m * n; i++) {
      cin >> levels[i]; levels[i] *= 100;
      f = min(f, levels[i]);
    }
    ll v; cin >> v;
    v *= 1000000;
    ll t = INF; // invariant is f <= x, t > x
    while (f != t) {
      ll m = (f + t) / 2;
      ll a = 0;
      for (auto l : levels) {
        if (m < l) continue;
        a += 1000 * 1000 * (m - l);
      }
      if (a == v) {
         f = t = m; break;
      }
      if (a < v) {
        f = m + 1;
      } else {
        t = m - 1;
      }
    }
    double flooded = 0;
    for (auto l : levels) if (l < f) flooded++;
    printf("Water level is %.2f meters.\n", ((double) f) / 100);
    printf("%.2f percent of the region is under water.\n\n",
          (flooded * 100) / (n * m));
  }
}
