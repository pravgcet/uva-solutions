#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ii = pair<int,int>;
using ll = long long;
using llu = unsigned long long;
const int INF = numeric_limits<int>::max();

// move
llu edit(llu n, int a, int b, int k, int m) {
  llu r = 0;
  int t = 0;
  int p = 0;
  if (k >= a) k++;
  llu mult = 1;
  llu q = n;
  while (t < m) {
    if (t == k) {
      llu cut = n;
      int i = 0;
      for (; i < a; i++) cut /= 10;
      for (; i < b; i++) {
        r += mult * (cut % 10);
        mult *= 10;
        cut /= 10;
        t++;
      }
      continue;
    }
    if (p >= a && p < b) { q /= 10; p++; continue; }
    r += mult * (q % 10);
    mult *= 10;
    q /= 10;
    p++;
    t++;
  }
  return r;
}

int main() {
  llu n = 7654321;
  cerr << edit(n, 2, 4, 0, 7) << endl;
  cerr << edit(n, 2, 3, 0, 7) << endl;
  cerr << edit(n, 2, 4, 1, 7) << endl;
  cerr << edit(n, 2, 4, 2, 7) << endl;
  cerr << edit(n, 2, 4, 3, 7) << endl;
  cerr << edit(n, 2, 4, 4, 7) << endl;
  cerr << edit(n, 0, 1, 0, 7) << endl;
}
