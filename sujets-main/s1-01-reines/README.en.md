# s1-01-reines — The Susceptible Queens

**Problem statement.** On an `n × n` chessboard where some squares are **forbidden**, we
want to place `n` queens that do not attack one another — two queens share neither a row,
nor a column, nor a diagonal — and none of which occupies a forbidden square. **How many
different placements exist?**

An instance contains **several cases**, one per line. You don't know how many: read
until the end of the input.

**Input format.** Each line describes a complete chessboard: the integer `n`, followed by
the `n` rows of the board, each made up of `n` characters, all separated by spaces. The
character `.` marks a free square and `*` a forbidden square.

```
n row_1 row_2 … row_n
```

So `4 .... .*.. .... ...*` describes a 4 × 4 chessboard in which squares (2,2) and (4,4)
are forbidden.

The bounds are not the same from one dataset to another:

| | `n` | forbidden squares |
|---|---|---|
| **small dataset** | `1 ≤ n ≤ 11` | up to 15% of the board |
| **large dataset** | `n = 15` | up to 26% of the board |

**Output format.** **One line per input line**, in the same order, containing only the
number of placements. Nothing else on standard output: no header, no case number, no
separator line.

**Two conventions.** You must place **exactly `n` queens**, no fewer. And a forbidden
square **does not stop attacks**: it only forbids placing a queen there. Two queens facing
each other along a diagonal attack each other, whether the squares between them are free,
forbidden, or occupied.

**The public instance.** `exemple.in` contains the following three cases, and
`exemple.out` the three answers:

```
8 ........ ........ ........ ........ ........ ........ ........ ........   →  92
4 .... .... .... ....                                                       →  2
3 ... ... ...                                                               →  0
```

The first is the eight queens problem, whose answer — 92 — has been known since 1850: it's
your canary. The second can be checked by hand. The third is a reminder that a board can
admit **no** placement at all, in which case `0` must be printed.

**A second test set.** `exemple-difficile.in` holds one instance at the scale of the
large dataset, and `exemple-difficile.out` the expected answer. **The judge does not
evaluate it**: it is there for you to test how your own program holds up, comparing your
output against the expected one with `diff`. An approach that suits the small dataset may
run there for a very long time — which is exactly what this file is for finding out early.

**An example.** The two placements for the empty 4 × 4 board, `Q` denoting a queen:

```
. Q . .          . . Q .
. . . Q          Q . . .
Q . . .          . . . Q
. . Q .          . Q . .
```

**A cheat sheet, should you need it.** [`diagonales.en.md`](diagonales.en.md) recalls how
to designate the rows, the columns and the two families of diagonals of a chessboard, and
how to number them so they can serve as array indices. It is coordinate geometry, not a
method — decide for yourself whether it helps.

**Submission requirements.** In the `s1-01-reines/` folder of your repository: your
source files, and a `Makefile` declaring the two targets of the contract.

```make
.PHONY: compile run
compile:
	cc -Wall -Wextra -std=c11 -O2 -o reines reines.c
run:
	./reines
```

Five languages are installed on the workstations, as in the judge's image: **C, C++17,
Rust, Java, and Haskell**. There is **no package manager** and **no network access**:
standard library only. The file name is free — it's your `Makefile` that specifies how to
compile it and how to run it.

**What the judge tells you.** The comparison is exact, line by line: "first difference on
line 7". Trailing spaces at the end of a line and trailing blank lines are not
significant.
