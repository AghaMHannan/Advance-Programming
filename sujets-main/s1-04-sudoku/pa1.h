#ifndef PA1_H
#define PA1_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <time.h>

typedef long long ll;
typedef unsigned long long u64;
typedef unsigned u32;

#define MIN(a,b) ((a)<(b)?(a):(b))
#define MAX(a,b) ((a)>(b)?(a):(b))

/* ============================ FAST INPUT ============================
 * rd_ll / rd_int return 1 when a number was read, 0 at end of input.
 * Skips any separator (space, newline, tab) -> "variable number of
 * integers per line" costs you nothing.
 *   ll x; while (rd_ll(&x)) { ... }
 * Do NOT mix these with scanf on the same stream.
 */
static char  pa1_ibuf[1 << 16];
static int   pa1_ipos = 0, pa1_ilen = 0;

static inline int pa1_gc(void) {
    if (pa1_ipos == pa1_ilen) {
        pa1_ilen = (int)fread(pa1_ibuf, 1, sizeof pa1_ibuf, stdin);
        pa1_ipos = 0;
        if (pa1_ilen <= 0) return -1;
    }
    return (unsigned char)pa1_ibuf[pa1_ipos++];
}
static inline int rd_ll(ll *out) {
    int c = pa1_gc(), neg = 0;
    while (c != -1 && (c < '0' || c > '9') && c != '-') c = pa1_gc();
    if (c == -1) return 0;
    if (c == '-') { neg = 1; c = pa1_gc(); }
    ll x = 0;
    while (c >= '0' && c <= '9') { x = x * 10 + (c - '0'); c = pa1_gc(); }
    *out = neg ? -x : x;
    return 1;
}
static inline int rd_u64(u64 *out) { ll v; if (!rd_ll(&v)) return 0; *out = (u64)v; return 1; }
static inline int rd_int(int *out) { ll v; if (!rd_ll(&v)) return 0; *out = (int)v; return 1; }

/* ============================ FAST OUTPUT ===========================
 * Call out_setup() first thing in main(): printf then buffers 64 KB
 * instead of flushing every line. Nothing else to change.
 */
static char pa1_obuf[1 << 16];
static inline void out_setup(void) { setvbuf(stdout, pa1_obuf, _IOFBF, sizeof pa1_obuf); }

/* =========================== SORT (qsort) ===========================
 * NEVER write `return a - b;` in a comparator: it overflows.
 */
static inline int cmp_int (const void *a, const void *b) { int x = *(const int *)a, y = *(const int *)b; return (x > y) - (x < y); }
static inline int cmp_ll  (const void *a, const void *b) { ll  x = *(const ll  *)a, y = *(const ll  *)b; return (x > y) - (x < y); }
static inline int cmp_int_desc(const void *a, const void *b) { return cmp_int(b, a); }
static inline int cmp_ll_desc (const void *a, const void *b) { return cmp_ll (b, a); }
/*  qsort(a, n, sizeof a[0], cmp_ll);  */

/* ========================== BINARY SEARCH ===========================
 * a must be sorted ascending.
 * lower_bound: index of the first element >= key   (first position >= x)
 * upper_bound: index of the first element >  key   (first position  > x)
 * count of key == upper_bound - lower_bound
 */
static inline int lower_bound_ll(const ll *a, int n, ll key) {
    int lo = 0, hi = n;
    while (lo < hi) { int mid = lo + (hi - lo) / 2; if (a[mid] < key) lo = mid + 1; else hi = mid; }
    return lo;
}
static inline int upper_bound_ll(const ll *a, int n, ll key) {
    int lo = 0, hi = n;
    while (lo < hi) { int mid = lo + (hi - lo) / 2; if (a[mid] <= key) lo = mid + 1; else hi = mid; }
    return lo;
}
static inline int lower_bound_int(const int *a, int n, int key) {
    int lo = 0, hi = n;
    while (lo < hi) { int mid = lo + (hi - lo) / 2; if (a[mid] < key) lo = mid + 1; else hi = mid; }
    return lo;
}
/* sort + remove duplicates in place, returns the new length */
static inline int uniq_ll(ll *a, int n) {
    if (n <= 0) return 0;
    qsort(a, (size_t)n, sizeof a[0], cmp_ll);
    int k = 1;
    for (int i = 1; i < n; i++) if (a[i] != a[k - 1]) a[k++] = a[i];
    return k;
}

/* ============================= BITMASKS =============================
 * m is a set of small elements; element i is in m iff bit i is 1.
 */
#define BIT(i)        (1u  << (i))
#define BITLL(i)      (1ull << (i))
#define HAS(m,i)      (((m) >> (i)) & 1u)
#define ADD(m,i)      ((m) |=  BIT(i))
#define DEL(m,i)      ((m) &= ~BIT(i))
#define FLIP(m,i)     ((m) ^=  BIT(i))
#define LOWBIT(m)     ((m) & -(m))            /* lowest set bit, as a mask   */
#define POPC(m)       __builtin_popcount(m)   /* number of set bits          */
#define POPCLL(m)     __builtin_popcountll(m)
#define CTZ(m)        __builtin_ctz(m)        /* index of lowest set bit, m!=0 */
#define CTZLL(m)      __builtin_ctzll(m)
#define FULL(n)       ((1u << (n)) - 1u)      /* set {0..n-1}, n < 32        */

/* iterate over the elements of m:
 *   for (u32 t = m; t; t &= t - 1) { int i = CTZ(t); ... }
 * iterate over every subset s of m (including 0 and m):
 *   for (u32 s = m; ; s = (s - 1) & m) { ...; if (!s) break; }
 */

/* ======================= MODULAR ARITHMETIC ========================= */
static inline u64 mod_pow(u64 a, u64 b, u64 m) {  /* a^b mod m, O(log b) */
    u64 r = 1 % m;                                 /* 1 % m, not 1 !     */
    a %= m;                                        /* else r*a overflows */
    while (b) {
        if (b & 1) r = r * a % m;                  /* < 4e18, fits in u64 */
        a = a * a % m;
        b >>= 1;
    }
    return r;
}
static inline u64 mod_mul(u64 a, u64 b, u64 m) {   /* safe when m > 2^32 */
    return (u64)((__uint128_t)a * b % m);
}
static inline ll gcd_ll(ll a, ll b) { while (b) { ll t = a % b; a = b; b = t; } return a; }

/* F(n) mod m by fast doubling, O(log n). Needs m*m to fit: m <= 3e9 in u64. */
static inline void fib_pair(u64 n, u64 m, u64 *f, u64 *g) { /* f=F(n), g=F(n+1) */
    if (n == 0) { *f = 0; *g = 1 % m; return; }
    u64 a, b;
    fib_pair(n >> 1, m, &a, &b);
    u64 c = a * ((2 * b % m + m - a % m) % m) % m;  /* F(2k)   */
    u64 d = (a * a % m + b * b % m) % m;            /* F(2k+1) */
    if (n & 1) { *f = d; *g = (c + d) % m; }
    else       { *f = c; *g = d; }
}
static inline u64 fib_mod(u64 n, u64 m) { u64 f, g; fib_pair(n, m, &f, &g); return f; }

/* ======================== NEXT PERMUTATION ==========================
 * C has no std::next_permutation. Sort ascending first, then:
 *   do { ... } while (next_permutation_int(a, n));
 * visits the n! permutations in lexicographic order.
 */
static inline int next_permutation_int(int *a, int n) {
    if (n < 2) return 0;
    int i = n - 2;
    while (i >= 0 && a[i] >= a[i + 1]) i--;
    if (i < 0) return 0;
    int j = n - 1;
    while (a[j] <= a[i]) j--;
    int t = a[i]; a[i] = a[j]; a[j] = t;
    for (int l = i + 1, r = n - 1; l < r; l++, r--) { t = a[l]; a[l] = a[r]; a[r] = t; }
    return 1;
}

/* ============================== TIMER ===============================
 * Print to stderr only. stdout belongs to the judge.
 *   double t0 = now(); ... fprintf(stderr, "%.3f s\n", now() - t0);
 */
static inline double now(void) { return (double)clock() / CLOCKS_PER_SEC; }

/* __int128 printing (for exact counts above 9.2e18) */
static inline void print_i128(__int128 v) {
    if (v < 0) { putchar('-'); v = -v; }
    char buf[42]; int k = 0;
    if (v == 0) buf[k++] = '0';
    while (v > 0) { buf[k++] = (char)('0' + (int)(v % 10)); v /= 10; }
    while (k--) putchar(buf[k]);
}

#endif /* PA1_H */