# s0-ex01 — The Mirror Program

## Exercise 1 — The Mirror Program

**Problem statement.** Write a program that reads an integer `x` from standard input, then prints
**its own source code** to standard output, `x` times in a row.

Input: a line containing `x` (`x ≥ 0`). Output: your source file, repeated `x` times.
If `x` is 0, your program prints nothing.

**Submission constraints.** In the `s0-ex01/` folder of your repository:

- **exactly one** source file named `miroir.<extension>` — this is the file your
  program must print, and it's the one the judge will compare against your output;
- a `Makefile` declaring the two contract targets:

```make
.PHONY: compile run
compile:
	cc -Wall -Wextra -std=c11 -O2 -o miroir miroir.c
run:
	./miroir
```

All languages in the image are accepted — C, C++, Rust, Java, Haskell — provided that
the file is named `miroir.…` (or `Miroir.java`, the capitalization required by Java being allowed).

**Reading your own file is allowed**: `__FILE__` in C and C++, `include_str!` in Rust.
That's the normal approach for this exercise.

**Small challenge.** `x` is small. First check that you're reading `x` correctly, and that
you print your source neither one time too many nor one time too few — the most common
mistake is an extra newline between two copies.

**Big challenge.** `x` is 10,000. Don't accumulate one giant string in memory: write
your source `x` times on the fly (streaming).

**One detail that matters.** The judge compares outputs after normalization: trailing
spaces at the end of lines and trailing blank lines are ignored. So there's no need to
fuss over the final newline — but avoid trailing spaces in your source, since they'd be
stripped on one side but not necessarily understood as such.

**Origin.** A classic in programming — the *quine*, or self-reproducing program —
adapted here as "quine × x" to practice reading input.

**Concepts.** Reading standard input, writing to standard output, streaming output,
accessing the source file from within the program, the judge's `Makefile` contract.
