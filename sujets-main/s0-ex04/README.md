# s0-ex04 — Un très grand Fibonacci

## Exercice 4 — Un très grand Fibonacci

**Énoncé.** La suite de Fibonacci est définie par

```
F(0) = 0
F(1) = 1
F(n) = F(n−1) + F(n−2)   pour n ≥ 2
```

soit `0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, …`

On vous donne des entiers `n`. Pour chacun, calculez `F(n)` **modulo 1 000 000 000**.

Une instance contient **plusieurs cas**, un par ligne. Vous ne savez pas combien : lisez
jusqu'à la fin de l'entrée.

**Format d'entrée.** Chaque ligne contient un seul entier `n`. Les bornes ne sont pas les
mêmes d'un jeu de données à l'autre :

| | `n` |
|---|---|
| **petit jeu** | `0 ≤ n ≤ 10^7` |
| **gros jeu** | `0 ≤ n ≤ 10^18` |

**Format de sortie.** **Une ligne par ligne d'entrée**, dans le même ordre, contenant le
seul entier `F(n) mod 1 000 000 000`. Rien d'autre sur la sortie standard : ni en-tête, ni
numéro de cas, ni ligne de séparation.

**L'instance publique.** `exemple.in` contient les deux cas suivants, et `exemple.out` les
deux réponses :

```
36                 →  14930352
0                  →  0
```

`F(36) = 14 930 352` tient encore sous le milliard : sur ces deux cas, le modulo ne se voit
pas. Il commence à mordre à `n = 45`, où `F(45) = 1 134 903 170` dépasse le milliard pour la
première fois — pensez-y avant de conclure que votre programme marche.

**Réduire au fil de l'eau.** Vous n'aurez jamais à construire `F(n)` en entier : `F(10^18)`
compte plus de 200 millions de chiffres. Comme à `s0-ex03`, le reste ne dépend que des
restes, pour la somme comme pour le produit :

```
(x + y) mod m  =  ( (x mod m) + (y mod m) ) mod m
(x × y) mod m  =  ( (x mod m) × (y mod m) ) mod m
```

Réduisez donc modulo 1 000 000 000 après chaque opération, et rien de ce que vous manipulez
ne dépassera le milliard.

**Contraintes de rendu.** Dans le dossier `s0-ex04/` de votre dépôt : vos sources, et un
`Makefile` déclarant les deux cibles du contrat.

```make
.PHONY: compile run
compile:
	cc -Wall -Wextra -std=c11 -O2 -o fibonacci fibonacci.c
run:
	./fibonacci
```

Tous les langages de l'image sont acceptés — C, C++, Rust, Java, Haskell. Le nom du fichier
est libre : c'est votre `Makefile` qui dit comment le compiler et comment le lancer.

**Deux choses à surveiller.** La taille de vos entiers — un débordement ne se voit pas, il
donne simplement une mauvaise réponse. Et la profondeur de vos appels, si vous écrivez une
version récursive.

**Ce que le juge vous répond.** Le vérificateur de cet exercice compte les cas justes et
vous le dit, même quand il en reste de faux : « 248/250 cases correct — first wrong answer
on line 12 ». Un rendu qui ne rate que deux cas ne ressemble donc pas à un rendu qui ne
marche pas, et vous saurez lequel des deux vous avez écrit.
