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
  ll i = 0, k = 2;
  ll x = 3, y = 3;
  ll d = 1;
  while (d == 1) {
    i++;
    x = g(x, n);
    d = gcd(abs(x - y), n);
    if (i == k) { y = x; k *= 2; }
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


default_random_engine source(random_device{}());

ll random_in_range(ll a, ll b) {
  return uniform_int_distribution<ll>(a, b)(source);
}

bool random_bool() {
  return random_in_range(0, 1) == 1;
}

string random_string(int length) {
  string s = "";
  string an = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
  for (int i = 0; i < length; i++) {
    s += an[random_in_range(0, an.size() - 1)];
  }
  return s;
}

bool complex_test(ll a, ll n) {
  ll c = n - 1;
  ll m = 1;
  ll k = 0;
  while (c >= m) {
    k++;
    m <<= 1;
  }
  m >>= 1;
  ll d = 1;
  for (ll i = 0; i < k; i++) {
    ll x = d;
    d = mult_mod(d, d, n);
    if (d == 1 && x != 1 && x != n - 1) return true;
    if (c & m) d = mult_mod(d, a, n);
    m >>= 1;
  }
  return (d != 1);
}

bool primality_test(ll n, ll trials) {
  for (ll i = 0; i < trials; i++) {
    ll a = random_in_range(2, n - 1);
    if (complex_test(a, n)) return false;
  }
  return true;
}

vll probablity_factorization(ll n) {
  vll factors = factorize_to_primes(n);
  n = factors.back(); factors.pop_back();
  if (!primality_test(n, 3)) {
    ll f = pollard_rho(n);
    factors.emplace_back(f);
    n /= f;
  }
  if (n != 1) factors.emplace_back(n);
  return factors;
}

const ll MAX_PRIME = 100000;
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
