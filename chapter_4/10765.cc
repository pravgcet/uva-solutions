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
#include <memory>

using namespace std;
struct node;
using ii = pair<int, int>;
using p_node = shared_ptr<node>;
using Graph = vector<p_node>;

struct node {
  p_node parent;
  int split;
  bool visited;
  int bucket;
  int age, low;
  Graph adjusted;
};

int main() {
  int m, n;
  while (cin >> n >> m, n) {
    Graph g(n);
    components.clear();
    components.resize(n);
    for (int i = 0; i < n; ++i) g[i] = make_shared<node>();
    int a, b;
    while (cin >> a >> b, a != -1) {
      g[a]->adjusted.push_back(g[b]);
      g[b]->adjusted.push_back(g[a]);
    }

    vector<ii> result;

    result.push_back(make_pair(i, count + k - 1));

    sort(result.begin(), result.end(),
      [](const ii &a, const ii &b) {
        if (a.second == b.second) return a.first < b.first;
        return a.second > b.second;
      });
    for (int i = 0; i < m; ++i) {
      printf("%d %d\n", result[i].first, result[i].second);
    }
    printf("\n");
  }
}
