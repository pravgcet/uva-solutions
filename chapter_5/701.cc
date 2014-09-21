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

int main() {
  ll a = 1;
  set<ll> s;
  for (int i = 0; i < 10000; ++i) {
    a = (a * 2);
    while (a / 3000000000 != 0) a /= 10;
    cout << a << endl;
    if (s.count(a)) {
      cout << "cycle" << endl;
      break;
    }
    s.insert(a);
  }
}
