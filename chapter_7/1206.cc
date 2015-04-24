#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ii = pair<int,int>;
using ll = long long;
using llu = unsigned long long;
const int INF = numeric_limits<int>::max();

struct dot { double x, y; };

struct vec { double x, y;
  vec(dot a, dot b) {
    x = b.x - a.x;
    y = b.y - a.y;
  }
};

using polygon = vector<dot>;

void print_polygon(polygon &p) {
  bool first = true;
  for (auto d : p) {
    if (!first) printf(" "); first = false;
    printf("(%.3f,%.3f)", d.x, d.y);
  }
  printf("\n");
}

polygon build_hull(polygon &p) {
  polygon hull;
}

int main() {
  string line;
  while (getline(cin, line)) {
    istringstream ss(line);
    string a;
    polygon p;
    while (ss >> a) {
      dot d;
      if (sscanf(a.c_str(),"(%lf,%lf)", &d.x, &d.y)) {
        p.emplace_back(d);
      }
    }
    print_polygon(build_hull(p));
  }
}
