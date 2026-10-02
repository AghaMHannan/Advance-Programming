#include "pa1.h"

static int g[81];                   /* 0 = empty, else 1..9 */
static int row[9], col[9], box[9];  /* bitmask of digits already used */

static inline int boxof(int i) { return (i / 9 / 3) * 3 + (i % 9) / 3; }

static int solve(void) {
    int best = -1, bestCount = 10, bestDom = 0;
    for (int i = 0; i < 81; i++) {
        if (g[i]) continue;
        int dom = ~(row[i / 9] | col[i % 9] | box[boxof(i)]) & 0x1FF;
        int c = POPC(dom);
        if (c == 0) return 0;                       /* empty domain: dead end */
        if (c < bestCount) { bestCount = c; best = i; bestDom = dom; if (c == 1) break; }
    }
    if (best < 0) return 1;                          /* no empty cell: solved */

    int r = best / 9, cc = best % 9, b = boxof(best);
    for (int dom = bestDom; dom; dom &= dom - 1) {
        int bit = LOWBIT((u32)dom);
        g[best] = CTZ((u32)bit) + 1;                 /* apply   */
        row[r] |= bit; col[cc] |= bit; box[b] |= bit;
        if (solve()) return 1;                       /* explore */
        g[best] = 0;                                 /* undo    */
        row[r] ^= bit; col[cc] ^= bit; box[b] ^= bit;
    }
    return 0;
}

int main(void) {
    const char *p = "8..........36......7..9.2...5...7.......457.....1...3...1....68..85...1..9....4..";
    for (int i = 0; i < 81; i++) {
        g[i] = (p[i] >= '1' && p[i] <= '9') ? p[i] - '0' : 0;
        if (g[i]) {
            int bit = 1 << (g[i] - 1);
            row[i / 9] |= bit; col[i % 9] |= bit; box[boxof(i)] |= bit;
        }
    }
    double t = now();
    printf("solved=%d in %.3f s\n", solve(), now() - t);
    for (int i = 0; i < 81; i++) { printf("%d", g[i]); if (i % 9 == 8) puts(""); }
    return 0;
}