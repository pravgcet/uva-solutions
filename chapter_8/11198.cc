#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ii = pair<int,int>;
using ll = long long;
using llu = unsigned long long;
const int INF = numeric_limits<int>::max();

bitset<20> primes;

struct State;

struct State {
  list<int> digits;
  int distance;
  friend ostream& operator << (ostream& stream, const State& s);
};

const uint encode(const State s) {
  uint c = 0;
  for (int i = 0; i < 8; i++) {
    if (s.digits[i] < 0) c++;
    c <<= 1;
  }
  c <<= 2;
  for (int i = 0; i < 8; i++) {
    if (i) c <<= 3;
    c += abs(s.digits[i]);
  }
  return c;
}

ostream& operator << (ostream& stream, const State& s) {
  for (int i = 0; i < 8; i++) stream << s.digits[i] << " ";
  stream << "= " << hex <<  encode(s) << dec;
  return stream;
}


bool fit(const int a, const int b) {
  return (a * b < 0) && primes[abs(a - b)];
}

int main() {
  primes.set(3);
  primes.set(5);
  primes.set(7);
  primes.set(11);
  primes.set(13);

  State target;
  for (int i = 0; i < 8; i++) target.digits[i] = i + 1;
  uint key = encode(target);

  // for (uint i = 0; i < (1u << 8); i++) {
  //   State s;
  //   for (int j = 0; j < 8; j++) {
  //     s.digits[j] = j + 1;
  //     if (i & (1u << j)) s.digits[j] = -s.digits[j];
  //   }
  //   // distance[encode(s)] = s.distance = 0;
  //   // q.emplace(s);
  //   cerr << s << endl;
  // }

  // return 0;

  for (int tc = 1;; tc++) {
    State s;
    for (int i = 0; i < 8; i++) {
      cin >> s.digits[i];
      if (s.digits[i] == 0) goto BYE;
    }
    queue<State> q;
    q.emplace(s);
    set<uint> queued;
    queued.insert(encode(s));
    int ans = -1;
    while (!q.empty()) {
      State s = q.front(); q.pop();
      cerr << s << endl;
      for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
          if (j == i) continue;
          if (!fit(s.digits[i], s.digits[j])) continue;
          State n = s;
          n.move(i, j);
          auto c = encode(n);
          i0f (queued.count(c)) continue;
          if ((key & c) == key) {
             ans = n.distance;
             goto FOUND;
          }
          queued.insert(c);
          q.emplace(n);
          cerr << "+ " << n << endl;
          State n = s;
          n.move(i, j + 1);
          auto c = encode(n);
          if ((key & c) == key) {
             ans = n.distance;
             goto FOUND;
          }
          if (queued.count(c)) continue;
          queued.insert(c);
          q.emplace(n);
          cerr << "+ " << n << endl;
        }
      }
    }
FOUND:
    // if (distance.count(c)) ans = distance[c];
    printf("Case %d: %d\n", tc, ans);
  }
BYE:
  return 0;
}

