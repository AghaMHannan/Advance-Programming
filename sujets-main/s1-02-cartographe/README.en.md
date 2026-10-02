# s1-02-cartographe — The frugal cartographer

**Statement.** A map has `n` regions numbered from 1 to `n`, and `m` borders. Two
regions separated by a border must be given different colors. **What is the minimum
number of colors** needed to color the whole map?

An instance contains **several cases**, one per line. You don't know how many: read
until the end of the input.

**Input format.** Each line describes a complete map, as space-separated integers: the
number of regions, the number of borders, then the `m` borders, each given by the two
regions it separates.

```
n m u_1 v_1 u_2 v_2 … u_m v_m
```

The bounds are not the same from one dataset to another:

| | `n` | `m` |
|---|---|---|
| **small dataset** | `1 ≤ n ≤ 11` | `0 ≤ m ≤ 30` |
| **large dataset** | `n = 55` | `650 ≤ m ≤ 820` |

**Output format.** **One line per input line**, in the same order, containing only the
minimum number of colors. Nothing else on standard output: no header, no case number,
no separator line.

**Three conventions.** The map is not necessarily connected, and not necessarily
planar — it's not because it's called a "map" that four colors are enough. A border
never separates a region from itself, and two regions are separated by at most one
border. Finally, a map **with no border at all** is colored with **one** color: the
answer is never 0 as soon as there is at least one region.

**The public instance.** `exemple.in` contains the following four cases, and
`exemple.out` the four answers:

```
6 8 1 2 2 3 1 3 3 4 4 5 3 5 5 6 6 1     →  3
4 6 1 2 1 3 1 4 2 3 2 4 3 4             →  4
5 0                                     →  1
6 6 1 2 2 3 3 4 4 5 5 6 6 1             →  2
```

The two in the middle are the reference points to keep in mind: four regions all
bordering each other pairwise require four colors — no saving is possible — while five
regions with no border make do with just one. The last one is a ring of six regions.
The first one requires a bit more searching.

**A second test set.** `exemple-difficile.in` holds one instance at the scale of the
large dataset, and `exemple-difficile.out` the expected answer. **The judge does not
evaluate it**: it is there for you to test how your own program holds up, comparing your
output against the expected one with `diff`. An approach that suits the small dataset may
run there for a very long time — which is exactly what this file is for finding out early.

**An example.** The ring `6 6 1 2 2 3 3 4 4 5 5 6 6 1` is colored by alternating:

| region | 1 | 2 | 3 | 4 | 5 | 6 |
|---|---|---|---|---|---|---|
| color | A | B | A | B | A | B |

The answer is `2`. The same ring with five regions requires `3`.

**What you are looking for is an EXACT minimum.** An approximate answer, even a very
good one, is counted wrong. Two easily computed quantities bound the answer, and it is
wise to look at them before coding: a **group of regions all bordering each other
pairwise** forces as many colors as it has regions (lower bound), and any coloring you
know how to construct provides an upper bound. But **these two bounds do not meet** on
the maps of the large dataset: between the two, you have to decide, and deciding means
proving that a coloring with one fewer color does not exist.

**A cheat sheet, should you need it.** [`graphe.en.md`](graphe.en.md) explains how to read
a list of borders and store a map in memory — neighbour list, adjacency matrix, row of bits
— and what each arrangement makes cheap or costly. It is a toolbox, not a method.

**Submission constraints.** In the `s1-02-cartographe/` folder of your repository: your
source code, and a `Makefile` declaring the two targets of the contract.

```make
.PHONY: compile run
compile:
	cc -Wall -Wextra -std=c11 -O2 -o carte carte.c
run:
	./carte
```

Five languages are installed on the machines, as in the judge's image: **C, C++17,
Rust, Java and Haskell**. There is **no package manager** and **no network access**:
standard library only. The file name is free — it's your `Makefile` that says how to
compile it and how to run it.

**What the judge tells you.** The comparison is exact, line by line: "first
difference on line 7". Trailing spaces at the end of a line and trailing blank lines
are not significant.
