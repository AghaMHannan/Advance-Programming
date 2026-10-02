# Cheat sheet — reading and representing a graph

This document explains how to **store in memory** a map given as a list of borders, and what
each arrangement makes cheap or costly. It says nothing about what you can then do with it.

## 1. What the input gives you

One line describes a whole map: the number of regions, the number of borders, then the
borders, each given by the two regions it separates.

```
6 8 1 2 2 3 1 3 3 4 4 5 3 5 5 6 6 1
│ │ └───────────── the 8 borders ─────────────┘
│ └── m = 8 borders
└──── n = 6 regions
```

The borders arrive **in no particular order**: do not rely on it. And `m` may be 0 — a map
with no border at all is a valid map.

## 2. A border goes both ways

This is the most frequent mistake, and it is a silent one. The border `1 2` says that region
1 touches region 2 **and** that region 2 touches region 1. If you record only one direction,
half your map is wrong and nothing complains:

```c
adj[a][b] = 1;
adj[b][a] = 1;   /* ← this one gets forgotten */
```

## 3. Three arrangements

**The neighbour list.** For each region, the list of those it touches, with its length
beside it. This is the right choice when you want to walk through the neighbours of a
region. Since the maps in this exercise have at most 55 regions, a fixed array is enough and
avoids any allocation:

```c
int neighbours[64][64];    /* neighbours[i][0 … degree[i]-1] */
int degree[64] = {0};

neighbours[a][degree[a]++] = b;
neighbours[b][degree[b]++] = a;
```

**The adjacency matrix.** An `n × n` array, `adj[i][j]` being 1 if `i` and `j` touch. It
answers "do these two regions touch?" in constant time, which the list can only do by
scanning.

```c
int adj[64][64] = {0};
```

**One row of bits per region.** This is the matrix, but with each row held in **a single
64-bit integer**: bit `j` of `adj[i]` is 1 if regions `i` and `j` touch. The maps in this
exercise have at most 55 regions, so a row fits entirely in one `unsigned long long`.

```c
unsigned long long adj[64];
adj[a] |= 1ULL << b;
adj[b] |= 1ULL << a;
```

The point: the set of neighbours of a region becomes a single value, which can be compared,
united or intersected in one instruction. The document
[`bitset.en.md`](../s1-06-caisse/bitset.en.md), in the folder of exercise 6, covers those
operations.

## 4. The full example

Here is the first map of `exemple.in` — the one from section 1 — stored all three ways.
**Regions are numbered 1 to 6 in the input; here they have been brought back to 0 … 5** by
subtracting 1 when reading.

| region | neighbours | degree | row of bits | value |
|---|---|---|---|---|
| 0 | 1, 2, 5 | 3 | `100110` | 38 |
| 1 | 0, 2 | 2 | `000101` | 5 |
| 2 | 0, 1, 3, 4 | 4 | `011011` | 27 |
| 3 | 2, 4 | 2 | `010100` | 20 |
| 4 | 2, 3, 5 | 3 | `101100` | 44 |
| 5 | 0, 4 | 2 | `010001` | 17 |

The rows of bits read as in `bitset.en.md`: the rightmost bit is number 0. For region 0,
`100110` carries 1s at positions 1, 2 and 5 — its three neighbours.

The neighbours are written here **in increasing order, for readability**. The array you
fill while reading will hold them in the order the borders arrive: region 2 will have
`1 0 3 4` there, not `0 1 3 4`. This matters not at all, as long as you do not assume
otherwise.

Two checks you can run on your own reading:

- **the sum of the degrees equals `2m`**, here `3+2+4+2+3+2 = 16 = 2 × 8`. Each border is
  counted once at each end. If your sum is `m`, you have forgotten one of the two
  directions;
- **the matrix is symmetric**: `adj[i][j]` and `adj[j][i]` always agree.

## 5. The degree of a region

The number of regions it touches. With the list it is `degree[i]`, kept up to date while
reading; with the row of bits it is the number of 1s, recounted on demand:

```c
int d = __builtin_popcountll(adj[i]);
```

## 6. Numbered from 1, stored from 0

The input numbers regions from `1` to `n`, C arrays start at `0`. Either solution works, but
you must **pick one and stick to it**:

- subtract 1 when reading, and work from `0` to `n-1` — this is what the table above does;
- or allocate `n+1` cells and leave index 0 unused.

Mixing the two in one program gives off-by-one shifts that only show up at run time, and
only on some maps.

## 7. What this document does not do

It stores a map in memory. It does not say what to do with it: a well-stored graph answers
no question by itself, and the storage does not change the difficulty of the question asked
— only the cost of each glance.

In other words: it is a tool, not a method.
