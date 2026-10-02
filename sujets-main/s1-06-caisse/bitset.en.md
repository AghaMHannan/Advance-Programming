# Cheat sheet — representing a set with the bits of an integer

This document explains a **representation**, useful whenever you handle sets drawn from a
collection of at most **64 elements**. It is not about any exercise in particular: decide
for yourself whether it helps you.

## 1. The idea: one bit per element

You have an array of `n` elements, `n` ranging from 0 to 64, and you want to designate a
**subset** of those elements. The usual way is an array of booleans:

```c
int present[64];    /* present[i] = 1 if the element at index i is in the set */
```

An `unsigned long long` is exactly 64 bits wide. Each of those bits can play the part of
one cell of that array:

> **the bit at index `i` is 1 if the element at index `i` is present, 0 if it is absent.**

The whole set then fits in **a single variable**. A set containing three elements is an
integer whose binary form has **exactly three `1`s** — no matter which ones, and no matter
how large the original array was.

Two special cases that fall out on their own:

| set | integer |
|---|---|
| the empty set | `0` |
| all 64 elements present | every bit set to 1 |

## 2. An example on 16 bits

Take a list of **6 elements**, at indices 0 to 5, and the set containing elements
**1, 2 and 5**. On 16 bits:

```
bit index :  15 14 13 12 11 10  9  8  7  6  5  4  3  2  1  0
    value :   0  0  0  0  0  0  0  0  0  0  1  0  0  1  1  0
                                            ↑        ↑  ↑
                                     element 5       2  1
```

That is `0000 0000 0010 0110` in binary, i.e. **38** in decimal — because
`2^5 + 2^2 + 2^1 = 32 + 4 + 2 = 38`.

Three remarks you pay dearly for if you discover them while debugging:

- **Bit 0 is on the RIGHT.** Binary notation reads in the opposite direction from the
  array indices. This is mistake number one; draw your example once, as above, and keep it
  in front of you.
- **Bits 6 to 15 are zero** and will stay so: the list only has 6 elements. A 64-bit
  integer represents — without the slightest change — a set drawn from a list of 6, of 20
  or of 64 elements; the spare bits simply lie dormant.
- **Two different sets give two different integers.** The correspondence is exact both
  ways: to each subset its integer, to each integer its subset.

## 3. Testing whether an element is present

To find out whether the element at index `i` is present, build an integer whose **only**
bit set is bit `i` — that is `1ULL << i` — and confront it with the set using `&`:

```c
if (E & (1ULL << i)) { /* element i is present */ }
```

`&` compares the two integers bit by bit and keeps a 1 only where **both** have one. Since
`1ULL << i` has a single bit, the result can only be `0` (absent) or `1ULL << i` (present).

**Example**, with `E = 38` from section 2.

Is element 2 present?

```
E           = 0000 0000 0010 0110      (38)
1ULL << 2   = 0000 0000 0000 0100      (4)
E & (1<<2)  = 0000 0000 0000 0100      (4)   → non-zero: PRESENT
```

And element 3?

```
E           = 0000 0000 0010 0110      (38)
1ULL << 3   = 0000 0000 0000 1000      (8)
E & (1<<3)  = 0000 0000 0000 0000      (0)   → zero: ABSENT
```

> **The trap not to fall into.** Write `1ULL << i`, never `1 << i`. `1` is a 32-bit `int`:
> from `i = 31` onwards, `1 << i` overflows and your program does anything at all
> **without reporting a thing**. With 64 possible elements, you will go through there.

The two neighbouring operations, for the record:

```c
E |=  (1ULL << i);    /* add element i     */
E &= ~(1ULL << i);    /* remove element i  */
```

## 4. Union and intersection

This is where the representation pays off: set operations become **a single machine
instruction**, whatever the size of the sets.

| sets | bits | C operator |
|---|---|---|
| union `A ∪ B` | 1 where one **or** the other has a 1 | `A \| B` |
| intersection `A ∩ B` | 1 where one **and** the other have a 1 | `A & B` |
| difference `A \ B` | in A and not in B | `A & ~B` |
| symmetric difference | in one or the other, not both | `A ^ B` |

**Example.** Take `A = {1, 2, 5}` again, and let `B = {0, 2, 3}`.

```
A = 0000 0000 0010 0110      (38)   = {1, 2, 5}
B = 0000 0000 0000 1101      (13)   = {0, 2, 3}
```

**Union** — keep a 1 everywhere at least one of the two has one:

```
A     = 0000 0000 0010 0110      (38)
B     = 0000 0000 0000 1101      (13)
A | B = 0000 0000 0010 1111      (47)   = {0, 1, 2, 3, 5}
```

**Intersection** — keep a 1 only where both have one:

```
A     = 0000 0000 0010 0110      (38)
B     = 0000 0000 0000 1101      (13)
A & B = 0000 0000 0000 0100      (4)    = {2}
```

Only element 2 belongs to both sets, and it is indeed the only bit that survives.

A few useful tests written with this:

```c
if ((A & B) == 0)  /* A and B are disjoint     */
if ((A & B) == A)  /* A is included in B       */
if (A == B)        /* A and B are the same set */
```

## 5. The lowest and the highest element present

A compiler knows how to count the zeros of an integer in a single instruction.

**The lowest index present** is the number of zeros **to the right** of the first `1` — the
trailing zeros. If bit 0 is set, there are no zeros to the right, and the lowest element is
indeed 0:

```c
int lowest = __builtin_ctzll(E);        /* count trailing zeros */
```

**The highest index present** follows from the zeros **to the left** — the leading zeros.
On 64 bits, the leftmost bit is bit 63, hence:

```c
int highest = 63 - __builtin_clzll(E);  /* count leading zeros */
```

**Example**, still with `E = 38 = {1, 2, 5}`, written this time on all 64 of its bits:

```
E = 000…000 0010 0110
    └─ 58 zeros ─┘  └┘ one zero on the right
```

- to the right of the first `1` there is **1** zero → `__builtin_ctzll(E) = 1` → the lowest
  element present is **1**. ✓
- to the left there are **58** zeros → `__builtin_clzll(E) = 58`, and `63 - 58 = 5` → the
  highest element present is **5**. ✓

> **The trap.** `__builtin_ctzll(0)` and `__builtin_clzll(0)` are **undefined**: on an
> empty set there is no "lowest element", and the function returns nothing sensible. Test
> `E != 0` before calling.

Two idioms that go with them:

```c
unsigned long long low = E & -E;    /* the set reduced to its lowest element */
E &= E - 1;                         /* remove the lowest element             */
```

`E & -E` isolates the lowest set bit; `E & (E - 1)` clears it. The second gives the usual
way to **walk through the elements of a set**, from lowest index to highest:

```c
unsigned long long rest = E;
while (rest) {
    int i = __builtin_ctzll(rest);   /* index of the lowest remaining element */
    /* ... do something with element i ... */
    rest &= rest - 1;                /* remove it, and start again            */
}
```

The loop runs exactly as many times as there are elements — not 64 times.

## 6. Counting the elements

The number of elements in the set is the number of bits set to 1:

```c
int how_many = __builtin_popcountll(E);     /* population count */
```

On `E = 38` it is 3 — elements 1, 2 and 5.

## 7. Depending on your language

All five accepted languages can do these three counts. Note the right-hand column: in Rust,
Java and Haskell the case of the zero integer is **defined** and equals 64, where C and C++
leave it undefined.

| | C / C++ | Rust | Java | Haskell (`Data.Bits`) | on 0 |
|---|---|---|---|---|---|
| trailing zeros | `__builtin_ctzll(x)` | `x.trailing_zeros()` | `Long.numberOfTrailingZeros(x)` | `countTrailingZeros x` | C/C++: **undefined** |
| leading zeros | `__builtin_clzll(x)` | `x.leading_zeros()` | `Long.numberOfLeadingZeros(x)` | `countLeadingZeros x` | C/C++: **undefined** |
| number of 1s | `__builtin_popcountll(x)` | `x.count_ones()` | `Long.bitCount(x)` | `popCount x` | 0 everywhere |

In C++20, `<bit>` offers the standard names `std::countr_zero`, `std::countl_zero` and
`std::popcount`, which are preferable to the GCC-specific `__builtin_` ones.

The type to use: `unsigned long long` in C and C++, `u64` in Rust, `long` in Java (careful,
it is signed — prefer the `Long` methods over `>>`), `Word64` in Haskell.

## 8. What this representation does not do

It is **free**: a set fits in a register, union and intersection cost one instruction, and
so does the membership test.

But it makes nothing fast by itself. It changes the way you **write** a set, not the
**number** of sets your program looks at — and that number is what decides whether your
program finishes. A list of 64 elements has 2⁶⁴ subsets; no representation, however
compact, will change anything about that.

In other words: it is a tool, not a method.
