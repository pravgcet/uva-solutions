#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ii = pair<int,int>;
using ll = long long;
using llu = unsigned long long;
const int INF = numeric_limits<int>::max();
const int MAX = 41;

using vb = vector<int>;
int n;
int formation[MAX]; int king;
int result, back_result;
int bound;
const int MAX_BACK = 10;
ll ops = 0;

const int di[] = {-4, -3, -1, 1, 3, 4};

int ht[MAX][MAX];

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

void dfs(int g, int tabu, int hh) {
  // ops++;
  if (hh == 0) {
    result = g;
    return;
  }
  if (g + hh > bound) return;
  g++;
  for (int j = 0; j < 6; j++) {
    int i = di[j];
    if (i == tabu) continue;
    int k = king + i;
    if (k < 0 || k >= n) continue;
    if (j > 0 && j < 5 && k / 4 != king / 4) continue;
    int dh = ht[k][formation[k]];
    swap(formation[k], formation[king]); swap(king, k);
    dfs(g, -i, hh - dh + ht[k][formation[k]]);
    swap(formation[k], formation[king]); swap(king, k);
    if (result != INF) return;
  }
}

int ida() {
  bound = h();
  result = INF;
  int hh = bound;
  for (; result == INF; bound++) {
    dfs(0, 0, hh);
  }
  return result;
}

int main() {
  for (int i = 0; i < 40; i++) {
    for (int f = 2; f <= 40; f++) {
      int& x = ht[i][f];
      x = 0;
      int d = abs(i - f + 1);
      x += d / 4;
      switch (d % 4) {
        case 1:
        case 3: x++; break;
        case 2: x += 2; break;
      }
    }
  }

  int tc = 0;
  while (cin >> n, n) {
    for (int i = 0; i < n; i++) {
      cin >> formation[i];
      if (formation[i] == 1) king = i;
    }
    tc++;
    printf("Set %d:\n%d\n", tc, ida());
  }
  // cerr << ops << " ops" << endl;
}
