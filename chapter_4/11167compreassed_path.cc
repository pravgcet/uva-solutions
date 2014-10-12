#include <vector>
#include <list>
#include <map>
#include <set>
#include <deque>
#include <stack>
#include <bitset>
#include <algorithm>
#include <functional>
#include <numeric>
#include <queue>
#include <utility>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <memory>

using namespace std;

using vi = vector<int>;
using ii = pair<int,int>;
using ll = long long;
using llu = unsigned long long;
const int INF = numeric_limits<int>::max();

struct node;
struct edge;
using pnode = shared_ptr<node>;
using pedge = shared_ptr<edge>;
using graph = vector<pnode>;

struct node {
  bool visited;
  int index;
  vector<pedge> edges;
  pedge back;
};

struct edge {
  int w;
  pedge opp;
  pnode from, to;
};

void connect(pnode a, pnode b, int w) {
  auto ea = make_shared<edge>();
  auto eb = make_shared<edge>();
  ea->from = a; ea->to = b; ea->opp = eb; ea->w = w;
  eb->from = b; eb->to = a; eb->opp = ea; eb->w = 0;
  a->edges.emplace_back(ea);
  b->edges.emplace_back(eb);
}

int adjust(pedge e, int d) {
  if (!e) return d;
  d = adjust(e->from->back, min(d, e->w));
  e->w -= d;
  e->opp->w += d;
  return d;
}

int max_flow(pnode source, pnode sink, graph &g) {
  int a = 0;
  while (true) {
    for (auto u : g) u->visited = false;
    queue<pnode> q;
    q.push(source); source->visited = true;
    while (!(q.empty() || sink->visited)) {
      auto u = q.front(); q.pop();
      for (auto e : u->edges) {
        auto v = e->to;
        if (e->w == 0 || v->visited) continue;
        v->visited = true;
        v->back = e;
        q.push(v);
      }
    }
    if (!sink->visited) break;
    //cerr << a << endl;
    a += adjust(sink->back, INF);
  }
  return a;
}

int main() {
  int n, m, i, j, tc, sum, a, b, v;
  tc = 0;
  while (cin >> n, n) {
    cin >> m;
    tc++;
    graph g;
    auto source = make_shared<node>(); g.emplace_back(source);
    source->index = -2;
    auto sink = make_shared<node>(); g.emplace_back(sink);
    sink->index = -2;
    vector<tuple<int, pnode, bool>> events;
    sum = 0;
    for (i = 0; i < n; i++) {
      cin >> v >> a >> b;
      sum += v;
      auto u = make_shared<node>(); g.emplace_back(u);
      u->index = -1;
      connect(source, u, v);
      events.emplace_back(a, u, true);
      events.emplace_back(b, u, false);
    }
    sort(events.begin(), events.end());

    auto it = events.begin();
    set<pnode> active;
    int start = -1;
    while (it != events.end()) {
      start = get<0>(*it);
      auto next = it;
      while (next != events.end() && get<0>(*next) == start) {
        it = next;
        if (get<2>(*it)) {
          active.insert(get<1>(*it));
        } else {
          active.erase(get<1>(*it));
        }
        next++;
      }
      if (next == events.end()) break;
      int end = get<0>(*next);
      auto u = make_shared<node>(); g.emplace_back(u);
      u->index = start;
      int w = end - start;
      connect(u, sink, w * m);
      for (auto v : active) {
        connect(v, u, w);
      }
      it = next;
    }

    printf("Case %d: ", tc);
    if (max_flow(source, sink, g) == sum) {
      printf("Yes\n");
      for (auto u : g) {
        if (u->index != -1) continue;
        vector<ii> t;
        ii p(-2, -2);
        for (auto e : u->edges) {
          if (e->to->index < 0 || e->opp->w == 0) continue;
          if (p.second + 1 < e->to->index) {
            if (p.second != -2) t.emplace_back(p);
            p.first = e->to->index;
            e->to->index += e->opp->w;
            p.second = e->to->index;
          } else {
            e->to->index += e->opp->w;
            p.second = e->to->index;
          }
        }
        t.emplace_back(p);
        printf("%lu", t.size());
        for (auto k : t) printf(" (%d,%d)", k.first, k.second);
        printf("\n");
      }
    } else {
      printf("No\n");
    }
  }
}

