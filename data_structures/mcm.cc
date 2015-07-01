// sudo apt-get install graphviz
//./mcm | dot -Tpng >mcm.png

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

const int MAX_SIZE = 10;

struct node;
struct edge;
using pnode = shared_ptr<node>;
using pedge = shared_ptr<edge>;
using graph = vector<pnode>;

struct node {
  ll id;
  bool visited;
  vector<pedge> adjusted;
  pedge back;
  vector<pedge> out() {
    return adjusted;
  }
};

struct edge {
  pnode _to;
  pedge opposite;
  pnode to() {
    return _to;
  }
  pnode from() { return opposite->to(); }
  bool matched;
  void match(bool v) {
    matched = v;
    opposite->matched = v;
  }
};

void connect(pnode &a, pnode &b) {
  pedge ea = make_shared<edge>();
  pedge eb = make_shared<edge>();
  ea->_to = b; ea->opposite = eb;
  eb->_to = a; eb->opposite = ea;
  a->adjusted.emplace_back(ea);
  b->adjusted.emplace_back(eb);
}

default_random_engine source(random_device{}());

ll random_int(ll a, ll b) {
  return uniform_int_distribution<ll>(a, b)(source);
}

double random_double(double a, double b) {
  return uniform_real_distribution<double>(a, b)(source);
}

bool random_bool() {
  return random_int(0, 1) == 1;
}

string random_string(int length) {
  string s = "";
  string an = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
  for (int i = 0; i < length; i++) {
    s += an[random_int(0, an.size() - 1)];
  }
  return s;
}

graph random_graph() {
  double connectivity = random_double(0, 1);
  ll size = random_int(1, MAX_SIZE);
  graph g(size);
  for (ll i = 0; i < size; i++) {
    g[i] = make_shared<node>();
    g[i]->id = i;
  }
  for (ll i = 0; i < size; i++) {
    for (ll j = i + 1; j < size; j++) {
      if (random_double(0, 1) > connectivity) continue;
      connect(g[i], g[j]);
    }
  }
  return g;
}

// output graph in graphviz format
ostream& print_graph(ostream& s, graph& g) {
  s << "graph {";
  for (auto u : g) {
    for (auto e : u->out()) {
      auto v = e->to();
      if (v->id < u->id) continue;
      s << u->id << " -- " << v->id;
      if (e->matched) s << " [style=bold,color=red]";
      s << ";" << endl;
    }
  }
  s << "}";
  return s;
}

pair<ll, pedge> dp(graph& g, llu mask, map<llu, pair<ll, pedge>>& memo) {
  if (memo.count(mask)) {
    return memo[mask];
  }
  memo[mask].first = 0;
  memo[mask].second = NULL;
  if (mask == 0) return memo[mask];
  ll i = 0;
  auto t = mask;
  while ((t & (1ull << i)) == 0) i++;
  t = t ^ (1ull << i);
  memo[mask] = dp(g, t, memo); // don't take
  for (auto e : g[i]->out()) {
    ll j = e->to()->id;
    if ((t & (1ull << j)) == 0) continue;
    auto c = dp(g, t ^ (1ull << j), memo);
    c.first++;
    c.second = e;
    if (c.first > memo[mask].first) memo[mask] = c;
  }
  return memo[mask];
}

ll max_dp_matching(graph& g) {
  llu mask = (1ull << g.size()) - 1;
  map<llu, pair<ll, pedge>> memo;
  auto r = dp(g, mask, memo);
  while (true) {
    auto p = dp(g, mask, memo);
    if (!p.second) break;
    p.second->match(true);
    mask = mask ^ (1ull << p.second->to()->id);
    mask = mask ^ (1ull << p.second->from()->id);
  }
  return r.first;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  auto g = random_graph();
  cerr << max_dp_matching(g);
  print_graph(cout, g) << endl;
}
