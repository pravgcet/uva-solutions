#include <algorithm>
#include <stdio.h>
#include <iostream>
#include <cstring>
#include <vector>

using namespace std;

const int MAX = 26;

// union-disjoint
int height[MAX];
int parent[MAX];

char get_token() {
    char c;
    while (scanf("%c", &c)) {
        if ((c >= 'A' && c <= 'Z') || (c == '*')) return c;
    }
    return 0;
}

int get_parent(int a) {
    while (parent[a] != a) a = parent[a];
    return a;
}

void join(int a, int b) {
    int p, c;
    a = get_parent(a);
    b = get_parent(b);
    if (a == b) return;
    if (height[a] >= height[b]) {
        p = a;
        c = b;
    } else {
        p = b;
        c = a;
    }
    if (height[p] == height[c]) height[p]++;
    parent[c] = p;
}

int main() {
    int cc;
    scanf("%d", &cc);
    while (cc--) {
        fill_n(height, MAX, 0);
        for (int i = 0; i < MAX; i++) parent[i] = i;
        char a, b;
        while (true) {
            a = get_token();
            if (a == '*') break;
            join(a - 'A', get_token() - 'A');
        }
        char s[250];
        fgets(s, 250, stdin); // skip asteriks
        fgets(s, 250, stdin);
        // while (fgets(s, 250, stdin), strlen(s) <= 1) {}
        int tree_count = 0;
        int acorn_count = 0;
        for (int i = 0; s[i]; i++) {
            if (s[i] < 'A' || s[i] > 'Z') continue;
            int j = s[i] - 'A';
            if (parent[j] != j) continue;
            if (height[j] == 0) {
                acorn_count++;
            } else {
                tree_count++;
            }
        }
        printf("There are %d tree(s) and %d acorn(s).\n", tree_count, acorn_count);
    }
    return 0;
}
