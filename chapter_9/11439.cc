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

map<llu, llu> DP;
vector<vector<llu>> icpc;

llu dp(llu mask) {
  if (DP.count(mask)) {
    return DP[mask];
  }
  // cout << mask << " #" << endl;
  ll i = 0;
  llu r = 0;
  while ((mask & (1ull << i)) == 0) i++;
  vll v;
  for (ll j = i + 1; j < 64; j++) {
    if (mask & (1ull << j)) {
      v.emplace_back(j);
    }
  }

  sort(v.begin(), v.end(), [&] (const ll a, const ll b) {
    return icpc[i][a - i - 1] > icpc[i][b - i - 1];
  });

  for (auto j : v) {
    llu m = (mask ^ (1ull << i)) ^ (1ull << j);
    if (icpc[i][j - i - 1] < r) continue;
    r = max(r, min(icpc[i][j - i - 1], dp(m)));
  }

  return DP[mask] = r;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  int tcc; cin >> tcc;
  for (int tc = 1; tc <= tcc; tc++) {
    ll n; cin >> n;
    n = 1 << n;
    icpc.resize(n);
    for (ll i = 0; i < n - 1; i++) {
      icpc[i].resize(n - i - 1);
      for (ll j = 0; j < icpc[i].size(); j++) cin >> icpc[i][j];
    }
    DP.clear();
    DP[0] = INF;
    // llu m;
    llu m = (1ull << n) - 1;
    if (n == 64) m = -1;
    // cout << m << "?" << endl;
    llu answer = dp(m);
    cout << "Case " << tc << ": " << answer << endl;
  }
}
