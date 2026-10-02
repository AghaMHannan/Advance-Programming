# s1-05-fours — Balancing the ovens

**Statement.** An industrial bakery has `k` identical ovens and must bake `n`
batches, the `i`-th taking `t_i` minutes. Each batch is assigned to an oven, and an
oven processes its batches one after another. The *makespan* is the moment the
**last oven** finishes, i.e. the largest of the loads. What is the **minimum**
makespan?

An instance contains **several cases**, one per line. You don't know how many: read
until the end of the input.

**Input format.** Each line describes a complete case, as space-separated integers:

```
n k t_1 t_2 … t_n
```

The bounds are not the same from one dataset to another:

| | `n` | `k` | `t_i` |
|---|---|---|---|
| **small dataset** | `1 ≤ n ≤ 13` | `1 ≤ k ≤ 3` | `1 ≤ t_i ≤ 7,000` |
| **large dataset** | `n = 26` | `k = 5` | `1 ≤ t_i ≤ 20,000` |

**Output format.** **One line per input line**, in the same order, containing only
the minimum makespan. Nothing else on standard output: no header, no case number, no
separator line.

**Three conventions.** The order of the batches within an oven does not matter at
all — only the sum of its durations counts. An oven can remain **empty**, in which
case its load is 0; this necessarily happens when `n < k`. And the ovens are
**interchangeable**: two assignments that differ only in the naming of the ovens are
the same.

**The public instance.** `exemple.in` contains the following three cases, and
`exemple.out` the three answers:

```
6 3 4 4 4 4 4 4        →  8
5 1 3 7 2 8 5          →  25
7 3 5 5 4 4 3 3 3      →  9
```

The first is the perfect case: six 4-minute batches on three ovens, two each,
8 minutes. The second has only one oven: there is nothing to distribute, the answer
is the sum. The third is worth doing by hand: the sum is 27, so no split into three
goes below 9.

**A second test set.** `exemple-difficile.in` holds one instance at the scale of the
large dataset, and `exemple-difficile.out` the expected answer. **The judge does not
evaluate it**: it is there for you to test how your own program holds up, comparing your
output against the expected one with `diff`. An approach that suits the small dataset may
run there for a very long time — which is exactly what this file is for finding out early.

**An example.** On `7 3 5 5 4 4 3 3 3`, a distribution that reaches 9 minutes:

| oven | batches | load |
|---|---|--:|
| A | 5, 4 | 9 |
| B | 5, 4 | 9 |
| C | 3, 3, 3 | 9 |

**What you are looking for is an EXACT minimum.** An approximate answer, even a very
good one, is counted wrong. Two easily computed values bound the answer, and it is
wise to look at them before coding: the sum of the durations divided by `k` (rounded
up) and the longest single batch are each lower bounds — but **the minimum is not
always the larger of the two**, and a greedy distribution does not always reach it
either.

**Submission constraints.** In the `s1-05-fours/` folder of your repository: your
source code, and a `Makefile` declaring the two targets of the contract.

```make
.PHONY: compile run
compile:
	cc -Wall -Wextra -std=c11 -O2 -o fours fours.c
run:
	./fours
```

Five languages are installed on the machines, as in the judge's image: **C, C++17,
Rust, Java and Haskell**. There is **no package manager** and **no network access**:
standard library only. The file name is free — it's your `Makefile` that says how to
compile it and how to run it.

**What the judge tells you.** The comparison is exact, line by line: "first
difference on line 7". Trailing spaces at the end of a line and trailing blank lines
are not significant.
