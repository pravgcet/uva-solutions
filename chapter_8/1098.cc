#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ii = pair<int,int>;
using ll = long long;
using llu = unsigned long long;
const int INF = numeric_limits<int>::max();
const int MAX = 8;

struct check_point {
  int x, y, t;
};

check_point cp[2];
const int dx[] = { 1, -1, 0, 0 };
const int dy[] = { 0, 0, 1, -1 };
bool field[MAX][MAX];
int n, m;
int counter;
llu full;
int start_x, start_y;

bool connected() {
  // return true;
  bool w[MAX][MAX];
  memcpy(&w, &field, MAX * MAX * sizeof(bool));
  queue<pair<int, int>> q;
  q.emplace(0, 1);
  w[0][1] = true;
  while (!q.empty()) {
    auto p = q.front(); q.pop();
    for (int i = 0; i < 4; i++) {
      int x = p.first + dx[i];
      int y = p.second + dy[i];
      if (x < 0 || x >= n || y < 0 || y >= m || w[x][y]) continue;
      w[x][y] = true;
      q.emplace(x, y);
    }
  }
  for (int x = 0; x < n; x++) {
    for (int y = 0; y < m; y++) {
      if (!w[x][y]) return false;
    }
  }
  return true;
}


llu encode() {
  llu r = 0;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      r = r << 1;
      if (field[i][j] && (i != start_x || j != start_y)) r++;
    }
  }
  return r;
}

void dfs(int x0, int y0, check_point target, int t,
  unordered_map<llu, llu>& counts) {
  if (t == target.t) {
    llu e = encode();
    counts[e]++;
    return;
  }
  t++;
  for (int i = 0; i < 4; i++) {
    int x = x0 + dx[i];
    int y = y0 + dy[i];
    // within field
    if (x < 0 || x >= n || y < 0 || y >= m) continue;
    // not visited
    if (field[x][y]) continue;
    // check points met
    int d = abs(target.x - x) + abs(target.y - y);
    int dt = target.t - t;
    if (d == 0 && dt != 0) continue;
    if (d > dt) continue;
    field[x][y] = true;
    if (connected()) {
      dfs(x, y, target, t, counts);
    }
    field[x][y] = false;
  }
}

void travel(int x0, int y0, check_point target, int t,
  unordered_map<llu, llu>& c) {
  fill(&field[0][0], &field[MAX][0], false);
  field[x0][y0] = true;
  start_x = x0; start_y = y0;
  dfs(x0, y0, target, t, c);
}

int main() {
  int tc = 0;
  while (cin >> n >> m, n != 0) {
    check_point points[4];
    for (int i = 0; i < 3; i++) {
      cin >> points[i].x >> points[i].y;
      points[i].t = m * n * (i + 1) / 4;
    }
    points[3].x = 0;
    points[3].y = 1;
    points[3].t = m * n;
    full = 0;
    for (int i = 0; i < n * m; i++) {
      full = (full << 1) + 1;
    }

    unordered_map<llu, llu> p1, p2, p3, p4;
    travel(0, 0, points[0], 1, p1);
    travel(points[0].x, points[0].y, points[1], points[0].t, p2);
    travel(points[1].x, points[1].y, points[2], points[1].t, p3);
    travel(points[2].x, points[2].y, points[3], points[2].t, p4);

    cerr << p1.size() << endl << p2.size() << endl << p3.size() << endl << p4.size() << endl;

    // return 0;

    llu total = 0;
    for (auto a1 : p1) {
      for (auto a2 : p2) {
        if (a1.first & a2.first) continue;
        llu j12 = a1.first | a2.first;
        for (auto a3 : p3) {
          if (a3.first & j12) continue;
          llu j123 = a3.first | j12;
          for (auto a4 : p4) {
            if (a4.first & j123) continue;
            total += a1.second * a2.second * a3.second * a4.second;
          }
        }
      }
    }
    tc++;
    printf("Case %d: %llu\n", tc, total);
  }
}
  // }
