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
using vvll = vector<vll>;
const int INF = numeric_limits<int>::max();
const double EPS = 1e-10;

ll gcd(ll a, ll b) {
  while (b) {
    ll t = b;
    b = a % b;
    a = t;
  }
  return a;
}

ll lcm(ll a, ll b) {
  return a * b / gcd(a, b);
}

ll mult_mod(ll a, ll b, ll mod) {
  // a = a % mod;
  // b = b % mod;
  if (a < 100000000 && b < 100000000) return (a * b) % mod;
  ll x = 0;
  // a = a % mod;
  while (b) {
    if (b % 2) x = (x + a) % mod;
    a = (a * 2) % mod;
    b /= 2;
  }
  return x;
}

ll g(ll x, ll n) {
  return (mult_mod(x, x, n) + 1) % n;
}

ll pollard_rho(ll n) {
  // ll i = 1, k = 2;
  // ll x = 2, y = 2;
  ll d = 1;
  vll v;
  v.emplace_back(2);
  ll px = 0;
  while (d == 1) {
    // i++;
    px++;
    // x = g(x, n);
    v.emplace_back(g(v.back(), n));
    v.emplace_back(g(v.back(), n));
    //y = g(g(y, n), n);
    d = gcd(abs(v.back() - v[px]), n); // just mod
  }
  return d;
}

vll primes;

vll factorize_to_primes(ll n) {
  vll factors;
  auto p = primes.begin();
  while (p != primes.end() && (*p) * (*p) <= n) {
    while (n % *p == 0) {
      factors.emplace_back(*p);
      n /= *p;
    }
    p++;
  }
  if (n != 1) factors.emplace_back(n);
  return factors;
}

vll probablity_factorization(ll n) {
  vll factors = factorize_to_primes(n);
  n = factors.back(); factors.pop_back();
  ll f = pollard_rho(n);
  // ll f = n;
  // auto s = factorize_to_primes(f);
  factors.emplace_back(f);
  n /= f;
  if (n != 1) factors.emplace_back(n);
  return factors;
}

const ll MAX_PRIME = 1000000;
vll sieve_primes() {
  bitset<MAX_PRIME + 1> b;
  vll primes;
  primes.emplace_back(2);
  for (ll i = 3; i <= MAX_PRIME; i += 2) {
    if (b[i]) continue;
    primes.emplace_back(i);
    for (ll j = i * i; j <= MAX_PRIME; j += i) b.set(j);
  }
  return primes;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  primes = sieve_primes();
  int tcc; cin >> tcc;
  for (int tc = 1; tc <= tcc; tc++) {
    ll n; cin >> n;
    cout << n << " = ";
    auto factors = probablity_factorization(n);
    sort(factors.begin(), factors.end());
    ll f = 0, c = 0;
    for (auto k : factors) {
      if (k == f) { c++; continue; }
      if (f != 0) {
        cout << f;
        if (c > 1) cout << '^' << c;
        cout << " * ";
      }
      c = 1;
      f = k;
    }
    cout << f;
    if (c > 1) cout << '^' << c;
    cout << endl;
  }
}
