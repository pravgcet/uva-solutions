#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ii = pair<int,int>;
using ll = long long;
using llu = unsigned long long;
const int INF = numeric_limits<int>::max();

int main() {
  int n;
  while (cin >> n, n) {
    bitset<100> b;
    for (int i = 1; ; i++) {
      cerr << i << endl;
      b.reset();
      int s = 0;
      int p = 0;
      while (true) {
        while (b[p]) {
          p++; p %= n;
        }
        b[p] = true;
        s++;
        if (p == 12) break;
        for (int j = 0; j < i; j++) {
          while (b[p]) { p++; p %= n; }
        }
      }
      if (s == n) {
        cout << i << endl;
        break;
      }
    }
  }
}
