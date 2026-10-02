# s0-ex04 — A Very Large Fibonacci

## Exercise 4 — A Very Large Fibonacci

**Problem statement.** The Fibonacci sequence is defined by

```
F(0) = 0
F(1) = 1
F(n) = F(n−1) + F(n−2)   for n ≥ 2
```

that is, `0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, …`

You are given integers `n`. For each one, compute `F(n)` **modulo 1,000,000,000**.

One instance holds **several cases**, one per line. You are not told how many: read until
the end of input.

**Input format.** Each line holds a single integer `n`. The bounds are not the same from one
data set to the other:

| | `n` |
|---|---|
| **small challenge** | `0 ≤ n ≤ 10^7` |
| **big challenge** | `0 ≤ n ≤ 10^18` |

**Output format.** **One line per input line**, in the same order, holding the single
integer `F(n) mod 1,000,000,000`. Nothing else on standard output: no header, no case
number, no separator line.

**The public instance.** `exemple.in` holds the two cases below, and `exemple.out` the two
answers:

```
36                 →  14930352
0                  →  0
```

`F(36) = 14,930,352` still fits under a billion: on these two cases the modulo does not show.
It starts to bite at `n = 45`, where `F(45) = 1,134,903,170` exceeds a billion for the first
time — keep that in mind before concluding that your program works.

**Reduce as you go.** You will never have to build `F(n)` in full: `F(10^18)` has more than
200 million digits. As in `s0-ex03`, the remainder depends only on the remainders, for sums
as well as for products:

```
(x + y) mod m  =  ( (x mod m) + (y mod m) ) mod m
(x × y) mod m  =  ( (x mod m) × (y mod m) ) mod m
```

So reduce modulo 1,000,000,000 after every operation, and nothing you handle will ever go
above a billion.

**Submission constraints.** In the `s0-ex04/` folder of your repository: your sources, and a
`Makefile` declaring the two contract targets.

```make
.PHONY: compile run
compile:
	cc -Wall -Wextra -std=c11 -O2 -o fibonacci fibonacci.c
run:
	./fibonacci
```

All languages in the image are accepted — C, C++, Rust, Java, Haskell. The file name is
free: it is your `Makefile` that says how to compile it and how to run it.

**Two things to watch.** The size of your integers — an overflow cannot be seen, it simply
yields a wrong answer. And the depth of your calls, if you write a recursive version.

**What the judge tells you.** This exercise's checker counts the correct cases and says so,
even when some are still wrong: "248/250 cases correct — first wrong answer on line 12". A
submission that only misses two cases therefore does not look like a submission that does
not work, and you will know which of the two you wrote.
