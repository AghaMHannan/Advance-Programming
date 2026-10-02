# s0-ex01 — Le programme miroir

## Exercice 1 — Le programme miroir

**Énoncé.** Écrivez un programme qui lit un entier `x` sur l'entrée standard, puis imprime
sur la sortie standard **le code source de votre propre programme**, `x` fois de suite.

Entrée : une ligne contenant `x` (`x ≥ 0`). Sortie : votre fichier source, répété `x` fois.
Si `x` vaut 0, votre programme n'imprime rien.

**Contraintes de rendu.** Dans le dossier `s0-ex01/` de votre dépôt :

- **exactement un** fichier source nommé `miroir.<extension>` — c'est lui que votre
  programme doit imprimer, et c'est lui que le juge comparera à votre sortie ;
- un `Makefile` déclarant les deux cibles du contrat :

```make
.PHONY: compile run
compile:
	cc -Wall -Wextra -std=c11 -O2 -o miroir miroir.c
run:
	./miroir
```

Tous les langages de l'image sont acceptés — C, C++, Rust, Java, Haskell — à condition que
le fichier s'appelle `miroir.…` (ou `Miroir.java`, la casse imposée par Java étant admise).

**Lire son propre fichier est autorisé** : `__FILE__` en C et C++, `include_str!` en Rust.
C'est la voie normale pour cet exercice.

**Petit jeu.** `x` est petit. Vérifiez d'abord que vous lisez bien `x`, et que vous
n'imprimez votre source ni une fois de trop ni une fois de moins — l'erreur la plus
fréquente est un retour à la ligne surnuméraire entre deux copies.

**Gros jeu.** `x` vaut 10 000. N'accumulez pas une chaîne géante en mémoire : écrivez
votre source `x` fois au fil de l'eau.

**Un détail qui compte.** Le juge compare les sorties après normalisation : les espaces en
fin de ligne et les lignes vides finales sont ignorés. Inutile donc de vous battre avec le
saut de ligne final — mais évitez les espaces en fin de ligne dans votre source, ils
seraient gommés d'un côté comme de l'autre sans que vous compreniez pourquoi.

**Provenance.** Grand classique de la programmation — le *quine*, ou programme
auto-reproducteur — décliné en « quine × x » pour exercer la lecture de l'entrée.

**Notions.** Lecture de l'entrée standard, écriture sur la sortie standard, écriture au fil
de l'eau, accès au fichier source depuis le programme, contrat `Makefile` du juge.
