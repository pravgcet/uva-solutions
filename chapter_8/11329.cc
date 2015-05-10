#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ii = pair<int,int>;
using ll = long long;
using llu = unsigned long long;
const int INF = numeric_limits<int>::max();
const int SPACE = 1 << 26;

int D[SPACE];
const int dr[] = {-1, 0, 1, 0};
const int dc[] = {0, -1, 0, 1};
const int rolls[][6] = {
  {3,0,1,2,4,5},
  {5,1,4,3,0,2},
  {1,2,3,0,4,5},
  {4,1,5,3,2,0}};

void jumps(uint& field, int r, int c, uint& dice) {
  int d = dice & 1u;
  int x = r * 4 + c;
  int f = field & (1u << x);
  if (d == f) return;
  dice = dice ^ 1u;
  field = field ^ (1u << x);
}

uint roll(uint dice, int d) {
  uint r = 0;
  for (int i = 0; i < 6; i++) {
    if (dice & (1u << rolls[d][i])) {
      r = r | (1u << i);
    }
  }
  return r;
}

uint encode(uint field, int r, int c, uint dice) {
  return field | (c << 16) | (r << 18) | (dice << 20);
}

tuple<uint, int, int, uint> decode(uint state) {
  return tuple<uint, int, int, uint>(
  state & ((1u << 16) - 1), // field
  (state >> 16) & 3, // c
  (state >> 18) & 3, // r
  state >> 20); // dice
}

int main() {
  int tcc;
  cin >> tcc;
  while (tcc--) {
    fill_n(D, SPACE, INF);
    int dice_r = 0, dice_c = 0;
    uint field = 0;
    for (int r = 0; r < 4; r++) {
      string s;
      cin >> s;
      for (int c = 0; c < 4; c++) {
        switch (s[c]) {
          case 'D': dice_r = r; dice_c = c; break;
          case 'X': uint dice = 1; jumps(field, r, c, dice); break;
        }
      }
    }
    queue<uint> q;
    uint t = encode(field, dice_r, dice_c, 0);
    q.emplace(t);
    D[t] = 0;
    int ans = 0;
    while (!q.empty() && ans == 0) {
      t = q.front(); q.pop();
      auto state = decode(t);
      uint field = get<0>(state);
      int c = get<1>(state);
      int r = get<2>(state);
      uint dice = get<3>(state);
      // printf("%x: field %x dice %x at %d %d\n", t, field, dice, r, c);
      for (int i = 0; i < 4; i++) {
        // cerr << i << endl;
        int r_ = r + dr[i];
        int c_ = c + dc[i];
        if (r_ < 0 || r_ > 3 || c_ < 0 || c_ > 3) continue;
        uint dice_ = roll(dice, i);
        uint field_ = field;
        jumps(field_, r_, c_, dice_);
        uint next = encode(field_, r_, c_, dice_);
        if (D[next] != INF) continue;
        D[next] = D[t] + 1;
        q.emplace(next);
        if (dice_ == ((1u << 6) - 1)) {
          ans = D[next];
          break;
        }
      }
    }
    if (ans == 0) {
      cout << "impossible" << endl;
    } else {
      cout << ans << endl;
    }
  }
}
