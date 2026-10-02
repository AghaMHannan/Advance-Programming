# s0-ex02 — The True Quine

## Exercise 2 — The True Quine

**Problem statement.** Same contract as exercise 1 — read an integer `x`, print your source
code `x` times — with one additional restriction: **your program must not open any file**.
It therefore cannot re-read its own source; it must reconstruct it. This is a *quine* in
the strict sense.

The restriction isn't just a guideline: it's enforced. The validator runs your program with
`open`, `openat`, `fopen`, and `freopen` intercepted; on the first call, your program is
killed and the exercise is failed.

**Accepted languages: C, C++, Rust, and Haskell.** Not Java, and that's not an oversight:
the Java virtual machine opens files just to start up, and the restriction kills it before
your first line runs. There's no reasonable workaround on that front.

**Submission constraints.** In the `s0-ex02/` folder of your repository:

- **exactly one** source file named `quine.<extension>` — `quine.c`, `quine.cpp`,
  `quine.rs`, or `quine.hs`;
- a `Makefile` declaring the two contract targets, for example:

```make
.PHONY: compile run
compile:
	cc -O2 -std=c11 -o quine quine.c        # or g++ -O2 -std=c++17 -o quine quine.cpp
	                                        # or rustc -O -o quine quine.rs
	                                        # or ghc -O2 -o quine quine.hs
run:
	./quine
```

**What gets checked**, in this order:

1. input `0`: your program prints nothing;
2. **round trip**: the output for `x = 1` is recompiled, and the resulting program must in
   turn print the same source — this is what distinguishes a quine from a program that
   merely prints *a* quine;
3. input `2`;
4. six inputs drawn at random between 3 and 100.
