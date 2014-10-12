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
  int age;
  int index;
  bool monkey;
  vector<edge> edges;
  vector<int> back;
};

struct edge {
  int to;
  int opp_index;
  int flow;
};

const int MAX = 51000;

vector<node> M;

void connect(int a, int b, int w) {
  edge ea, eb;
  ea.to = b;
  ea.opp_index = M[b].edges.size();
  ea.flow = w;

  eb.to = a;
  eb.opp_index = M[a].edges.size();
  eb.flow = 0;

  M[a].edges.push_back(ea);
  M[b].edges.push_back(eb);
}

int adjust(int it, int ie, int d) {
  int sum = 0;
  auto &u = M[it];
  auto &e = u.edges[ie];
  auto &v = M[e.to];
  d = min(d, e.flow);
  if (u.back.empty()) sum = d;
  for (auto i : u.back) {
    sum += adjust(u.edges[i].to, u.edges[i].opp_index, d - sum);
    if (sum == d) break;
  }
  d = sum;
  e.flow -= d;
  v.edges[e.opp_index].flow += d;
  return d;
}

int max_flow(int source, int sink) {
  int a = 0;
  while (true) {
    for (auto &u : M) {
      u.age = INF;
      u.back.clear();
    }
    queue<int> q;
    q.emplace(source); M[source].age = 0;
    while (!q.empty()) {
      auto &u = M[q.front()]; q.pop();
      for (auto e : u.edges) {
        auto &v = M[e.to];
        if (e.flow == 0 || v.age <= u.age) continue;
        if (v.age == INF) {
          v.age = u.age + 1;
          q.push(e.to);
        }
        v.back.push_back(e.opp_index);
      }
    }
    if (M[sink].age == INF) break;
    for (auto i : M[sink].back) {
      auto &e = M[sink].edges[i];
      a += adjust(e.to, e.opp_index, INF);
    }
  }
  return a;
}

int main() {
  int n, m, i, j, tc, sum, a, b, v;
  tc = 0;
  while (scanf("%d", &n), n) {
    cerr << "read" << endl;
    scanf("%d", &m);
    tc++;
    M.clear();
    M.resize(MAX);
    int sink = 0;
    int source = 1;
    for (i = 0; i < MAX; i++) M[i].index = i;
    for (i = 2 + n; i < MAX; i++) connect(i, sink, m);
    sum = 0;
    cerr << "connect" << endl;
    for (i = 0; i < n; i++) {
      scanf("%d %d %d", &v, &a, &b);
      sum += v;
      connect(source, i + 2, v);
      for (j = a; j < b; j++) connect(i + 2, j + 2 + n, 1);
    }
    cerr << "solve" << endl;
    printf("Case %d: ", tc);
    if (max_flow(source, sink) == sum) {
      printf("Yes\n");
      for (i = 0; i < n; i++) {
        auto &u = M[i + 2];
        vector<ii> t;
        auto p = u.edges.begin();
        auto e = u.edges.end();
        while (p != e) {
          if (p->to != source && p->flow == 0) {
            t.emplace_back(p->to - n - 2, 0);
            auto next = p;
            while (next != e && next->to != source && next->flow == 0) {
              p = next;
              next++;
            }
            t.back().second = p->to - n - 2 + 1;
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

