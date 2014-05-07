#include <iostream>
#include <string>

using namespace std;

const int MAX = 200;

bool M[MAX][MAX];

string seq;
int pos;
int cols, rows;

void fill_b() {
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            M[r][c] = (seq[pos] == '1');
            pos++;
        }
    }
}

void fill_d(int rf, int cf, int rt, int ct) {
    if (rf == rt || cf == ct) return;
    char q = seq[pos];
    pos++;
    if (q == 'D') {
        int rm = (rf + rt + 1) / 2;
        int cm = (cf + ct + 1) / 2;
        fill_d(rf, cf, rm, cm);
        fill_d(rf, cm, rm, ct);
        fill_d(rm, cf, rt, cm);
        fill_d(rm, cm, rt, ct);
    } else {
        for (int r = rf; r < rt; r++) {
            for (int c = cf; c < ct; c++) {
                M[r][c] = (q == '1');
            }
        }
    }
}

void print_d(int rf, int cf, int rt, int ct) {
    if (rf == rt || cf == ct) return;
    bool same = true;
    for (int r = rf; r < rt && same; r++) {
        for (int c = cf; c < ct && same; c++) {
            same = (M[r][c] == M[rf][cf]);
        }
    }
    if (same) {
        putchar(M[rf][cf] ? '1' : '0');
        return;
    }
    putchar('D');
    int rm = (rf + rt + 1) / 2;
    int cm = (cf + ct + 1) / 2;
    print_d(rf, cf, rm, cm);
    print_d(rf, cm, rm, ct);
    print_d(rm, cf, rt, cm);
    print_d(rm, cm, rt, ct);
}

void print_b() {
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            putchar(M[r][c] ? '1' : '0');
        }
    }
}

int main() {
    char t;
    while(cin >> t, t != '#') {
        scanf("%d%d", &rows, &cols);
        cin >> seq;
        pos = 0;
        if (t == 'B') {
            fill_b();
            printf("D %d %d\n", rows, cols);
            print_d(0, 0, rows, cols);
            putchar('\n');
        } else {
            if (t != 'D') break;
            fill_d(0, 0, rows, cols);
            printf("B %d %d\n", rows, cols);
            print_b();
            putchar('\n');
        }
    }
    return 0;
}
