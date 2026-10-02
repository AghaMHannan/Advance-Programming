# s1-03-cavalier — La tournée du cavalier

**Énoncé.** Un cavalier est posé sur la case (1,1) d'un échiquier `n × n` — coin en haut à
gauche. Il se déplace en L, comme aux échecs : deux cases dans une direction, une case
perpendiculairement. Faites-lui visiter **chacune des `n²` cases exactement une fois**. La
tournée n'a pas à revenir à son point de départ.

**Comment se déplace le cavalier.** Un saut, c'est **deux cases dans une direction, puis
une case perpendiculairement**. Le cavalier ne se déplace donc jamais en ligne droite, et
il n'atterrit jamais sur une case voisine de la sienne : il saute par-dessus. Depuis une
case au large de l'échiquier, huit sauts sont possibles — les huit `*` autour du cavalier
`C` :

```
    . * . * .
    * . . . *
    . . C . .
    * . . . *
    . * . * .
```

Ces huit sauts sont les huit couples `(±1, ±2)` et `(±2, ±1)`, ajoutés à la rangée et à la
colonne courantes. Le cavalier change donc de couleur de case à chaque saut, et les huit
destinations forment un anneau qui laisse intactes les seize cases les plus proches.

Près d'un bord, les sauts qui sortent de l'échiquier n'existent tout simplement pas. Depuis
la case de départ `(1,1)`, dans le coin, il n'en reste que **deux** :

```
    C . . . .
    . . * . .
    . * . . .
    . . . . .
    . . . . .
```

Une instance contient **plusieurs cas**, un par ligne. Vous ne savez pas combien : lisez
jusqu'à la fin de l'entrée.

**Format d'entrée.** Chaque ligne contient un seul entier : la taille `n` de l'échiquier.

| | `n` |
|---|---|
| **petit jeu** | `1 ≤ n ≤ 8` |
| **gros jeu** | `9 ≤ n ≤ 64` |

**Format de sortie.** **Une ligne par ligne d'entrée**, dans le même ordre. Chaque ligne
contient les `n²` cases visitées **dans l'ordre**, chacune donnée par sa rangée puis sa
colonne (numérotées à partir de 1), le tout séparé par des espaces :

```
l_1 c_1 l_2 c_2 … l_{n²} c_{n²}
```

soit `2n²` entiers sur une seule ligne. La première case doit être `1 1`. Si aucune tournée
n'existe, écrivez `IMPOSSIBLE` sur la ligne — et rien d'autre.

**Votre réponse n'a pas à être la nôtre.** Un échiquier admet en général un nombre
astronomique de tournées valides ; le juge ne compare pas votre sortie à une réponse type,
il la **vérifie** : bon nombre de cases, toutes distinctes, toutes sur l'échiquier, départ
en (1,1), et chaque pas est bien un pas de cavalier. Toute tournée correcte est acceptée.

**L'instance publique.** `exemple.in` contient quatre cas — `n` = 1, 3, 5 et 8 — et
`exemple.out` une réponse valide pour chacun. Regardez-la : le cas `n = 3` répond
`IMPOSSIBLE` (la case centrale d'un échiquier 3 × 3 n'est atteignable par aucun mouvement
de cavalier), et le cas `n = 1` répond `1 1` — un échiquier d'une case est visité
intégralement sans bouger.

**Un second jeu d'essai.** `exemple-difficile.in` contient un échiquier à l'échelle du
gros jeu, et `exemple-difficile.out` **une** tournée valide — pas la seule. **Le juge ne
l'évalue pas**, et ne compare pas non plus votre tournée à celle-ci : toute tournée
correcte convient. Ce fichier est là pour que vous éprouviez vous-même la tenue de votre
programme. Une approche qui convient au petit jeu peut y tourner très longtemps.

**Un exemple.** La tournée que `exemple.out` donne pour `n = 5`, reportée sur l'échiquier —
chaque case porte son rang de visite :

```
       c1   c2   c3   c4   c5
 l1     1   16   21   10    7
 l2    22   11    8   15   20
 l3    17    2   25    6    9
 l4    12   23    4   19   14
 l5     3   18   13   24    5
```

**Contraintes de rendu.** Dans le dossier `s1-03-cavalier/` de votre dépôt : vos sources,
et un `Makefile` déclarant les deux cibles du contrat.

```make
.PHONY: compile run
compile:
	cc -Wall -Wextra -std=c11 -O2 -o cavalier cavalier.c
run:
	./cavalier
```

Cinq langages sont installés sur les postes comme dans l'image du juge : **C, C++17, Rust,
Java et Haskell**. Il n'y a **aucun gestionnaire de paquets** et **aucun accès réseau** :
bibliothèque standard uniquement. Le nom du fichier est libre — c'est votre `Makefile` qui
dit comment le compiler et comment le lancer.

**Attention à la profondeur de récursion.** À `n = 64`, une tournée compte 4 096 cases. Si
vous descendez récursivement d'un appel par case, vous empilez 4 096 cadres : c'est sans
danger en C, mais des langages plus généreux en variables locales par cadre s'en
souviennent.

**Ce que le juge vous répond.** Le vérificateur nomme le premier défaut trouvé et le cas où
il l'a trouvé : « case 3 (line 3 of your output): (4,4) to (5,5) is not a knight move », ou
« the tour stops after 37 squares, 81 were expected ». Un rendu qui échoue sur un seul
échiquier ne ressemble donc pas à un rendu qui ne marche pas.
