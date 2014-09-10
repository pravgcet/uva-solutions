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
#include <utility>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <ctime>

using namespace std;
using vi = vector<int>;

struct node {
  int discovered, low;
  bool visited;
  int parent = -1;
  bool articulation;
  vi adjusted;
};

int T = 0;

void mark_adjusted(vector<node> &G, int from) {
  node &x = G[from];
  x.visited = true;
  x.discovered = x.low = ++T;
  int children = 0;
  for (auto i : x.adjusted) {
    node &y = G[i];
    if (y.visited) {
      if (i == x.parent) continue;
      x.low = min(x.low, y.discovered);
      continue;
    }
    children++;
    y.parent = from;
    mark_adjusted(G, i);
    x.low = min(x.low, y.low);

    if (x.parent == -1) {
      x.articulation = children > 1;
    } else {
      x.articulation = y.low >= x.discovered;
    }
  }
}

int main() {
  int n;
  while (cin >> n, n) {
    vector<node> G(n);
    int f;
    while (cin >> f, f) {
      --f;
      int t;
      while (cin.peek() != '\n' && cin >> t) {
        --t;
        G[f].adjusted.push_back(t);
        G[t].adjusted.push_back(f);
      }
    }
    mark_adjusted(G, 0);
    int count = 0;
    for (auto n : G) {
      if (n.articulation) ++count;
    }
    cout << count << endl;
  }
}
