# s1-06-caisse — La caisse commune

**Énoncé.** Les `n` membres d'une association ont chacun versé une somme `a_1`, …, `a_n`.
Le trésorier veut savoir combien de **sous-ensembles de membres** ont versé **exactement**
`x` au total.

Une instance contient **plusieurs cas**, un par ligne. Vous ne savez pas combien : lisez
jusqu'à la fin de l'entrée.

**Format d'entrée.** Chaque ligne décrit un cas complet, en entiers séparés par des
espaces :

```
n x a_1 a_2 … a_n
```

Les bornes ne sont pas les mêmes d'un jeu de données à l'autre :

| | `n` | `x` | `a_i` |
|---|---|---|---|
| **petit jeu** | `1 ≤ n ≤ 24` | `0 ≤ x ≤ 5·10^10` | `1 ≤ a_i ≤ 10^9` |
| **gros jeu** | `41 ≤ n ≤ 42` | `0 ≤ x ≤ 5·10^10` | `1 ≤ a_i ≤ 10^9` |

**Format de sortie.** **Une ligne par ligne d'entrée**, dans le même ordre, contenant le
seul nombre de sous-ensembles. Rien d'autre sur la sortie standard : ni en-tête, ni numéro
de cas, ni ligne de séparation.

**Deux conventions**, pour qu'aucun cas n'ait deux réponses possibles.

1. **L'ensemble vide est un sous-ensemble** : sa somme vaut 0, donc un cas où `x = 0`
   compte au moins cette réponse-là.
2. **Les membres sont distincts, même quand leurs versements sont égaux.** On compte des
   ensembles de *personnes*, pas des ensembles de *valeurs* : si trois membres ont versé 5
   chacun, il y a trois sous-ensembles différents qui totalisent 5, pas un seul.

**L'instance publique.** `exemple.in` contient les trois cas suivants, et `exemple.out` les
trois réponses :

```
4 3 1 2 3 4          →  2
5 0 5 5 5 5 5        →  1
6 7 1 1 1 2 2 3      →  8
```

Le premier se vérifie à la main : `{3}` et `{1, 2}` totalisent 3, et rien d'autre. Le
deuxième est la convention 1 : seul l'ensemble vide vaut 0, puisque tous les versements
sont strictement positifs. Le troisième est la convention 2 : ses huit sous-ensembles sont
listés juste en dessous.

**Un second jeu d'essai.** `exemple-difficile.in` contient une instance à l'échelle du
gros jeu, et `exemple-difficile.out` la réponse attendue. **Le juge ne l'évalue pas** :
elle est là pour que vous éprouviez vous-même la tenue de votre programme, en comparant
votre sortie à l'attendu avec `diff`. Une approche qui convient au petit jeu peut y tourner
très longtemps — c'est précisément ce que ce fichier sert à découvrir tôt.

**Un exemple.** Sur `6 7 1 1 1 2 2 3`, les membres étant numérotés dans l'ordre où leurs
versements sont donnés, voici les huit sous-ensembles qui totalisent 7 :

| sous-ensemble | versements |
|---|---|
| `{4, 5, 6}` | 2 + 2 + 3 |
| `{1, 2, 3, 4, 5}` | 1 + 1 + 1 + 2 + 2 |
| `{1, 2, 4, 6}` | 1 + 1 + 2 + 3 |
| `{1, 3, 4, 6}` | 1 + 1 + 2 + 3 |
| `{2, 3, 4, 6}` | 1 + 1 + 2 + 3 |
| `{1, 2, 5, 6}` | 1 + 1 + 2 + 3 |
| `{1, 3, 5, 6}` | 1 + 1 + 2 + 3 |
| `{2, 3, 5, 6}` | 1 + 1 + 2 + 3 |

**Attention à la taille de vos entiers.** Deux endroits débordent, et aucun des deux ne
proteste : les **sommes**, qui montent au-delà de 4·10^10, et la **réponse elle-même**, qui
peut dépasser plusieurs centaines de milliards. Un débordement ne se voit pas, il donne
simplement une mauvaise réponse.

**Un aide-mémoire, si vous en avez l'usage.** [`bitset.md`](bitset.md) explique comment
représenter un ensemble d'au plus 64 éléments par les bits d'un seul entier : tester la
présence d'un élément, faire une union ou une intersection, trouver le plus petit et le
plus grand élément présent. C'est une boîte à outils, pas une marche à suivre — à vous de
voir si elle vous sert ici.

**Contraintes de rendu.** Dans le dossier `s1-06-caisse/` de votre dépôt : vos sources, et un
`Makefile` déclarant les deux cibles du contrat.

```make
.PHONY: compile run
compile:
	cc -Wall -Wextra -std=c11 -O2 -o caisse caisse.c
run:
	./caisse
```

Cinq langages sont installés sur les postes comme dans l'image du juge : **C, C++17, Rust,
Java et Haskell**. Il n'y a **aucun gestionnaire de paquets** et **aucun accès réseau** :
bibliothèque standard uniquement. Le nom du fichier est libre — c'est votre `Makefile` qui
dit comment le compiler et comment le lancer.

**Ce que le juge vous répond.** La comparaison est exacte, ligne à ligne : « first
difference on line 7 ». Les espaces en fin de ligne et les lignes vides finales ne sont pas
significatifs.
