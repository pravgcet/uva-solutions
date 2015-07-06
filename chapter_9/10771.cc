#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ii = pair<int,int>;
using vii = vector<ii>;
using vvi = vector<vi>;
using ll = long long;
using llu = unsigned long long;
using vb = vector<bool>;
using vvb = vector<vb>;
using vd = vector<double>;
using vvd = vector<vd>;
using vll = vector<ll>;
const int INF = numeric_limits<int>::max();
const double EPS = 1e-10;

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  ll n, m, k;
  while (cin >> n >> m >> k, n + m) {
    vector<bool> v(n + m, false);
    for (ll i = n; i < n + m; i++) v[i] = true;
    ll p = 0;
    for (ll i = 0; i < n + m - 1; i++) {
      p = (p + k - 1) % v.size();
      bool b = v[p];
      v.erase(v.begin() + p);
      p = (p + k - 1) % v.size();
      v[p] = (v[p] != b);
      p++;
    }
    if (v[0]) {
      cout << "Keka" << endl;
    } else {
      cout << "Gared" << endl;
    }
  }
}
