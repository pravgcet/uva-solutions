#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>; using vvi = vector<vi>;
using ii = pair<int,int>; using vii = vector<ii>;
using l = long long; using vl = vector<l>; using vvl = vector<vl>;
using ll = pair<l,l>; using vll = vector<ll>; using vvll = vector<vll>;
using lu = unsigned long long;
using vb = vector<bool>; using vvb = vector<vb>;
using vd = vector<double>; using vvd = vector<vd>;
const int INF = numeric_limits<int>::max();
const double EPS = 1e-10;
const l e5 = 100000, e6 = 1000000, e7 = 10000000, e9 = 1000000000;

struct bigint {
  // base and base_digits must be consistent
  l sign = 1;
  static const l shift = 30;
  static const l mask = (1LL << shift) - 1;
  l base = 1LL << shift;
  static const l base_digits = 9;
  vector<l> a;

  bigint() {}

  explicit bigint(long long v) { *this = v; }

  explicit bigint(const string &s) { read(s); }

  void operator=(const bigint &v) {
    base = v.base;
    sign = v.sign;
    a = v.a;
  }

  void operator=(long long v) {
    sign = 1;
    if (v < 0) sign = -1, v = -v;
    for (; v > 0; v = v / base) a.push_back(v % base);
  }

  bigint operator+(const bigint &v) const {
    if (sign == v.sign) {
      bigint res = v;

      for (l i = 0, carry = 0; i < (l)max(a.size(), v.a.size()) || carry;
           ++i) {
        if (i == (l)res.a.size()) res.a.push_back(0);
        res.a[i] += carry + (i < (l)a.size() ? a[i] : 0);
        carry = res.a[i] >= base;
        if (carry) res.a[i] -= base;
      }
      return res;
    }
    return *this - (-v);
  }

  bigint operator-(const bigint &v) const {
    if (sign == v.sign) {
      if (abs() >= v.abs()) {
        bigint res = *this;
        for (l i = 0, carry = 0; i < (l)v.a.size() || carry; ++i) {
          res.a[i] -= carry + (i < (l)v.a.size() ? v.a[i] : 0);
          carry = res.a[i] < 0;
          if (carry) res.a[i] += base;
        }
        // res.trim();
        return res;
      }
      return -(v - *this);
    }
    return *this + (-v);
  }

  void operator*=(l v) {
    if (v < 0) sign = -sign, v = -v;
    for (l i = 0, carry = 0; i < (l)a.size() || carry; ++i) {
      if (i == (l)a.size()) a.push_back(0);
      long long cur = a[i] * (long long)v + carry;
      carry = (l)(cur / base);
      a[i] = (l)(cur % base);
    }
    trim();
  }

  bigint operator*(l v) const {
    bigint res = *this;
    res *= v;
    return res;
  }

  friend pair<bigint, bigint> divmod(const bigint &a1, const bigint &b1) {
    auto base = a1.base;
    l norm = base / (b1.a.back() + 1);
    bigint a = a1.abs() * norm;
    bigint b = b1.abs() * norm;
    bigint q, r;
    q.a.resize(a.a.size());

    for (l i = a.a.size() - 1; i >= 0; i--) {
      r *= base;
      r += bigint(a.a[i]);
      l s1 = r.a.size() <= b.a.size() ? 0 : r.a[b.a.size()];
      l s2 = r.a.size() <= b.a.size() - 1 ? 0 : r.a[b.a.size() - 1];
      l d = ((long long)base * s1 + s2) / b.a.back();
      r -= b * d;
      while (r < bigint(0)) r += b, --d;
      q.a[i] = d;
    }

    q.sign = a1.sign * b1.sign;
    r.sign = a1.sign;
    q.trim();
    r.trim();
    return make_pair(q, r / norm);
  }

  bigint operator/(const bigint &v) const { return divmod(*this, v).first; }

  bigint operator%(const bigint &v) const { return divmod(*this, v).second; }

  void operator/=(l v) {
    if (v < 0) sign = -sign, v = -v;
    for (l i = (l)a.size() - 1, rem = 0; i >= 0; --i) {
      l cur = a[i] + rem * base;
      a[i] = (cur / v);
      rem = (cur % v);
    }
    trim();
  }

  bigint operator/(l v) const {
    bigint res = *this;
    res /= v;
    return res;
  }

  l operator%(l v) const {
    if (v < 0) v = -v;
    l m = 0;
    for (l i = a.size() - 1; i >= 0; --i)
      m = (a[i] + m * (long long)base) % v;
    return m * sign;
  }

  void operator+=(const bigint &v) { *this = *this + v; }
  void operator-=(const bigint &v) { *this = *this - v; }
  void operator*=(const bigint &v) { *this = *this *v; }
  void operator/=(const bigint &v) { *this = *this / v; }

  bool operator<(const bigint &v) const {
    if (sign != v.sign) return sign < v.sign;
    if (a.size() != v.a.size()) return a.size() * sign < v.a.size() * v.sign;
    for (l i = a.size() - 1; i >= 0; i--)
      if (a[i] != v.a[i]) return a[i] * sign < v.a[i] * sign;
    return false;
  }

  bool operator>(const bigint &v) const { return v < *this; }
  bool operator<=(const bigint &v) const { return !(v < *this); }
  bool operator>=(const bigint &v) const { return !(*this < v); }
  bool operator==(const bigint &v) const {
    return !(*this < v) && !(v < *this);
  }
  bool operator!=(const bigint &v) const { return *this < v || v < *this; }

  void trim() {
    while (!a.empty() && !a.back()) a.pop_back();
    if (a.empty()) sign = 1;
  }

  void normalize(const size_t from) {
    l c = 0;
    for (size_t i = from; i < a.size(); i++) {
      a[i] += c;
      c = a[i] >> shift;
      a[i] = a[i] & mask;
    }
    while (c) {
      a.push_back(c & mask);
      c = c >> shift;
    }
  }

  bool isZero() const { return a.empty() || (a.size() == 1 && !a[0]); }

  bigint operator-() const {
    bigint res = *this;
    res.sign = -sign;
    return res;
  }

  bigint abs() const {
    bigint res = *this;
    res.sign *= res.sign;
    return res;
  }

  long long longValue() const {
    long long res = 0;
    for (l i = a.size() - 1; i >= 0; i--) res = res * base + a[i];
    return res * sign;
  }

  friend bigint gcd(const bigint &a, const bigint &b) {
    return b.isZero() ? a : gcd(b, a % b);
  }
  friend bigint lcm(const bigint &a, const bigint &b) {
    return a / gcd(a, b) * b;
  }

  void read(const string &s) {
    sign = 1;
    vl ta;
    ta.clear();
    l pos = 0;
    while (pos < (l)s.size() && (s[pos] == '-' || s[pos] == '+')) {
      if (s[pos] == '-') sign = -sign;
      ++pos;
    }
    for (l i = s.size() - 1; i >= pos; i -= base_digits) {
      l x = 0;
      for (l j = max(pos, i - base_digits + 1); j <= i; j++)
        x = x * 10 + s[j] - '0';
      ta.push_back(x);
    }
    from_base10(ta);
  }

  friend istream &operator>>(istream &stream, bigint &v) {
    string s;
    stream >> s;
    v.read(s);
    return stream;
  }

  friend ostream &operator<<(ostream &stream, const bigint &v) {
    if (v.sign == -1) stream << '-';
    auto ta = v.to_base10();
    stream << (ta.empty() ? 0 : ta.back());
    for (l i = (l)ta.size() - 2; i >= 0; --i)
      stream << setw(base_digits) << setfill('0') << ta[i];
    return stream;
  }

  static vl convert_base(const vector<l> &a, l old_digits,
                                  l new_digits) {
    vl p(max(old_digits, new_digits) + 1);
    p[0] = 1;
    for (l i = 1; i < (l)p.size(); i++) p[i] = p[i - 1] * 10;
    vl res;
    long long cur = 0;
    l cur_digits = 0;
    for (l i = 0; i < (l)a.size(); i++) {
      cur += a[i] * p[cur_digits];
      cur_digits += old_digits;
      while (cur_digits >= new_digits) {
        res.push_back(l(cur % p[new_digits]));
        cur /= p[new_digits];
        cur_digits -= new_digits;
      }
    }
    res.push_back((l)cur);
    while (!res.empty() && !res.back()) res.pop_back();
    return res;
  }

  static vl karatsubaMultiply(const vl &a, const vl &b) {
    l n = a.size();
    vl res(n + n);
    if (n <= 64) {
      for (l i = 0; i < n; i++)
        for (l j = 0; j < n; j++) res[i + j] += a[i] * b[j];
      return res;
    }

    l k = n >> 1;
    vl a1(a.begin(), a.begin() + k);
    vl a2(a.begin() + k, a.end());
    vl b1(b.begin(), b.begin() + k);
    vl b2(b.begin() + k, b.end());

    vl a1b1 = karatsubaMultiply(a1, b1);
    vl a2b2 = karatsubaMultiply(a2, b2);

    for (l i = 0; i < k; i++) a2[i] += a1[i];
    for (l i = 0; i < k; i++) b2[i] += b1[i];

    vl r = karatsubaMultiply(a2, b2);
    for (l i = 0; i < (l)a1b1.size(); i++) r[i] -= a1b1[i];
    for (l i = 0; i < (l)a2b2.size(); i++) r[i] -= a2b2[i];

    for (l i = 0; i < (l)r.size(); i++) res[i + k] += r[i];
    for (l i = 0; i < (l)a1b1.size(); i++) res[i] += a1b1[i];
    for (l i = 0; i < (l)a2b2.size(); i++) res[i + n] += a2b2[i];
    return res;
  }

  bigint operator*(const bigint &v) const {
    vl a = this->a;
    vl b = v.a;
    while (a.size() < b.size()) a.push_back(0);
    while (b.size() < a.size()) b.push_back(0);
    while (a.size() & (a.size() - 1)) a.push_back(0), b.push_back(0);
    vl c = karatsubaMultiply(a, b);
    bigint res;
    res.sign = sign * v.sign;
    for (l i = 0, carry = 0; i < (l)c.size(); i++) {
      l cur = c[i] + carry;
      res.a.push_back((l)(cur % base));
      carry = (l)(cur / base);
    }
    res.trim();
    return res;
  }

  static vl karatsubaSquare(const vl &a) {
    l n = a.size();
    vl res(n + n);
    if (n <= 32) {
      for (l i = 0; i < n; i++)
        for (l j = 0; j < n; j++) res[i + j] += a[i] * a[j];
      return res;
    }

    l k = n >> 1;
    vl a1(a.begin(), a.begin() + k);
    vl a2(a.begin() + k, a.end());

    vl a1b1 = karatsubaSquare(a1);
    vl a2b2 = karatsubaSquare(a2);

    for (l i = 0; i < k; i++) a2[i] += a1[i];

    vl r = karatsubaSquare(a2);
    l z = (l)a1b1.size();
    for (l i = 0; i < z; i++) r[i] -= a1b1[i];
    z = (l)a2b2.size();
    for (l i = 0; i < z; i++) r[i] -= a2b2[i];
    z = (l)r.size();
    for (l i = 0; i < z; i++) res[i + k] += r[i];
    z = (l)a1b1.size();
    for (l i = 0; i < z; i++) res[i] += a1b1[i];
    z = (l)a2b2.size();
    for (l i = 0; i < z; i++) res[i + n] += a2b2[i];
    return res;
  }

  void from_base10(vl& b) {
    bigint y(1);
    for (auto i : b) {
      *this += y * i;
      y *= e9;
    }
    normalize(0);
  }

  static void normalize10(vl& a) {
    l c = 0;
    for (auto &i : a) {
      i += c;
      c = i / e9;
      i %= e9;
    }
    while (c) {
      a.push_back(c % e9);
      c /= e9;
    }
    while (!a.empty() && a.back() == 0) a.pop_back();
  }

  static vl mult(vl& a, l b) {
    vl c;
    for (auto i : a) c.push_back(i * b);
    normalize10(c);
    return c;
  }

  static void add_to(vl& a, vl& b) {
    size_t s = max(a.size(), b.size());
    a.resize(s);
    b.resize(s);
    for (size_t i = 0; i < s; i++) a[i] += b[i];
    normalize10(a);
  }

  vl to_base10() const {
    vl y;
    y.push_back(1);
    vl result;
    for (auto i : a) {
      auto t = mult(y, i);
      add_to(result, t);
      y = mult(y, base);
    }
    normalize10(result);
    return result;
  }

  void debug(ostream& s) {
    s << "base = " << base << endl;
    s << a.size() << " buckets" << endl;
    for (auto i : a) s << i << " ";
    s << endl;
  }
};

const string AZ = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const string az = "abcdefghijklmnopqrstuvwxyz";
const string d09 = "0123456789";
const string d19 = "123456789";

default_random_engine source(random_device{}());

l random_in_range(l a, l b) {
  return uniform_int_distribution<l>(a, b)(source);
}

bool random_bool() {
  return random_in_range(0, 1) == 1;
}

string random_string(int length, string source) {
  string s = "";
  for (int i = 0; i < length; i++) {
    s += source[random_in_range(0, source.size() - 1)];
  }
  return s;
}

//#define TEST

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
#if defined(TEST)
  l resizes = 0;
  for (l ii = 0 ; ii < 100000; ii++) {
    l length = random_in_range(1, 50);
    auto s = random_string(1, d19) + random_string(length - 1, d09);
    bigint r(s);
    bigint A = r * r;
    A.normalize(0);
    A.trim();
#else
  l tcc; cin >> tcc;
  while (tcc--) {
    bigint A;
    cin >> A;
#endif
    l k = (A.a.size() + 1) / 2;
    while (2 * k + 1 > A.a.size()) k--;
    l sv = A.shift;
    bigint x(0);
    bigint d2 = A;
    bigint p;
    p.a.resize(d2.a.size() + 2);
    d2.a.resize(d2.a.size() + 2);
    while (true) {
      fill(&(p.a[0]), &(p.a[p.a.size()]), 0);
      l t = max(2 * k + 1, k + (l)x.a.size());
      if (t <= A.a.size()) {
        //y2.a = x2.a;
        // assert(v > 0);
        // y2.a.resize(max((l)y2.a.size(), max(2 * k + 1, k + (l)x.a.size())));
        for (size_t i = 0; i < x.a.size(); i++) {
          p.a[i + k] += x.a[i] << (sv + 1);
        }
        p.a[2 * k] += 1LL << (sv + sv);
        p.normalize(k);
      }
      // cerr << t << ", " << p << " <> " << d2 << endl;
      if (t > A.a.size() || p > d2) {
        // cerr << "skip" << endl;
        // p.debug(cerr);
        // d2.debug(cerr);
        if (sv == 0) {
          if (k == 0) break;
          k--;
          // v = A.base;
          sv = A.shift;
        }
        // v /= 2;
        sv--;
        continue;
      }
      // cout << "+" << endl;
      if (k + 1 > x.a.size()) {
        x.a.resize(k + 1);
      }
      x.a[k] += (1LL << sv);
      x.normalize(k);
      //swap(x2.a, y2.a);
      if (d2 == p) break;
      d2 -= p;
      // d2.a.resize(p.a.size());
      assert(d2.sign == 1);
    }
#if defined(TEST)
    auto g = x * x;
    g.normalize(0);
    if (g != A) {
      g.debug(cout);
      A.debug(cout);
      cout << x << " * " << x << " = " << (x * x) << " != " << A << endl;
      break;
    }
#else
    cout << x << endl;
    if (tcc) cout << endl;
#endif
  }
}
