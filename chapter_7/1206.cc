#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ii = pair<int,int>;
using ll = long long;
using llu = unsigned long long;
const int INF = numeric_limits<int>::max();

struct dot { double x, y; };

int main() {
  string line;
  while (getline(cin, line)) {
    istringstream ss(line);
    string p;
    while (ss >> p) {
      cout << p << endl;
    }
  }
}
