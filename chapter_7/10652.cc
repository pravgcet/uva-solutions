#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ii = pair<int,int>;
using ll = long long;
using llu = unsigned long long;
const int INF = numeric_limits<int>::max();

struct point {
  double x, y;
};

using vp = vector<point>;

vp build_hull(vp dots) {
  return dots;
}

double area(vp p) {
  return 1;
}

int main() {
  int tcc; cin >> tcc;
  while (tcc--) {
    int n; cin >> n;
    double rect_area = 0;
    vp dots;
    while (n--) {
      double x, y, w, h, th;
      cin >> x >> y >> w >> h >> th;
      th = th * M_PI / 180;
      rect_area += w * h;
      for (int i = -1; i < 2; i += 2) {
        for (int j = -1; j < 2; j += 2) {
          point p;
          p.x = x + 0.5 * (i * w * cos(th) + j * h * sin(th));
          p.y = y + 0.5 * (-i * w * sin(th) + j * h * cos(th));
          dots.emplace_back(p);
        }
      }
    }
    vp hull = build_hull(dots);
    printf("%.1f %%\n", round(rect_area * 1000 / area(hull)) / 10);
  }
}
