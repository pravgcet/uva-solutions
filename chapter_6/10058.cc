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
#include <queue>
#include <utility>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <memory>
#include <regex>

using namespace std;

using vi = vector<int>;
using ii = pair<int,int>;
using ll = long long;
using llu = unsigned long long;
const int INF = numeric_limits<int>::max();

vector<string> verbs = { "hate", "love", "know", "like",
 "hates", "loves", "knows", "likes" };

vector<string> nouns = {"tom", "jerry", "goofy", "mickey", "jimmy", "dog", "cat", "mouse"};

string verb("(hate|love|know|like)s");
string noun("(tom|jerry|goofy|mickey|jimmy|dog|cat|mouse)");
string actor("(a |the )?"+noun);
string active_list("(" +noun + " and )*" +noun);
string action(active_list + " " + verb + " " + active_list);
regex statement("("+action+" ?, ?)*"+action);

int main() {
  string s;
  while (getline(cin, s)) {
    cerr << s << endl;
    regex e(".", regex::grep);
    cerr << regex_match(s, e) << endl;
    string o;
    string r = "?";
    cerr << regex_replace(s, e, r) << endl;
    if (regex_match(s, statement)) {
      cout << "YES I WILL" << endl;
    } else {
      cout << "NO I WON'T" << endl;
    }
  }
}
