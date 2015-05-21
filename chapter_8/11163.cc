#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ii = pair<int,int>;
using ll = long long;
using llu = unsigned long long;
const int INF = numeric_limits<int>::max();
const int MAX = 40;

using vb = vector<int>;
int n;
int formation[MAX]; int king;
int result, back_result;
int bound;
const int MAX_BACK = 10;
ll ops = 0;

const int di[] = {-4, -3, -1, 1, 3, 4};

map<vi, int> distances;

int h() {
  int x = 0;
  for (int i = 1; i <= n; i++) {
    int f = formation[i - 1];
    if (f == 1) continue;
    // if (i + 1 % 4 != f[i] % 4) x++;
    x += abs(i - f) / 4;
    int t = abs((i % 4) - (f % 4));
    switch (t) {
      case 1:
      case 3: x++; break;
      case 2: x += 2; break;
    }
    // if (state[i] == i + 1) continue;
    // x++;// abs(i + 1 - state[i]) / 4;
  }
  return x;
}

int pdh(int i, int j) {
  int f = formation[i] - 1;
  // if (f == 1) return 0;
  // if (i + 1 % 4 != f[i] % 4) x++;
  i = abs(i - f);
  j = abs(j - f);
  int x = j / 4 - i / 4;
  i = i % 4;
  j = j % 4;
  if (i != j) {
    // f = f % 4;
    switch (i) {
      case 1:
      case 3: x--; break;
      case 2: x -= 2; break;
    }
    switch (j) {
      case 1:
      case 3: x++; break;
      case 2: x += 2; break;
    }
  }
  return x;
}

void dfs(int g, int tabu, int hh) {
  // ops++;
  if (hh == 0) {
    result = g;
    return;
  }
  if (g + hh >= bound) return;
  // if (hh <= MAX_BACK) {
  //   auto ff = get_formation();
  //   if (distances.count(ff)) {
  //     back_result = min(back_result, distances[ff] + g);
  //   }
  // }
  g++;
  // vector<ii> v;
  // int m = INF;
  // for (int i = -4; i <= 4; i++) {
  for (int j = 0; j < 6; j++) {
    int i = di[j];
    if (i == tabu) continue;
    int k = king + i;
    if (k < 0 || k >= n) continue;
    if (j > 0 && j < 5 && k / 4 != king / 4) continue;
    // int dh = pdh(k, king);
    swap(formation[k], formation[king]); swap(king, k);
    dfs(g, -i, hh - pdh(k, king));
    swap(formation[k], formation[king]); swap(king, k);
    if (result != INF) return;
  }
}
/*
void fill_back() {
  queue<pair<vi, int>> q;
  q.emplace(formation, 0);
  distances[formation] = 0;
  while (!q.empty()) {
    vi f = q.front().first;
    int d = q.front().second + 1;
    q.pop();
    for (int i = 0; i < n; i++) {
      if (f[i] == 1) {
        king = i;
        break;
      }
    }
    for (int i = -4; i <= 4; i++) {
      if (i == 2 || i == -2 || i == 0) continue;
      int k = king + i;
      if (k < 0 || k >= n) continue;
      if (i < 4 && i > -4) {
        if (k / 4 != king / 4) continue;
      }
      vi a = f;
      swap(a[k], a[king]);
      if (distances.count(a) == 0) {
        distances[a] = d;
        if (d < MAX_BACK) q.emplace(a, d);
      }
    }
  }
}
*/
int ida() {
  bound = h();
  result = INF;
  back_result = INF;
  int hh = bound;
  for (; result == INF; bound++) {
    dfs(0, 0, hh);
    // if (result == INF && back_result != INF) result = back_result;
  }
  // while (result == INF) {
    // cout << ">" << bound << endl;
  // }
  // cout << hh << endl;
  return result;
}

int main() {
  // for (int i = 0; i < MAX; i++) formation[i] = i + 1;
  // king = 0;
  // for (n = 4; n <= MAX; n += 4) {
    // fill_back();
  // }
  // cerr << "OK" << endl;
  // return 0;
  int tc = 0;
  while (cin >> n, n) {
    // formation.resize(n);
    for (int i = 0; i < n; i++) {
      // int a; cin >> a;
      cin >> formation[i];
      if (formation[i] == 1) king = i;
    }
    tc++;
    printf("Set %d:\n%d\n", tc, ida());
  }
  // cerr << ops << " ops" << endl;
}
