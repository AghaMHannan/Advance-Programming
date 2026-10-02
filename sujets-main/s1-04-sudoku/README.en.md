# s1-04-sudoku — Competition sudoku

**Statement.** Solve sudoku grids: a 9 × 9 grid to be filled with the digits 1 to 9,
so that each **row**, each **column**, and each of the nine 3 × 3 **blocks** contains
the nine digits exactly once. Each grid in the input admits **one and only one**
solution.

An instance contains **several grids**, one per line. You don't know how many: read
until the end of the input.

**Input format.** Each line contains the 81 cells of the grid, **row by row**, with no
separator: a digit `1`–`9` for a filled cell, a period `.` for an empty cell.

```
.....4.21.2...1.6...42..8..43.5.2..771..9854.5.6.1...8.41....7585..46.9.67.1254.3
```

is therefore the grid whose first row is `. . . . . 4 . 2 1`, second row
`. 2 . . . 1 . 6 .`, and so on.

| | given clues per grid | number of grids |
|---|---|---|
| **small dataset** | 34 | 30 |
| **large dataset** | 22 to 27 | **1,000** |

**Output format.** **One line per input line**, in the same order: the 81 digits of
the solved grid, with no separator or period. Nothing else on standard output: no
header, no grid number, no separator line.

**The public instance.** `exemple.in` contains three largely filled-in grids, and
`exemple.out` their solutions. They can be solved by hand if you feel like it, and it
is actually advisable to try once: what you will then do without thinking about it —
"this cell can now only be a 7", "in this block, the 4 has only one place left" — is
exactly what separates the two datasets of this exercise.

**A second test set.** `exemple-difficile.in` holds **one hundred grids** at the scale
of the large dataset, and `exemple-difficile.out` their solutions. **The judge does not
evaluate it**: it is there for you to test how your own program holds up, comparing your
output against the expected one with `diff`. One hundred grids, not one: on this exercise it
is not a single grid that defeats a naive approach, it is their number.

**An example.** The first grid of `exemple.in`, read back nine characters per row, and
its solution — which the judge expects, in turn, on a single line of 81 digits:

```
. . . . . 4 . 2 1        9 8 7 6 5 4 3 2 1
. 2 . . . 1 . 6 .        3 2 5 9 8 1 7 6 4
. . 4 2 . . 8 . .        1 6 4 2 7 3 8 5 9
4 3 . 5 . 2 . . 7        4 3 8 5 6 2 9 1 7
7 1 . . 9 8 5 4 .        7 1 2 3 9 8 5 4 6
5 . 6 . 1 . . . 8        5 9 6 4 1 7 2 3 8
. 4 1 . . . . 7 5        2 4 1 8 3 9 6 7 5
8 5 . . 4 6 . 9 .        8 5 3 7 4 6 1 9 2
6 7 . 1 2 5 4 . 3        6 7 9 1 2 5 4 8 3
```

**Submission constraints.** In the `s1-04-sudoku/` folder of your repository: your
source code, and a `Makefile` declaring the two targets of the contract.

```make
.PHONY: compile run
compile:
	cc -Wall -Wextra -std=c11 -O2 -o sudoku sudoku.c
run:
	./sudoku
```

Five languages are installed on the machines, as in the judge's image: **C, C++17,
Rust, Java and Haskell**. There is **no package manager** and **no network access**:
standard library only. The file name is free — it's your `Makefile` that says how to
compile it and how to run it.

**What the judge tells you.** The comparison is exact, line by line: "first
difference on line 348". Trailing spaces at the end of a line and trailing blank
lines are not significant.
