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

const int MAX_COUNT = 100;

int memo[10201][MAX_COUNT];
int price[MAX_COUNT], value[MAX_COUNT];

int find(int sum, int k) {
    if (sum <= 0 || k < 0) return 0;
    int &v = memo[sum][k];
    if (v == -1) {
        if (sum >= price[k]) {
            v = value[k] + find(sum - price[k], k - 1);
        }
        v = max(v, find(sum, k - 1));
    }
    return v;
}

int main() {
    int m, n;
    int count = 0;
    while (cin >> m >> n) {
        count++;
        cerr << count << " " << m << " " << n << endl;
        for (int i = 0; i < n; i++) {
            cin >> price[i] >> value[i];
        }
        if (m > 2000 - 200) m += 200;
        // clear
        fill(&memo[0][0], &memo[10201][0], -1);
        cout << find(m, n - 1) << endl;
    }
}
