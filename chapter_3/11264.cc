#include <iostream>
#include <vector>
using namespace std;

int coins[1000];

int main() {
    int tcc;
    scanf("%d", &tcc);
    while (tcc--) {
        int n;
        cin >> n;
        for (int i = 0; i < n; i++) {
            scanf("%d", coins + i);
        }
        int r = 1;
        int sum = 0;
        for (int i = 0; i < n - 1; i++) {
            if (coins[i] + sum < coins[i + 1]) {
                sum += coins[i];
                r++;
            }
        }
        cout << r << endl;
    }
    return 0;
}
