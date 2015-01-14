#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ii = pair<int,int>;
using ivi = vi::iterator;
using ll = long long;
using llu = unsigned long long;
const int INF = numeric_limits<int>::max();

vi primes;
int best_c, best_n;

void sieve() {
  bitset<40000> b;
  primes.emplace_back(2);
  for (ll i = 3; i < b.size(); i += 2) {
    if (b[i]) continue;
    primes.emplace_back(i);
    for (ll j = i * i; j < b.size(); j += i) b.set(j);
  }
}

void check(int f, int t, ivi p, int n, int c) {
  //cerr << f << " " << t << " " << *p << " " << n << " " << c << endl;
  if (t == 1) {
    if (c > best_c || (c == best_c && n < best_n)) {
      best_c = c;
      best_n = n;
    }
    return;
  }
  if (p == primes.end() || *p > t) {
    if (f == 1) {
      check(1, 1, p, n, c);
    } else {
      check(1, 1, p, f * n, c + 1);
    }
    return;
  }
  int a = 0;
  while (true) {
    check(f, t, p + 1, n, c * (a + 1));
    n *= (*p);
    a++;
    if (f == t && t % (*p) != 0) break;
    f = (f + (*p) - 1) / (*p);
    t = t / (*p);
    if (f > t) break;
  }
}

int main() {
  sieve();
  int tcc;
  cin >> tcc;
  while (tcc--) {
    best_c = 0;
    best_n = 0;
    int f, t;
    cin >> f >> t;
    check(f, t, primes.begin(), 1, 1);
    printf("Between %d and %d, %d has a maximum of %d divisors.\n", f, t, best_n, best_c);
  }
}
