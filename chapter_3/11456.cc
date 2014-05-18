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

struct train {
    int left, right, length;
};

int main() {
    int tcc;
    cin >> tcc;
    while (tcc--) {
        int n;
        cin >> n;
        vector<int> w(n);

        for (int i = 0; i < n; i++) {
            cin >> w[i];
        }

        reverse(w.begin(), w.end());

        vector<int> lds(n, 1);
        vector<int> lis(n ,1);

        int best = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < i; j++) {
                if (w[j] > w[i]) lds[i] = max(lds[i], lds[j] + 1);
                if (w[j] < w[i]) lis[i] = max(lis[i], lis[j] + 1);
            }
            best = max(best, lis[i] + lds[i] - 1);
        }
        cout << best << endl;
    }
}
