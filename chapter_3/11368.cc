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

struct doll {
    int w, h;
    bool used;
    bool operator < (const doll &o) const {
        return w < o.w && h < o.h;
    }
};

int main() {
    int tcc;
    cin >> tcc;
    while (tcc--) {
        int n;
        cin >> n;
        vector<doll> dolls;
        while (n--) {
            doll d;
            cin >> d.h >> d.w;
            d.used = false;
            dolls.push_back(d);
        }
        sort(dolls.begin(), dolls.end());
        int to_pick = dolls.size();
        int count = 0;
        while (to_pick) {
            count++;
            int i;
            for (i = 0; i < dolls.size(); i++) {
                if (!dolls[i].used) break;
            }
            dolls[i].used = true;
            to_pick--;
            int j = i + 1;
            while (j < dolls.size()) {
                if (dolls[i].h < dolls[j].h &&
                    dolls[i].w < dolls[j].w
                    && !dolls[j].used) {
                    i = j;
                    dolls[i].used = true;
                    to_pick--;
                }
                j++;
            }
        }
        cout << count << endl;
    }
}
