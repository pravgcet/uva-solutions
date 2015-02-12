#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ii = pair<int,int>;
using ll = long long;
using llu = unsigned long long;
const int INF = numeric_limits<int>::max();

const int MAX = 110;

int main() {
  int m, n;
  int f[MAX][MAX];
  while (cin >> m, m) {
    cin >> n;
    string s;
    for (int i = 0; i < m; i++) {
      cin >> s;
      for (int j = 0; j < n; j++) {
        f[i][j] = s[j] == '*' ? 0 : 1;
      }
    }
    int c = 0;
    for (int i = 0; i < m; i++) {
      for (int j = 0; j < n; j++) {
        if (f[i][j] == 0) continue;
        queue<ii> q;
        q.emplace(i, j);
        while (q.empty())
      }
    }
  }
}
