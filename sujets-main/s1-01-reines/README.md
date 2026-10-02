# s1-01-reines — Les reines susceptibles

**Énoncé.** Sur un échiquier `n × n` dont certaines cases sont **interdites**, on veut
placer `n` reines qui ne s'attaquent pas mutuellement — deux reines ne partagent ni ligne,
ni colonne, ni diagonale — et dont aucune n'occupe une case interdite. **Combien de
placements différents existe-t-il ?**

Une instance contient **plusieurs cas**, un par ligne. Vous ne savez pas combien : lisez
jusqu'à la fin de l'entrée.

**Format d'entrée.** Chaque ligne décrit un échiquier complet : l'entier `n`, puis les `n`
rangées de l'échiquier, chacune formée de `n` caractères, le tout séparé par des espaces.
Le caractère `.` marque une case libre et `*` une case interdite.

```
n rangée_1 rangée_2 … rangée_n
```

Ainsi `4 .... .*.. .... ...*` décrit un échiquier 4 × 4 dont les cases (2,2) et (4,4) sont
interdites.

Les bornes ne sont pas les mêmes d'un jeu de données à l'autre :

| | `n` | cases interdites |
|---|---|---|
| **petit jeu** | `1 ≤ n ≤ 11` | jusqu'à 15 % de l'échiquier |
| **gros jeu** | `n = 15` | jusqu'à 26 % de l'échiquier |

**Format de sortie.** **Une ligne par ligne d'entrée**, dans le même ordre, contenant le
seul nombre de placements. Rien d'autre sur la sortie standard : ni en-tête, ni numéro de
cas, ni ligne de séparation.

**Deux conventions.** Il faut placer **exactement `n` reines**, pas moins. Et une case
interdite **n'arrête pas les attaques** : elle interdit seulement qu'on y pose une reine.
Deux reines qui se regardent le long d'une diagonale s'attaquent, que les cases entre elles
soient libres, interdites ou occupées.

**L'instance publique.** `exemple.in` contient les trois cas suivants, et `exemple.out` les
trois réponses :

```
8 ........ ........ ........ ........ ........ ........ ........ ........   →  92
4 .... .... .... ....                                                       →  2
3 ... ... ...                                                               →  0
```

Le premier est le problème des huit reines, dont la réponse — 92 — est connue depuis 1850 :
c'est votre canari. Le deuxième se vérifie à la main. Le troisième rappelle qu'un échiquier
peut n'admettre **aucun** placement, et qu'il faut alors imprimer `0`.

**Un second jeu d'essai.** `exemple-difficile.in` contient une instance à l'échelle du
gros jeu, et `exemple-difficile.out` la réponse attendue. **Le juge ne l'évalue pas** :
elle est là pour que vous éprouviez vous-même la tenue de votre programme, en comparant
votre sortie à l'attendu avec `diff`. Une approche qui convient au petit jeu peut y tourner
très longtemps — c'est précisément ce que ce fichier sert à découvrir tôt.

**Un exemple.** Les deux placements de l'échiquier 4 × 4 vide, `Q` pour une reine :

```
. Q . .          . . Q .
. . . Q          Q . . .
Q . . .          . . . Q
. . Q .          . Q . .
```

**Un aide-mémoire, si vous en avez l'usage.** [`diagonales.md`](diagonales.md) rappelle
comment désigner les rangées, les colonnes et les deux familles de diagonales d'un
échiquier, et comment les numéroter pour s'en servir comme indices de tableau. C'est de la
géométrie de coordonnées, pas une marche à suivre — à vous de voir si elle vous sert.

**Contraintes de rendu.** Dans le dossier `s1-01-reines/` de votre dépôt : vos sources, et un
`Makefile` déclarant les deux cibles du contrat.

```make
.PHONY: compile run
compile:
	cc -Wall -Wextra -std=c11 -O2 -o reines reines.c
run:
	./reines
```

Cinq langages sont installés sur les postes comme dans l'image du juge : **C, C++17, Rust,
Java et Haskell**. Il n'y a **aucun gestionnaire de paquets** et **aucun accès réseau** :
bibliothèque standard uniquement. Le nom du fichier est libre — c'est votre `Makefile` qui
dit comment le compiler et comment le lancer.

**Ce que le juge vous répond.** La comparaison est exacte, ligne à ligne : « first
difference on line 7 ». Les espaces en fin de ligne et les lignes vides finales ne sont pas
significatifs.
