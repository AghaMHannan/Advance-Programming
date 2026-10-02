# s1-06-caisse — The shared fund

**Statement.** The `n` members of an association have each paid in an amount `a_1`,
…, `a_n`. The treasurer wants to know how many **subsets of members** paid in
**exactly** `x` in total.

An instance contains **several cases**, one per line. You don't know how many: read
until the end of the input.

**Input format.** Each line describes a complete case, as space-separated integers:

```
n x a_1 a_2 … a_n
```

The bounds are not the same from one dataset to another:

| | `n` | `x` | `a_i` |
|---|---|---|---|
| **small dataset** | `1 ≤ n ≤ 24` | `0 ≤ x ≤ 5·10^10` | `1 ≤ a_i ≤ 10^9` |
| **large dataset** | `41 ≤ n ≤ 42` | `0 ≤ x ≤ 5·10^10` | `1 ≤ a_i ≤ 10^9` |

**Output format.** **One line per input line**, in the same order, containing only
the number of subsets. Nothing else on standard output: no header, no case number,
no separator line.

**Two conventions**, so that no case has two possible answers.

1. **The empty set is a subset**: its sum is 0, so a case with `x = 0` counts at
   least that one answer.
2. **Members are distinct, even when their payments are equal.** We are counting
   sets of *people*, not sets of *values*: if three members each paid in 5, there
   are three different subsets that total 5, not just one.

**The public instance.** `exemple.in` contains the following three cases, and
`exemple.out` the three answers:

```
4 3 1 2 3 4          →  2
5 0 5 5 5 5 5        →  1
6 7 1 1 1 2 2 3      →  8
```

The first can be checked by hand: `{3}` and `{1, 2}` total 3, and nothing else. The
second is convention 1: only the empty set is worth 0, since all payments are
strictly positive. The third is convention 2: its eight subsets are listed just
below.

**A second test set.** `exemple-difficile.in` holds one instance at the scale of the
large dataset, and `exemple-difficile.out` the expected answer. **The judge does not
evaluate it**: it is there for you to test how your own program holds up, comparing your
output against the expected one with `diff`. An approach that suits the small dataset may
run there for a very long time — which is exactly what this file is for finding out early.

**An example.** On `6 7 1 1 1 2 2 3`, with members numbered in the order their
payments are given, here are the eight subsets that total 7:

| subset | payments |
|---|---|
| `{4, 5, 6}` | 2 + 2 + 3 |
| `{1, 2, 3, 4, 5}` | 1 + 1 + 1 + 2 + 2 |
| `{1, 2, 4, 6}` | 1 + 1 + 2 + 3 |
| `{1, 3, 4, 6}` | 1 + 1 + 2 + 3 |
| `{2, 3, 4, 6}` | 1 + 1 + 2 + 3 |
| `{1, 2, 5, 6}` | 1 + 1 + 2 + 3 |
| `{1, 3, 5, 6}` | 1 + 1 + 2 + 3 |
| `{2, 3, 5, 6}` | 1 + 1 + 2 + 3 |

**Watch out for the size of your integers.** Two places overflow, and neither one
complains: the **sums**, which climb beyond 4·10^10, and the **answer itself**,
which can exceed several hundred billion. An overflow is invisible — it simply
gives a wrong answer.

**A cheat sheet, should you need it.** [`bitset.en.md`](bitset.en.md) explains how
to represent a set of at most 64 elements using the bits of a single integer: testing
whether an element is present, taking a union or an intersection, finding the lowest and
highest element present. It is a toolbox, not a method — decide for yourself whether it
helps here.

**Submission constraints.** In the `s1-06-caisse/` folder of your repository: your
source code, and a `Makefile` declaring the two targets of the contract.

```make
.PHONY: compile run
compile:
	cc -Wall -Wextra -std=c11 -O2 -o caisse caisse.c
run:
	./caisse
```

Five languages are installed on the machines, as in the judge's image: **C, C++17,
Rust, Java and Haskell**. There is **no package manager** and **no network access**:
standard library only. The file name is free — it's your `Makefile` that says how to
compile it and how to run it.

**What the judge tells you.** The comparison is exact, line by line: "first
difference on line 7". Trailing spaces at the end of a line and trailing blank lines
are not significant.
