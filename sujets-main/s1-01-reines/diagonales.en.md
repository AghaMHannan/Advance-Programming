# Cheat sheet — rows, columns and diagonals of a chessboard

This document explains how to **designate** the four alignments of an `n × n` chessboard,
and how to number them so they can serve as array indices. It is coordinate geometry: it
says nothing about how to search for anything.

## 1. Locating a square

A square is a pair `(r, c)` — its row and its column, counted from 0:

```
        c=0  c=1  c=2  c=3  c=4
 r=0     .    .    .    .    .
 r=1     .    .    .    .    .
 r=2     .    .    .    .    .
 r=3     .    .    .    .    .
 r=4     .    .    .    .    .
```

Two squares are on the **same row** if `r` is the same, on the **same column** if `c` is
the same. Nothing surprising so far.

## 2. The two families of diagonals

There are two kinds of diagonal, and they behave differently.

A **`\`** diagonal goes down to the right: moving one square along it, `r` increases by 1
and `c` increases by 1. **Their difference `r - c` therefore does not change.**

A **`/`** diagonal goes up to the right: `r` decreases by 1 while `c` increases by 1.
**Their sum `r + c` does not change.**

Hence the complete test, in one expression:

```c
/* are squares (r1,c1) and (r2,c2) aligned? */
r1 == r2  ||  c1 == c2  ||  r1 - c1 == r2 - c2  ||  r1 + c1 == r2 + c2
/*   row       column        diagonal  \            diagonal  /        */
```

## 3. Numbering the diagonals

To use a diagonal as an **array index**, its number must be an integer between 0 and
something.

For the `/` ones this is immediate: `r + c` is 0 in the top-left corner and `2n - 2` in the
bottom-right corner. The numbering is ready to use.

For the `\` ones, `r - c` is `n - 1` in the top-right corner and `-(n - 1)` in the
bottom-left corner: **half the values are negative.** Shift them by `n - 1`:

```c
int rising_diagonal  = r + c;            /* "/" :  0 … 2n-2 */
int falling_diagonal = r - c + n - 1;    /* "\" :  0 … 2n-2 */
```

## 4. The full example

Here are the two numberings on a **5 × 5** board. On the left `r + c`, on the right
`r - c + 4`. Squares carrying the same number are on the same diagonal:

```
      "/"  :  r + c                  "\"  :  r - c + n - 1

      0  1  2  3  4                    4  3  2  1  0
      1  2  3  4  5                    5  4  3  2  1
      2  3  4  5  6                    6  5  4  3  2
      3  4  5  6  7                    7  6  5  4  3
      4  5  6  7  8                    8  7  6  5  4
```

Read the left grid slantwise, from the bottom-left corner towards the top-right: the `4`s do
form a `/` diagonal. On the right one, the `4`s run from the top-left corner down to the
bottom-right — a `\` diagonal.

Let us check on two squares. `(1, 3)` and `(3, 1)`: their sums are `4` and `4` — same `/`
diagonal. Their shifted differences are `2` and `6` — different `\` diagonals.

## 5. How many are there?

Both numberings run from 0 to `2n - 2`, that is **`2n - 1` diagonals in each family**. For a
5 × 5 board, 9 of each. For a 15 × 15 board, **29 of each**.

It is not `n`: the corner diagonals contain a single square, and there are almost twice as
many of them as there are rows. An array sized to `n` overflows.

> **The trap.** `r - c` is negative as soon as `c > r`, that is over the whole upper-right
> half of the board. In C, indexing an array with a negative number raises no error: the
> program reads or writes beside the array and starts giving wrong results elsewhere, long
> afterwards. Do not forget the `+ n - 1`.

## 6. What this document does not do

It gives a coordinate system, nothing more. Being able to designate a diagonal in constant
time says nothing about **which squares to try**, nor **in what order**, nor **when to
stop** — and that is where the difference lies between a program that answers and a program
that is still running tomorrow.

In other words: it is a tool, not a method.
