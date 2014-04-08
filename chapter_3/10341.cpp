#include <cmath>
#include <stdio.h>
#include <iostream>

using namespace std;

int p, q, r, s, t, u;

double calc(double x) {
    return p * exp(-x) + q * sin(x) + r * cos(x) + s * tan(x) + t * x * x + u;
}

int main() {
    while (scanf("%d%d%d%d%d%d", &p, &q, &r, &s, &t, &u) == 6) {
        double r = 1.0d;
        double l = 0.0d;
        double lv = calc(l);
        double rv = calc(r);
        if (lv * rv > 0) {
            printf("No solution\n");
            continue;
        }
        double x;
        while (abs(r - l) > 1e-7) {
            x = (r + l) / 2;
            double v = calc(x);
            if (v * lv <= 0) {
                rv = v;
                r = x;
            } else {
                lv = v;
                l = x;
            }
        }
        // x = (r + l) / 2;
        printf("%.4lf\n", x);
    }
    return 0;
}
