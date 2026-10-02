# s1-02-cartographe — Le cartographe économe

**Énoncé.** Une carte comporte `n` régions numérotées de 1 à `n`, et `m` frontières. Deux
régions séparées par une frontière doivent recevoir des couleurs différentes. **Combien de
couleurs faut-il au minimum** pour colorier toute la carte ?

Une instance contient **plusieurs cas**, un par ligne. Vous ne savez pas combien : lisez
jusqu'à la fin de l'entrée.

**Format d'entrée.** Chaque ligne décrit une carte complète, en entiers séparés par des
espaces : le nombre de régions, le nombre de frontières, puis les `m` frontières, chacune
donnée par les deux régions qu'elle sépare.

```
n m u_1 v_1 u_2 v_2 … u_m v_m
```

Les bornes ne sont pas les mêmes d'un jeu de données à l'autre :

| | `n` | `m` |
|---|---|---|
| **petit jeu** | `1 ≤ n ≤ 11` | `0 ≤ m ≤ 30` |
| **gros jeu** | `n = 55` | `650 ≤ m ≤ 820` |

**Format de sortie.** **Une ligne par ligne d'entrée**, dans le même ordre, contenant le
seul nombre minimal de couleurs. Rien d'autre sur la sortie standard : ni en-tête, ni numéro
de cas, ni ligne de séparation.

**Trois conventions.** La carte n'est pas nécessairement d'un seul tenant, et n'est pas
nécessairement planaire — ce n'est pas parce qu'on l'appelle une carte que quatre couleurs
suffisent. Une frontière ne sépare jamais une région d'elle-même, et deux régions ne sont
séparées que par une frontière au plus. Enfin, une carte **sans aucune frontière** se
colorie avec **une** couleur : la réponse n'est jamais 0 dès qu'il y a au moins une région.

**L'instance publique.** `exemple.in` contient les quatre cas suivants, et `exemple.out` les
quatre réponses :

```
6 8 1 2 2 3 1 3 3 4 4 5 3 5 5 6 6 1     →  3
4 6 1 2 1 3 1 4 2 3 2 4 3 4             →  4
5 0                                     →  1
6 6 1 2 2 3 3 4 4 5 5 6 6 1             →  2
```

Les deux du milieu sont les repères à avoir en tête : quatre régions toutes frontalières
deux à deux exigent quatre couleurs — aucune économie n'est possible — tandis que cinq
régions sans frontière se contentent d'une seule. Le dernier est un anneau de six régions.
Le premier, lui, demande de chercher un peu.

**Un second jeu d'essai.** `exemple-difficile.in` contient une instance à l'échelle du
gros jeu, et `exemple-difficile.out` la réponse attendue. **Le juge ne l'évalue pas** :
elle est là pour que vous éprouviez vous-même la tenue de votre programme, en comparant
votre sortie à l'attendu avec `diff`. Une approche qui convient au petit jeu peut y tourner
très longtemps — c'est précisément ce que ce fichier sert à découvrir tôt.

**Un exemple.** L'anneau `6 6 1 2 2 3 3 4 4 5 5 6 6 1` se colorie en alternant :

| région | 1 | 2 | 3 | 4 | 5 | 6 |
|---|---|---|---|---|---|---|
| couleur | A | B | A | B | A | B |

La réponse est `2`. Le même anneau à cinq régions demande `3`.

**Ce que vous cherchez est un minimum EXACT.** Une réponse approchée, même très bonne, est
comptée fausse. Deux quantités faciles à calculer encadrent la réponse, et il est prudent de
les regarder avant de coder : un **groupe de régions toutes frontalières deux à deux** force
autant de couleurs qu'il compte de régions (minorant), et n'importe quel coloriage que vous
savez construire en fournit un majorant. Mais **ces deux bornes ne se rejoignent pas** sur
les cartes du gros jeu : entre les deux, il faut décider, et décider veut dire prouver qu'un
coloriage avec une couleur de moins n'existe pas.

**Un aide-mémoire, si vous en avez l'usage.** [`graphe.md`](graphe.md) explique comment
lire une liste de frontières et ranger une carte en mémoire — liste de voisins, matrice
d'adjacence, ligne de bits — et ce que chaque rangement rend facile ou coûteux. C'est une
boîte à outils, pas une marche à suivre.

**Contraintes de rendu.** Dans le dossier `s1-02-cartographe/` de votre dépôt : vos
sources, et un `Makefile` déclarant les deux cibles du contrat.

```make
.PHONY: compile run
compile:
	cc -Wall -Wextra -std=c11 -O2 -o carte carte.c
run:
	./carte
```

Cinq langages sont installés sur les postes comme dans l'image du juge : **C, C++17, Rust,
Java et Haskell**. Il n'y a **aucun gestionnaire de paquets** et **aucun accès réseau** :
bibliothèque standard uniquement. Le nom du fichier est libre — c'est votre `Makefile` qui
dit comment le compiler et comment le lancer.

**Ce que le juge vous répond.** La comparaison est exacte, ligne à ligne : « first
difference on line 7 ». Les espaces en fin de ligne et les lignes vides finales ne sont pas
significatifs.
