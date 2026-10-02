# s1-05-fours — L'équilibrage des fours

**Énoncé.** Une boulangerie industrielle dispose de `k` fours identiques et doit cuire `n`
fournées, la `i`-ième demandant `t_i` minutes. Chaque fournée est affectée à un four, et un
four traite ses fournées l'une après l'autre. Le *makespan* est l'instant où le **dernier
four** termine, c'est-à-dire la plus grande des charges. Quel est le makespan **minimal** ?

Une instance contient **plusieurs cas**, un par ligne. Vous ne savez pas combien : lisez
jusqu'à la fin de l'entrée.

**Format d'entrée.** Chaque ligne décrit un cas complet, en entiers séparés par des
espaces :

```
n k t_1 t_2 … t_n
```

Les bornes ne sont pas les mêmes d'un jeu de données à l'autre :

| | `n` | `k` | `t_i` |
|---|---|---|---|
| **petit jeu** | `1 ≤ n ≤ 13` | `1 ≤ k ≤ 3` | `1 ≤ t_i ≤ 7 000` |
| **gros jeu** | `n = 26` | `k = 5` | `1 ≤ t_i ≤ 20 000` |

**Format de sortie.** **Une ligne par ligne d'entrée**, dans le même ordre, contenant le
seul makespan minimal. Rien d'autre sur la sortie standard : ni en-tête, ni numéro de cas,
ni ligne de séparation.

**Trois conventions.** L'ordre des fournées à l'intérieur d'un four n'a aucune importance —
seule compte la somme de ses durées. Un four peut rester **vide**, sa charge vaut alors 0 ;
c'est ce qui arrive nécessairement quand `n < k`. Et les fours sont **interchangeables** :
deux affectations qui ne diffèrent que par le nom des fours sont la même.

**L'instance publique.** `exemple.in` contient les trois cas suivants, et `exemple.out` les
trois réponses :

```
6 3 4 4 4 4 4 4        →  8
5 1 3 7 2 8 5          →  25
7 3 5 5 4 4 3 3 3      →  9
```

Le premier est le cas parfait : six fournées de 4 minutes sur trois fours, deux chacun,
8 minutes. Le deuxième n'a qu'un four : il n'y a rien à répartir, la réponse est la somme.
Le troisième vaut la peine d'être fait à la main : la somme est 27, donc aucun découpage en
trois ne descend sous 9.

**Un second jeu d'essai.** `exemple-difficile.in` contient une instance à l'échelle du
gros jeu, et `exemple-difficile.out` la réponse attendue. **Le juge ne l'évalue pas** :
elle est là pour que vous éprouviez vous-même la tenue de votre programme, en comparant
votre sortie à l'attendu avec `diff`. Une approche qui convient au petit jeu peut y tourner
très longtemps — c'est précisément ce que ce fichier sert à découvrir tôt.

**Un exemple.** Sur `7 3 5 5 4 4 3 3 3`, une répartition qui atteint les 9 minutes :

| four | fournées | charge |
|---|---|--:|
| A | 5, 4 | 9 |
| B | 5, 4 | 9 |
| C | 3, 3, 3 | 9 |

**Ce que vous cherchez est un minimum EXACT.** Une réponse approchée, même très bonne, est
comptée fausse. Deux valeurs faciles à calculer encadrent la réponse, et il est prudent de
les regarder avant de coder : la somme des durées divisée par `k` (arrondie au-dessus) et
la plus longue fournée sont chacune des minorants — mais **le minimum ne vaut pas toujours
le plus grand des deux**, et une répartition gloutonne ne l'atteint pas toujours non plus.

**Contraintes de rendu.** Dans le dossier `s1-05-fours/` de votre dépôt : vos sources, et un
`Makefile` déclarant les deux cibles du contrat.

```make
.PHONY: compile run
compile:
	cc -Wall -Wextra -std=c11 -O2 -o fours fours.c
run:
	./fours
```

Cinq langages sont installés sur les postes comme dans l'image du juge : **C, C++17, Rust,
Java et Haskell**. Il n'y a **aucun gestionnaire de paquets** et **aucun accès réseau** :
bibliothèque standard uniquement. Le nom du fichier est libre — c'est votre `Makefile` qui
dit comment le compiler et comment le lancer.

**Ce que le juge vous répond.** La comparaison est exacte, ligne à ligne : « first
difference on line 7 ». Les espaces en fin de ligne et les lignes vides finales ne sont pas
significatifs.
