#include <cmath>
#include <stdio.h>
#include <iostream>

using namespace std;

int p, q, r, s, t, u;

double f(double x) {
    return p * exp(-x) + q * sin(x) + r * cos(x) + s * tan(x) + t * x * x + u;
}

double fd(double x){
  return -p*exp(-x) + q*cos(x) - r*sin(x) + s/(cos(x)*cos(x)) + 2*t*x;
}

double newton(){
  if (f(0)==0) return 0;
  int r = 5000;
  int r1;
  for (double x=0.5; ;) {
    double x1 = x - f(x)/fd(x);
    r1 = round(x1 * 10000);
    if (r1 == r) return x;
    x = x1;
    r = r1;
  }
}

int main() {
    while (scanf("%d%d%d%d%d%d", &p, &q, &r, &s, &t, &u) == 6) {
        if (f(0) * f(1) > 0) {
            printf("No solution\n");
            continue;
        }
        printf("%.4lf\n", newton());
    }
    return 0;
}
