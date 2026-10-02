# s1-03-cavalier — The knight's tour

**Statement.** A knight is placed on square (1,1) of an `n × n` chessboard — the
top-left corner. It moves in an L-shape, as in chess: two squares in one direction,
one square perpendicular to it. Make it visit **each of the `n²` squares exactly
once**. The tour does not have to return to its starting point.

**How the knight moves.** One jump is **two squares in one direction, then one square
perpendicular to it**. The knight therefore never moves in a straight line, and never lands
on a square adjacent to its own: it jumps over them. From a square well inside the board,
eight jumps are possible — the eight `*` around the knight `C`:

```
    . * . * .
    * . . . *
    . . C . .
    * . . . *
    . * . * .
```

Those eight jumps are the eight pairs `(±1, ±2)` and `(±2, ±1)`, added to the current row
and column. The knight thus changes square colour with every jump, and the eight
destinations form a ring that leaves the sixteen nearest squares untouched.

Near an edge, the jumps that leave the board simply do not exist. From the starting square
`(1,1)`, in the corner, only **two** remain:

```
    C . . . .
    . . * . .
    . * . . .
    . . . . .
    . . . . .
```

An instance contains **several cases**, one per line. You don't know how many: read
until the end of the input.

**Input format.** Each line contains a single integer: the size `n` of the chessboard.

| | `n` |
|---|---|
| **small dataset** | `1 ≤ n ≤ 8` |
| **large dataset** | `9 ≤ n ≤ 64` |

**Output format.** **One line per input line**, in the same order. Each line contains
the `n²` squares visited **in order**, each given by its row then its column (numbered
starting from 1), all separated by spaces:

```
r_1 c_1 r_2 c_2 … r_{n²} c_{n²}
```

that is, `2n²` integers on a single line. The first square must be `1 1`. If no tour
exists, write `IMPOSSIBLE` on the line — and nothing else.

**Your answer does not have to be ours.** A chessboard generally admits an
astronomical number of valid tours; the judge does not compare your output to a
reference answer, it **checks** it: correct number of squares, all distinct, all on
the board, start at (1,1), and each step is indeed a knight's move. Any correct tour
is accepted.

**The public instance.** `exemple.in` contains four cases — `n` = 1, 3, 5 and 8 — and
`exemple.out` a valid answer for each. Take a look at it: the case `n = 3` answers
`IMPOSSIBLE` (the center square of a 3 × 3 chessboard cannot be reached by any
knight's move), and the case `n = 1` answers `1 1` — a one-square chessboard is fully
visited without moving.

**A second test set.** `exemple-difficile.in` holds one board at the scale of the large
dataset, and `exemple-difficile.out` **one** valid tour — not the only one. **The judge
does not evaluate it**, and does not compare your tour against this one either: any correct
tour will do. This file is there for you to test how your own program holds up. An approach
that suits the small dataset may run there for a very long time.

**An example.** The tour that `exemple.out` gives for `n = 5`, laid out on the
chessboard — each square carries its visit order:

```
       c1   c2   c3   c4   c5
 r1     1   16   21   10    7
 r2    22   11    8   15   20
 r3    17    2   25    6    9
 r4    12   23    4   19   14
 r5     3   18   13   24    5
```

**Submission constraints.** In the `s1-03-cavalier/` folder of your repository: your
source code, and a `Makefile` declaring the two targets of the contract.

```make
.PHONY: compile run
compile:
	cc -Wall -Wextra -std=c11 -O2 -o cavalier cavalier.c
run:
	./cavalier
```

Five languages are installed on the machines, as in the judge's image: **C, C++17,
Rust, Java and Haskell**. There is **no package manager** and **no network access**:
standard library only. The file name is free — it's your `Makefile` that says how to
compile it and how to run it.

**Watch out for recursion depth.** At `n = 64`, a tour has 4,096 squares. If you
recurse one call per square, you stack 4,096 frames: this is harmless in C, but
languages more generous with local variables per frame will feel it.

**What the judge tells you.** The checker names the first defect found and the case
where it found it: "case 3 (line 3 of your output): (4,4) to (5,5) is not a knight
move", or "the tour stops after 37 squares, 81 were expected". So a submission that
fails on a single chessboard does not look like a submission that doesn't work at all.
