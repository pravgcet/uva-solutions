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

struct node {
  bool visited;
  int c;
  vector<pedge> edges;
  pedge back;
  double x, y;
};

struct edge {
  pedge opp;
  int c, r;
  pnode from, to;
};

int max_flow(int s, int t, vector<pnode> &g) {
  for (auto u : g) {
    for (auto e : u->edges) e->r = e->c;
  }

  int result = 0;
  while (true) {
    for (auto u : g) u->visited = false;
    queue<pnode> q;
    q.push(g[s]); g[s]->visited = true;

    while (!q.empty()) {
      auto u = q.front(); q.pop();
      if (u == g[t]) break;
      for (auto e : u->edges) {
        auto v = e->to;
        if (v->visited || e->r == 0) continue;
        q.push(v); v->visited = true;
        v->back = e;
      }
    }

    if (!g[t]->visited) break;

    auto e = g[t]->back;
    int f = INF;
    while (true) {
      f = min(f, e->r);
      if (e->from == g[s]) break;
      e = e->from->back;
    }

    result += f;

    e = g[t]->back;
    while (true) {
      e->r -= f;
      e->opp->r += f;
      if (e->from == g[s]) break;
      e = e->from->back;
    }
  }

  return result;
}

int main() {
  int tcc;
  cin >> tcc;
  while (tcc--) {
    int n;
    double d;
    cin >> n >> d;
    ++n;
    vector<pnode> g(n); // g[0] - source
    for (int i = 0; i < n; ++i) g[i] = make_shared<node>();

    int total = 0;
    for (int i = 1; i < n; ++i) {
      int k;
      cin >> g[i]->x >> g[i]->y >> k >> g[i]->c;
      total += k;
      pedge a = make_shared<edge>();
      pedge b = make_shared<edge>();
      a->from = g[0]; a->c = k; a->to = g[i]; a->opp = b;
      g[0]->edges.push_back(a);
      b->from = g[i]; b->c = 0; b->to = g[0]; b->opp = a;
      g[i]->edges.push_back(b);
    }

    for (int i = 1; i < n; ++i)
    for (int j = i + 1; j < n; ++j) {
      double q = pow(pow(g[i]->x - g[j]->x, 2)
                   + pow(g[i]->y - g[j]->y, 2), 0.5);
      if (q > d) continue;
      pedge a = make_shared<edge>();
      pedge b = make_shared<edge>();
      a->from = g[i]; a->c = g[i]->c; a->to = g[j]; a->opp = b;
      g[i]->edges.push_back(a);
      b->from = g[j]; b->c = g[j]->c; b->to = g[i]; b->opp = a;
      g[j]->edges.push_back(b);
    }

    vi v;
    for (int i = 1; i < n; ++i) {
      if (max_flow(0, i, g) == total) v.push_back(i);
    }

    if (v.empty()) {
      printf("-1\n");
    } else {
      printf("%d", v[0] - 1);
      for (int i = 1; i < v.size(); ++i) {
        printf(" %d", v[i] - 1);
      }
      printf("\n");
    }
  }
}
