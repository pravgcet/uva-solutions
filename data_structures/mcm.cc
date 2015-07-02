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

struct edge {
  pnode _to;
  pedge opposite;
  bool matched, visited;

  pnode to();
  pnode from() { return opposite->to(); }
  void match(bool v) {
    matched = v;
    opposite->matched = v;
  }
};

struct node {
  ll id, age, tree_no, blossom_id;
  bool visited, exposed;
  vector<pedge> adjusted;
  pedge back;
  pnode up;
  vector<pnode> down;
  vector<pedge> out() {
    //TODO we can cache this
    if (down.empty()) return adjusted;
    vector<pedge> o;
    for (auto u : down) {
      for (auto e : u->out()) {
        auto v = e->to();
        auto r = e->from();
        if (v == r) continue;
        o.emplace_back(e);
      }
    }
    return o;
  };
  void reset() {
    age = 0;
    tree_no = 0;
    back = NULL;
    up = NULL;
    down.clear();
    visited = false;
    for (auto e : adjusted) e->matched = false;
  }
  vector<pedge> path_to_root() {
    if (!back) return vector<pedge>();
    auto p = back->from()->path_to_root();
    p.emplace_back(back);
    return p;
  }
};

pnode edge::to() {
  auto t = _to;
  while (t->up) t = t->up;
  return t;
}

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
  for (auto u : g) u->reset();
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

vector<pedge> find_augmenting_path(graph& g);
ll _blossom_id = 0;
vector<pedge> process_blossom(graph& g, const pedge connect) {
  cerr << '2';
  _blossom_id++;
  ll blossom_id = _blossom_id;
  auto blossom = make_shared<node>();
  auto u = connect->from();
  auto w = connect->to();
  cerr << "T";
  while (u->age > w->age) {
    blossom->down.emplace_back(u);
    u = u->back->from();
  }
  while (w->age > u->age) {
    blossom->down.emplace_back(w);
    w = w->back->from();
  }
  cerr << "U[" << u->age << "@" << u->tree_no << " " << w->age << "@" << w->tree_no << "]";
  while (u != w) {
    cerr << "+[" << u->id << " " << u->age << "@" << u->tree_no << " "
      << w->id << " " <<  w->age << "@" << w->tree_no << "]";
    blossom->down.emplace_back(w);
    blossom->down.emplace_back(u);
    if (!u->back || !w->back) {
      cout << endl;
      print_graph(cout, g) << endl;
    }
    assert(u->back);
    assert(w->back);
    u = u->back->from();
    w = w->back->from();
  }
  cerr << "S";
  blossom->down.emplace_back(w);
  for (auto v : blossom->down) {
    v->up = blossom;
    v->blossom_id = blossom_id;
  }
  g.emplace_back(blossom);
  cerr << "Q";
  auto path = find_augmenting_path(g);
  cerr << "W";
  g.pop_back();
  for (auto v : blossom->down) {
    v->up = NULL;
    v->age = 0;
    v->back = NULL;
  }
  cerr << "E";
  vector<pnode> border;
  for (auto e : path) {
    if (e->to()->blossom_id == blossom_id) border.emplace_back(e->to());
    if (e->from()->blossom_id == blossom_id) border.emplace_back(e->from());
  }
  if (border.empty()) return path;
  if (border.size() > 2) {
    cout << border.size() << " @ border" << endl;
    assert(border.size() < 3);
  }
  queue<pnode> q;
  cerr << "R";
  q.emplace(border[0]);
  border[0]->age = 1;
  auto f = border[0];
  while (!q.empty()) {
    auto u = q.front(); q.pop();
    if ((u->age % 2 == 1) && u->exposed) f = u;
    for (auto e : u->out()) {
      auto v = e->to();
      if (v->blossom_id != blossom_id) continue;
      if (v->age != 0) continue;
      if (border.size() > 1 && v == border[1] && u->age % 2 == 1) continue;
      v->back = e;
      v->age = u->age + 1;
      q.emplace(v);
    }
  }
  if (border.size() == 2) f = border[1];
  auto b = f->path_to_root();
  path.insert(path.end(), b.begin(), b.end());
  return path;
}

vector<pedge> find_augmenting_path(graph& g) {
  cerr << '1';
  ll tree_no = 1;
  queue<pnode> q;
  for (auto u : g) {
    if (u->up) continue;
    u->exposed = true;
    u->age = 0;
    u->tree_no = 0;
    u->visited = false; // need this?
    u->back = NULL;
    for (auto e : u->out()) {
      e->visited = false;
      if (e->matched) u->exposed = false;
    }
    if (!u->exposed) continue;
    q.emplace(u);
    u->tree_no = tree_no++;
  }
  cerr << '3';
  vector<pedge> path;
  while (!q.empty()) {
    cerr << '4';
    auto u = q.front(); q.pop();
    for (auto e : u->out()) {
      cerr << '5';
      if (e->visited || e->opposite->visited) continue;
      e->visited = true;
      u->visited = true;
      e->opposite->visited = true;
      auto w = e->to();
      cerr << '6';
      if (w->tree_no == 0) {
        cerr << '7';
        pnode x;
        for (auto y : w->out()) {
          if (y->matched) {
            x = y->to();
            x->back = y;
            y->visited = true;
            y->opposite->visited = true;
          }
        }
        assert(x);
        assert(x->back);
        w->tree_no = x->tree_no = u->tree_no;
        w->back = e;
        w->age = u->age + 1;
        x->age = u->age + 2;
        q.emplace(x);
        continue;
      }
      cerr << '8';
      if (w->age % 2 == 1) continue;
      cerr << '9';
      if (w->tree_no != u->tree_no) {
        cerr << 'A';
        path.emplace_back(e);
        cerr << "A0";
        auto p = u->path_to_root();
        cerr << "A1";
        path.insert(path.end(), p.begin(), p.end());
        cerr << "A2";
        p = w->path_to_root();
        cerr << "A3";
        path.insert(path.end(), p.begin(), p.end());
        cerr << "A4";
        return path;
      }
      cerr << 'B';
      return process_blossom(g, e);
    }
  }
  return path;
}

ll blossom_mcm(graph& g) {
  for (auto u : g) u->reset();
  while (true) {
    auto p = find_augmenting_path(g);
    if (p.empty()) break;
    for (auto e : p) e->match(!e->matched);
  }
  ll r = 0;
  for (auto u : g) {
    for (auto e : u->adjusted) {
      if (e->matched && e->to()->id > u->id) r++;
    }
  }
  return r;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  ll a, b;
  for (ll i = 0; i < 100; i++) {
    auto g = random_graph();
    a = max_dp_matching(g);
    b = blossom_mcm(g);
    if (a != b) {
      // cout << a << " ? " << b << endl;
      // print_graph(cout, g) << endl;
      // break;
    }
  }
}
