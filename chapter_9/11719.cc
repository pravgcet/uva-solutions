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
const int INF = numeric_limits<int>::max();
const double EPS = 1e-10;

const ll MOD = 10000000000000007;

struct bigint {
  static const ll BUCKET = 100;
  static const int BUCKET_DIGITS = 2;
  vll buckets;
  // constructors
  bigint() {};
  bigint(ll a) {
    buckets.emplace_back(a);
    normalize();
  }
  bigint(const bigint& n) { buckets = n.buckets; }
  bigint(bigint&& n) : bigint() { swap(*this, n); }
  friend void swap(bigint& first, bigint& second) {
    swap(first.buckets, second.buckets);
  }
  // assignment
  bigint& operator = (ll a) {
    buckets.clear();
    buckets.emplace_back(a);
    normalize();
    return *this;
  }
  bigint& operator = (bigint rhs) {
    swap(*this, rhs);
    return *this;
  }
  // utility
  void normalize() {
    size_t i = 0;
    while (i < buckets.size()) {
      ll t = buckets[i] / BUCKET;
      if (t) {
        if (i + 1 == buckets.size()) buckets.resize(i + 2);
        buckets[i + 1] += t;
        buckets[i] %= BUCKET;
      }
      i++;
    }
  }
  size_t size() {
    if (buckets.empty()) return 0;
    size_t r = BUCKET_DIGITS * (buckets.size() - 1) + 1;
    ll b = buckets.back();
    while (b >= 10) {
      r++;
      b /= 10;
    }
    return r;
  }
  friend ostream& operator << (ostream& s, bigint& n) {
    for (auto i = n.buckets.rbegin(); i != n.buckets.rend(); i++) {
      s << *i << setw(BUCKET_DIGITS) << setfill('0');
    }
    s << setw(0);
    return s;
  }
  // +
  friend bigint operator + (bigint lhs, const bigint &rhs) {
    lhs += rhs;
    return lhs;
  }
  bigint& operator += (const bigint& rhs) {
    size_t n = rhs.buckets.size();
    if (n > buckets.size()) buckets.resize(n);
    for (size_t i = 0; i < min(buckets.size(), n); i++) {
      buckets[i] += rhs.buckets[i];
    }
    normalize();
    return *this;
  }
  bigint& operator += (const ll n) {
    buckets[0] += n;
    normalize();
    return *this;
  }
  friend bigint operator + (bigint lhs, const ll &rhs) {
    lhs += rhs;
    return lhs;
  }
  // *
  bigint& operator *= (const ll n) {
    for (size_t i = 0; i < buckets.size(); i++) {
      buckets[i] *= n;
    }
    normalize();
    return *this;
  }
  friend bigint operator * (bigint lhs, const ll &rhs) {
    lhs *= rhs;
    return lhs;
  }
  bigint& operator *= (const bigint& rhs) {
    bigint c = *this;
    buckets.clear();
    for (size_t i = 0; i < rhs.buckets.size(); i++) {
      *this += (c * rhs.buckets[i]);
      normalize();
      c.buckets.insert(c.buckets.begin(), 0);
    }
    return *this;
  }
  friend bigint operator * (bigint lhs, const bigint &rhs) {
    lhs *= rhs;
    return lhs;
  }
  friend ll mod(const bigint& lhs, const ll mod) {
    ll r = 0;
    for (auto i = lhs.buckets.rbegin(); i != lhs.buckets.rend(); i++) {
      r = (r * BUCKET + *i) % mod;
    }
    return r;
  }
};


bigint power(const bigint& base, const ll p) {
  if (p == 1) return base;
  bigint t = power(base, p / 2);
  auto a = t;
  a = mod(a * t, MOD);
  if (p % 2 == 1) a = mod(a * base, MOD);
  return a;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  int tcc; cin >> tcc;
  for (int tc = 1; tc <= tcc; tc++) {
    ll r, c;
    cin >> r >> c;
    ll p = (r * c) / 2;
    ll q = r * c - p;
    bigint answer = power(bigint(p), q - 1);
    answer = mod(answer * power(bigint(q), p - 1), MOD);
    cout << answer << endl;
  }
}
