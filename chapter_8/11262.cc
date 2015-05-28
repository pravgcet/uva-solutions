#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ii = pair<int,int>;
using ll = long long;
using llu = unsigned long long;
const int INF = numeric_limits<int>::max();

struct point {
  double x, y;
  point() {}
  point(double x, double y) : x(x), y(y) {}
  double operator * (const point & o) {
    return x * o.x + y * o.y;
  }
  point operator - (const point& o) {
    return point(x - o.x, y - o.y);
  }
  point operator + (const point& o) {
    return point(x + o.x, y + o.y);
  }
  double operator >> (const point& o) {
    point d = (*this - o);
    return sqrt(d * d);
  }
};

ostream& operator << (ostream& s, const point& p) {
  s << "(" << p.x << ", " << p.y << ")";
  return s;
}

struct node;
struct edge;
using pnode = shared_ptr<node>;
using pedge = shared_ptr<edge>;
using graph = vector<pnode>;

struct node {
  bool visited;
  vector<pedge> adjusted;
  pedge back;
  point p;
};

struct edge {
  pnode from, to;
  int flow;
  int capacity;
  pedge opposite;
  double d;
};

void connect(pnode &a, pnode &b, int w, double d) {
  pedge ea = make_shared<edge>();
  pedge eb = make_shared<edge>();
  ea->from = a; ea->to = b; ea->capacity = ea->flow = w; ea->opposite = eb;
  ea->d = d;
  eb->from = b; eb->to = a; eb->capacity = eb->flow = 0; eb->opposite = ea;
  eb->d = d;
  a->adjusted.emplace_back(ea);
  b->adjusted.emplace_back(eb);
}

int adjust(pedge e, int d) {
  if (!e) return d;
  d = adjust(e->from->back, min(d, e->flow));
  e->flow -= d;
  e->opposite->flow += d;
  return d;
}

int max_flow(vector<pnode> &g, pnode &source, pnode &sink, double max_d) {
  int result = 0;
  while (true) {
    for (auto u : g) u->visited = false;
    queue<pnode> q;
    q.push(source); source->visited = true;
    while (!(q.empty() || sink->visited)) {
      auto u = q.front(); q.pop();
      for (auto e : u->adjusted) {
        auto v = e->to;
        if (v->visited || e->flow == 0 || e->d > max_d) continue;
        v->back = e;
        v->visited = true;
        q.push(v);
      }
    }
    if (!sink->visited) break;
    for (auto e : sink->adjusted) {
      auto o = e->opposite;
      if (!o->from->visited || o->flow == 0 || o->d > max_d) continue;
      result += adjust(o, o->flow);
    }
  }
  return result;
}

// invariant: answer is within (a, b], f(a) = false, f(b) = true
ll binary_search_lower(ll a, ll b, function<bool(ll)> f) {
  while (b - a > 1) {
    ll m = (a + b) / 2;
    if (f(m)) {
      b = m;
    } else {
      a = m;
    }
  }
  return b;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  int tcc;
  cin >> tcc;
  for (int tc = 1; tc <= tcc; tc++) {
    vector<pnode> red, blue;
    int n, k;
    cin >> n >> k;
    graph g;
    pnode source = make_shared<node>();
    pnode sink = make_shared<node>();
    g.emplace_back(source);
    g.emplace_back(sink);
    for (int i = 0; i < n; i++) {
      string color;
      pnode u = make_shared<node>();
      g.emplace_back(u);
      cin >> u->p.x >> u->p.y >> color;
      if (color == "red") {
        red.emplace_back(u);
        connect(source, u, 1, 0);
      } else {
        blue.emplace_back(u);
        connect(u, sink, 1, 0);
      }
    }

    for (auto r : red) {
      for (auto b : blue) {
        double l = r->p >> b->p;
        connect(r, b, 1, l);
      }
    }

    auto test = [&] (ll x) {
      for (auto u : g) for (auto e : u->adjusted) e->flow = e->capacity;
      return max_flow(g, source, sink, x) >= k;
    };

    if (!test(3000)) {
      cout << "Impossible" << endl;
    } else {
      ll answer = binary_search_lower(-1, 3000, test);
      cout << answer << endl;
    }
  }
}
