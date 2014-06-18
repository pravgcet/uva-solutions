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
using llu = unsigned long long;

const int MAX_COIN = 300;
const int MAX_WAYS = 1000;

int main() {
    llu ways[MAX_COIN + 1][MAX_WAYS + 1]; // SUM | number of coins
    fill(&ways[0][0], &ways[MAX_COIN + 1][0], 0);
    ways[0][0] = 1;
    for (int coin = 1; coin <= MAX_COIN; coin++) {
        for (int sum = coin; sum <= MAX_COIN; sum++) {
            for (int n = 1; n <= MAX_WAYS; n++) {
                ways[sum][n] += ways[sum - coin][n - 1];
            }
        }
    }
    for (int sum = 1; sum <= MAX_COIN; sum++)
    for (int n = 1; n <= MAX_WAYS; n++) {
        ways[sum][n] += ways[sum][n - 1];
    }

    for (int i = 1; i <= 10; i++) cerr << ways[6][i] << endl;
}
