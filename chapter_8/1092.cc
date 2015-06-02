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

class intervals {
private:
  struct intervals_key {
    bool operator() (const ii& a, const ii& b) {
      return a.second < b.first;
   };
  };
  map<ii, int, intervals_key> m;
public:
  void add(int a, int b) {
    m.emplace(make_pair(a, b), 0);
  }

  void remove(int a, int b) {
    //
  }

  vii find(int a, int b) {
    vii r;
    auto p = m.equal_range(make_pair(a, b));
    for (auto i = p.first; i != p.second; i++) r.emplace_back(i->first);
    return r;
  }
};

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  intervals w;
  w.add(1, 3);
  w.add(4, 6);
  w.add(8, 10);
  auto v = w.find(2, 3);
  for (auto i : v) cout << i.first << " " << i.second << endl;
}
