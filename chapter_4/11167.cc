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
    auto source = make_shared<node>();
    source->index = -2;
    auto sink = make_shared<node>();
    sink->index = -2;
    g.emplace_back(source);
    g.emplace_back(sink);
    vector<pnode> times(50001);
    sum = 0;
    for (i = 0; i < n; i++) {
      cin >> v >> a >> b;
      sum += v;
      auto u = make_shared<node>();
      u->index = -1;
      g.emplace_back(u);
      connect(source, u, v);
      for (j = a; j < b; j++) {
        auto &v = times[j];
        if (!v) {
          v = make_shared<node>();
          g.emplace_back(v);
          v->index = j;
          connect(v, sink, m);
        }
        connect(u, v, 1);
      }
    }
    printf("Case %d: ", tc);
    if (max_flow(source, sink, g) == sum) {
      printf("Yes\n");
      for (auto u : g) {
        if (u->index != -1) continue;
        vector<ii> t;
        auto p = u->edges.begin();
        auto e = u->edges.end();
        while (p != e) {
          if ((*p)->to->index >= 0 && (*p)->w == 0) {
            t.emplace_back((*p)->to->index, 0);
            auto p2 = p + 1;
            while (p2 != e && (*p2)->to->index >= 0 && (*p2)->w == 0) {
              p = p2;
              p2++;
            }
            t.back().second = (*p)->to->index + 1;
          }
          p++;
        }
        printf("%lu", t.size());
        for (auto k : t) printf(" (%d,%d)", k.first, k.second);
        printf("\n");
      }
    } else {
      printf("No\n");
    }
  }
}

