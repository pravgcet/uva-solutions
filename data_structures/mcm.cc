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

bool visualize = true;

ll _edge_id = 0;
struct edge {
  pnode _to;
  pedge opposite;
  bool matched, visited;
  ll id;

  pnode to();
  pnode from() { return opposite->to(); }
  void match(bool v) {
    matched = v;
    opposite->matched = v;
  }
};
ll _node_id;
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
  _edge_id++;
  ea->id = _edge_id; ea->_to = b; ea->opposite = eb;
  eb->id = _edge_id; eb->_to = a; eb->opposite = ea;
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

const string colors[] = {
"#ffffff",
"#d6d6d6",
"#4d4d4c",
"#8e908c",
"#c82829",
"#f5871f",
"#eab700",
"#718c00",
"#3e999f",
"#4271ae",
"#8959a8"
};

void show_forest(graph &g) {
  if (!visualize) return;
  cout << "{message: 'forest', action: function() { nodes.update([";
  for (auto u : g) {
    string style = "";
    if (u->up) {
      style = "color: '#cccccc'";
    } else {
      style = "color: '" + colors[u->tree_no] + "'";
    }
    cout << "{id : " << u->id << ", " << style << "},";
  }
  cout << "]);}}," << endl;
}

void show_path(vector<pedge> p, string message, string style) {
  if (!visualize) return;
  cout << "{message: '" << message << "', action: function() { edges.update([";
  for (auto e : p) {
    ll id = e->id; if (id == 0) id = e->opposite->id;
    cout << "{id : " << id << ", " << style << "},";
  }
  cout << "]);}},";
  cout << endl;
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
    g[i]->id = _node_id;
    _node_id++;
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
void print_graph(graph& g) {
  cout << "function initialize_data() { nodes.add([";
  for (auto u : g) {
    cout << "{id: " << u->id <<  ", label: '" << u->id <<  "'},";
  }
  cout << "]); edges.add([";
  for (auto u : g) {
    for (auto e : u->out()) {
      if (e->to()->id < u->id) continue;
      cout << "{id: " << e->id
      << ", from: " << e->from()->id
      << ", to: "<< e->to()->id <<", color: {inherit: false}, scaling: {max: 3}},";
    }
  }
  cout << "]); network.stabilize();}" << endl;
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
  _blossom_id++;
  ll blossom_id = _blossom_id;
  auto blossom = make_shared<node>();
  blossom->id = _node_id++;
  set<ll> blossom_border;
  blossom_border.insert(connect->id);
  if (visualize) cout << "// " << connect->from()->id
                      << " -> "<< connect->to()->id << endl;
  auto u = connect->from();
  auto w = connect->to();
  while (u->age > w->age) {
    blossom->down.emplace_back(u);
    blossom_border.insert(u->back->id);
    if (visualize) cout << "// " << u->back->from()->id
                        << " -> "<< u->back->to()->id << endl;
    u = u->back->from();
  }
  while (w->age > u->age) {
    blossom->down.emplace_back(w);
    blossom_border.insert(w->back->id);
    if (visualize) cout << "// " << w->back->from()->id
                        << " -> "<< w->back->to()->id << endl;
    w = w->back->from();
  }
  while (u != w) {
    blossom->down.emplace_back(w);
    blossom->down.emplace_back(u);
    if (!u->back || !w->back) {
      // cout << "" << endl;
      // print_graph(cout, g) << endl;
    }
    assert(u->back);
    assert(w->back);
    blossom_border.insert(w->back->id);
    blossom_border.insert(u->back->id);
    if (visualize) cout << "// " << u->back->from()->id
                        << " -> "<< u->back->to()->id << endl;
    if (visualize) cout << "// " << w->back->from()->id
                        << " -> "<< w->back->to()->id << endl;
    u = u->back->from();
    w = w->back->from();
  }
  blossom->down.emplace_back(w);
  for (auto v : blossom->down) {
    v->up = blossom;
    v->blossom_id = blossom_id;
  }
  if (visualize) {
    cout << "{message: 'blossom', action: function() { nodes.update([";
    for (auto v : blossom->down) {
      cout << "{id : " << v->id << ", color: 'red'},";
    }
    cout << "]);}}," << endl;
  }
  g.emplace_back(blossom);
  auto path = find_augmenting_path(g);
  show_path(path, "P^", "dashes: true");
  g.pop_back();
  for (auto v : blossom->down) {
    v->up = NULL;
    v->age = 0;
    v->back = NULL;
  }
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
  q.emplace(border[0]);
  border[0]->age = 1;
  auto f = border[0];
  if (visualize) cout << "// " << blossom_border.size() << " edges in blossom" << endl;
  while (!q.empty()) {
    auto u = q.front(); q.pop();
    if (visualize) cout << "// @ " << u->id << endl;
    if (u->exposed) f = u;
    for (auto e : u->out()) {
      if (blossom_border.count(e->id) == 0) continue;
      auto v = e->to();
      // if (v->blossom_id != blossom_id) continue;
      if (v->age != 0) continue;
      if (border.size() > 1 && v == border[1] && u->age % 2 == 1) continue;
      if (v->exposed && u->age % 2 == 1) continue;
      v->back = e;
      v->age = u->age + 1;
      q.emplace(v);
    }
  }
  if (border.size() == 2) f = border[1];
  auto b = f->path_to_root();
  path.insert(path.end(), b.begin(), b.end());
  show_path(path, "P", "dashes: true");
  return path;
}

vector<pedge> find_augmenting_path(graph& g) {
  ll tree_no = 1;
  queue<pnode> q;
  for (auto u : g) {
    u->back = NULL;
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
  show_forest(g);
  vector<pedge> path;
  while (!q.empty()) {
    auto u = q.front(); q.pop();
    for (auto e : u->out()) {
      if (e->visited || e->opposite->visited) continue;
      e->visited = true;
      u->visited = true;
      e->opposite->visited = true;
      auto w = e->to();
      if (w->tree_no == 0) {
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
      if (w->age % 2 == 1) continue;
      if (w->tree_no != u->tree_no) {
        path.emplace_back(e);
        auto p = u->path_to_root();
        path.insert(path.end(), p.begin(), p.end());
        p = w->path_to_root();
        path.insert(path.end(), p.begin(), p.end());
        return path;
      }
      return process_blossom(g, e);
    }
  }
  return path;
}

void matched_state(graph& g) {
  if (!visualize) return;
  cout << "{message: 'matched', action: function() { edges.update([";
  for (auto u : g) {
    for (auto e : u->out()) {
      if (e->id == 0) continue;
      cout << "{id : " << e->id << ", dashes: false";
      if (e->matched) {
        cout << ", value: 0.1";
      } else {
        cout << ", value: 0";
      }
      cout << "},";
    }
  }
  cout << "]);}},";
  cout << endl;
}

ll blossom_mcm(graph& g) {
  while (true) {
    auto p = find_augmenting_path(g);
    if (p.empty()) break;
    show_path(p, "augment", "dashes: true");
    for (auto e : p) e->match(!e->matched);
    matched_state(g);
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
  visualize = false;
  for (ll i = 0; i < 1000; i++) {
    ll random_seed = random_device{}();
    // ll random_seed = 553835326; visualize = true;
    source.seed(random_seed);
    if (visualize) cout << "------------------" << endl;
    // cerr << "generage graph" << endl;
    _node_id = 0;
    auto g = random_graph();
    // cerr << "dp" << endl;
    a = max_dp_matching(g);
    // cerr << "reset" << endl;
    for (auto u : g) u->reset();
    // cerr << "print" << endl;
    if (visualize) print_graph(g);
    if (visualize) cout << "var events = [";
    // cerr << "start blossom match" << endl;
    b = blossom_mcm(g);
    if (visualize) cout << "];" << endl;
    if (a != b) {
      cout << "seed = " << random_seed << endl;
      cout <<  "exposed " << a << " but " << b << endl;
      break;
    }
  }
}

