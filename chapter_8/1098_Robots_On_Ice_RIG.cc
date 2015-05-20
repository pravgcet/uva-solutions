#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ii = pair<int,int>;
using ll = long long;
using llu = unsigned long long;
const int INF = numeric_limits<int>::max();

default_random_engine source(random_device{}());

int main() {
  int cases = 100;
  for (int tc = 0; tc < cases; tc++) {
    uniform_int_distribution<> length(1, 8);
    int n = length(source);
    int m = length(source);
    uniform_int_distribution<> getx(0, n - 1);
    uniform_int_distribution<> gety(0, m - 1);
    printf("%d %d\n", n, m);
    int x0 = 0, y0 = 0;
    int run = (n * m) / 4;
    for (int i = 0; i < 3; i++) {
      while (true) {
        int x = getx(source);
        int y = gety(source);
        int d = abs(x - x0) + abs(y - y0);
        if (d > run) continue;
        if (i) printf(" ");
        printf("%d %d", x, y);
        x0 = x;
        y0 = y;
        break;
      }
    }
    printf("\n");
  }
  printf("0 0\n");
}
