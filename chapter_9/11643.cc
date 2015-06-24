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

const int MAX = 16;

ll D[MAX][MAX];
struct point { int x, y; };
const int dx[] = { -2, -2, -1, -1, 1, 1, 2, 2};
const int dy[] = { 1, -1, 2, -2, 2, -2, 1, -1};
ll dpm[MAX][1 << MAX];

ll dp(ll mask, int p) {
  ll &r = dpm[p][mask];
  if (r < 0) {
    if (mask == 0) {
      r = D[p][0];
      return r;
    }
    r = INF;
    for (int i = 1; i < MAX; i++) {
      if (mask & (1 << i)) {
        r = min(r, D[p][i] + dp(mask ^ (1 << i), i));
      }
    }
  }
  return r;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  int tcc; cin >> tcc;
  for (int tc = 1; tc <= tcc; tc++) {
    ll n, s; cin >> s >> n;
    vector<point> knights(n);
    for (ll i = 0; i < n; i++) cin >> knights[i].x >> knights[i].y;
    fill(&D[0][0], &D[MAX][0], INF);
    for (ll i = 0; i < n; i++) {
      D[i][i] = 0;
      queue<pair<point, int>> q;
      q.emplace(make_pair(knights[i], 0));
      while (!q.empty()) {
        ll d; point p;
        tie(p, d) = q.front(); q.pop();
        for (ll j = 0; j < n; j++) {

          ll a = abs(p.x - knights[j].x);
          ll b = abs(p.y - knights[j].y);
          if (a < b) swap(a, b);
          if (a % 2 != 0) continue;
          if (a / 2 >= b && ((a / 2) % 2 == b % 2)) {
            D[i][j] = D[j][i] = min(D[i][j], d + a / 2);
          }
        }
        if (d < 4) {
          for (int j = 0; j < 8; j++) {
            point t;
            t.x = p.x + dx[j];
            t.y = p.y + dy[j];
            if (t.x < 1 || t.x > s || t.y < 1 || t.y > s) continue;
            q.emplace(make_pair(t, d + 1));
          }
        }
      }
    }
    fill(&dpm[0][0], &dpm[MAX][0], -1);
    ll answer = dp((1 << n) - 2, 0);
    cout << "Case " << tc << ": " << answer << endl;
  }
}
