# s0-ex02 — La vraie quine

## Exercice 2 — La vraie quine

**Énoncé.** Même contrat qu'à l'exercice 1 — lire un entier `x`, imprimer votre code source
`x` fois — avec une interdiction supplémentaire : **votre programme ne doit ouvrir aucun
fichier**. Il ne peut donc pas relire son propre source ; il doit le reconstruire. C'est un
*quine* au sens strict.

L'interdiction n'est pas une consigne : elle est appliquée. Le validateur exécute votre
programme avec `open`, `openat`, `fopen` et `freopen` détournés ; au premier appel, votre
programme est tué et l'exercice est perdu.

**Langages acceptés : C, C++, Rust et Haskell.** Pas Java, et ce n'est pas un oubli : la
machine virtuelle Java ouvre des fichiers rien que pour démarrer, et l'interdiction la tue
avant votre première ligne. Aucun contournement raisonnable n'existe de ce côté.

**Contraintes de rendu.** Dans le dossier `s0-ex02/` de votre dépôt :

- **exactement un** fichier source nommé `quine.<extension>` — `quine.c`, `quine.cpp`,
  `quine.rs` ou `quine.hs` ;
- un `Makefile` déclarant les deux cibles du contrat, par exemple :

```make
.PHONY: compile run
compile:
	cc -O2 -std=c11 -o quine quine.c        # ou g++ -O2 -std=c++17 -o quine quine.cpp
	                                        # ou rustc -O -o quine quine.rs
	                                        # ou ghc -O2 -o quine quine.hs
run:
	./quine
```

**Ce qui est vérifié**, dans cet ordre :

1. entrée `0` : votre programme n'imprime rien ;
2. **aller-retour** : la sortie pour `x = 1` est recompilée, et le programme obtenu doit à
   son tour imprimer le même source — c'est ce qui distingue une quine d'un programme qui
   imprime *une* quine ;
3. entrée `2` ;
4. six entrées tirées au hasard entre 3 et 100.
