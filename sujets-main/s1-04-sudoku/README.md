# s1-04-sudoku — Sudoku de compétition

**Énoncé.** Résolvez des grilles de sudoku : une grille 9 × 9 à remplir avec les chiffres 1
à 9, de sorte que chaque **rangée**, chaque **colonne** et chacun des neuf **blocs 3 × 3**
contienne les neuf chiffres une fois chacun. Chaque grille de l'entrée admet **une et une
seule** solution.

Une instance contient **plusieurs grilles**, une par ligne. Vous ne savez pas combien :
lisez jusqu'à la fin de l'entrée.

**Format d'entrée.** Chaque ligne contient les 81 cases de la grille, **rangée par rangée**,
sans séparateur : un chiffre `1`–`9` pour une case donnée, un point `.` pour une case vide.

```
.....4.21.2...1.6...42..8..43.5.2..771..9854.5.6.1...8.41....7585..46.9.67.1254.3
```

est donc la grille dont la première rangée est `. . . . . 4 . 2 1`, la deuxième
`. 2 . . . 1 . 6 .`, et ainsi de suite.

| | indices donnés par grille | nombre de grilles |
|---|---|---|
| **petit jeu** | 34 | 30 |
| **gros jeu** | 22 à 27 | **1 000** |

**Format de sortie.** **Une ligne par ligne d'entrée**, dans le même ordre : les 81 chiffres
de la grille résolue, sans séparateur ni point. Rien d'autre sur la sortie standard : ni
en-tête, ni numéro de grille, ni ligne de séparation.

**L'instance publique.** `exemple.in` contient trois grilles largement remplies, et
`exemple.out` leurs solutions. Elles se résolvent à la main si le cœur vous en dit, et c'est
d'ailleurs conseillé une fois : ce que vous ferez alors sans y penser — « cette case ne peut
plus être qu'un 7 », « dans ce bloc, le 4 n'a plus qu'une place » — est exactement ce qui
sépare les deux jeux de données de cet exercice.

**Un second jeu d'essai.** `exemple-difficile.in` contient **cent grilles** à
l'échelle du gros jeu, et `exemple-difficile.out` leurs solutions. **Le juge ne l'évalue
pas** : il est là pour que vous éprouviez vous-même la tenue de votre programme, en
comparant votre sortie à l'attendu avec `diff`. Cent grilles, et non une : sur cet
exercice, ce n'est pas une grille isolée qui met une approche naïve en difficulté, c'est
leur nombre.

**Un exemple.** La première grille de `exemple.in` relue neuf caractères par rangée, et sa
solution — que le juge attend, elle, sur une seule ligne de 81 chiffres :

```
. . . . . 4 . 2 1        9 8 7 6 5 4 3 2 1
. 2 . . . 1 . 6 .        3 2 5 9 8 1 7 6 4
. . 4 2 . . 8 . .        1 6 4 2 7 3 8 5 9
4 3 . 5 . 2 . . 7        4 3 8 5 6 2 9 1 7
7 1 . . 9 8 5 4 .        7 1 2 3 9 8 5 4 6
5 . 6 . 1 . . . 8        5 9 6 4 1 7 2 3 8
. 4 1 . . . . 7 5        2 4 1 8 3 9 6 7 5
8 5 . . 4 6 . 9 .        8 5 3 7 4 6 1 9 2
6 7 . 1 2 5 4 . 3        6 7 9 1 2 5 4 8 3
```

**Contraintes de rendu.** Dans le dossier `s1-04-sudoku/` de votre dépôt : vos sources, et un
`Makefile` déclarant les deux cibles du contrat.

```make
.PHONY: compile run
compile:
	cc -Wall -Wextra -std=c11 -O2 -o sudoku sudoku.c
run:
	./sudoku
```

Cinq langages sont installés sur les postes comme dans l'image du juge : **C, C++17, Rust,
Java et Haskell**. Il n'y a **aucun gestionnaire de paquets** et **aucun accès réseau** :
bibliothèque standard uniquement. Le nom du fichier est libre — c'est votre `Makefile` qui
dit comment le compiler et comment le lancer.

**Ce que le juge vous répond.** La comparaison est exacte, ligne à ligne : « first
difference on line 348 ». Les espaces en fin de ligne et les lignes vides finales ne sont
pas significatifs.
