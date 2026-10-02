# s0-ex03 — A Very Large Power

## Exercise 3 — A Very Large Power

**Problem statement.** For three integers `a`, `b` and `m`, compute `a^b mod m` — the
remainder of `a` to the power `b` divided by `m`.

One instance holds **several cases**, one per line. You are not told how many: read until
the end of input. The hidden instances hold about twenty each.

**Input format.** Each line holds three space-separated integers:

```
a b m
```

The bounds are not the same from one data set to the other:

| | `a` | `b` | `m` |
|---|---|---|---|
| **small challenge** | `0 ≤ a ≤ 10^18` | `0 ≤ b ≤ 2·10^6` | `1 ≤ m ≤ 2·10^9` |
| **big challenge** | `0 ≤ a ≤ 10^18` | `0 ≤ b ≤ 10^18` | `1 ≤ m ≤ 2·10^9` |

**Output format.** **One line per input line**, in the same order, holding the single
integer `a^b mod m`. Nothing else on standard output: no header, no case number, no
separator line.

**Two conventions**, so that no case has two possible answers: `a^0 = 1` for every `a`,
including `0^0 = 1`; and if `m = 1`, the answer is `0`.

**The public instance.** `exemple.in` holds the two cases below, and `exemple.out` the two
answers:

```
2 10 1000          →  24
5 0 7              →  1
```

The first one is worth a look: 2^10 = 1024, and 1024 mod 1000 = **24**. If your program
answers `1024`, you forgot the modulo — and you will know it before being judged at all,
since this is the only instance whose answer you have.

**Modular multiplication in two minutes.** `x mod m` is the **remainder** of the integer
division of `x` by `m` — the `%` operator in C, C++, Rust and Java (`17 % 5` is `2`). Every
value in this exercise is non-negative, so you will not have to worry about how `%` behaves
on negative numbers.

The property the whole exercise rests on is called **modular multiplication**:

```
(x × y) mod m  =  ( (x mod m) × (y mod m) ) mod m
```

In other words, **the remainder of a product depends only on the remainders of its
factors**. So you *never* have to build `a^b`, which would have billions of digits: you can
reduce modulo `m` after *every* multiplication, and the final result is the same.

In practice: start from `r = 1 % m`, then repeat `r = (r × a) % m`. Here is `7^5 mod 100`,
reducing at every step:

| step | computation | `r` |
|---|---|---|
| start | | `1` |
| × 7 | 1 × 7 = 7, remainder 7 | `7` |
| × 7 | 7 × 7 = 49, remainder 49 | `49` |
| × 7 | 49 × 7 = 343, remainder 43 | `43` |
| × 7 | 43 × 7 = 301, remainder 1 | `1` |
| × 7 | 1 × 7 = 7, remainder 7 | `7` |

And indeed `7^5 = 16,807`, whose remainder modulo 100 is **7**. No number handled along the
way went above 343, whereas `7^5` is already 16,807.

The same rule holds for squares, which are products like any other:
`(x × x) mod m = ((x mod m) × (x mod m)) mod m`.

**Submission constraints.** In the `s0-ex03/` folder of your repository: your sources, and
a `Makefile` declaring the two contract targets.

```make
.PHONY: compile run
compile:
	cc -Wall -Wextra -std=c11 -O2 -o puissance puissance.c
run:
	./puissance
```

All languages in the image are accepted — C, C++, Rust, Java, Haskell. Unlike `s0-ex01`,
the file name is free: it is your `Makefile` that says how to compile it and how to run it.

**Mind the size of your integers.** The values in this exercise are large, and the
intermediate products they give rise to are larger still. Choose your types accordingly: an
overflow cannot be seen — it simply yields a wrong answer.

**What the judge tells you.** This exercise's checker counts the correct cases and says so,
even when some are still wrong: "19/20 cases correct — first wrong answer on line 2". A
submission that only misses one edge case therefore does not look like a submission that
does not work, and you will know which of the two you wrote.
