#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ii = pair<int,int>;
using ll = long long;
using llu = unsigned long long;
const int INF = numeric_limits<int>::max();
const int MAX = 20000001;

vi v(MAX), p2(MAX), p5(MAX);

int p(int n, int m) {
  if (n == 0 || m == 0) return 1;
  ll a = 1, t2 = 0, t5 = 0;
  for (int i = n - m + 1; i <= n; i++) {
    a = (a * v[i]) % 10;
    t2 += p2[i];
    t5 += p5[i];
  }
  while (t2 * t5 != 0) { t2--; t5--; }
  //cerr << t << endl;
  if (t2) a *= (2 << ((t2 + 3) % 4));
  if (t5) a *= 5;
  a %= 10;
  return a;
}

int main() {
  ll n, m;
  for (int i = 1; i < MAX; i++) {
    int &t = v[i] = i;
    while (t % 2 == 0) {
      p2[i]++; t /= 2;
    }
    while (t % 5 == 0) {
      p5[i]++; t /= 5;
    }
  }

  while (cin >> n >> m) {
    cout << p(n, m) << endl;
  }
}
