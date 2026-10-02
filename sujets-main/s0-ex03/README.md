# s0-ex03 — Une très grosse puissance

## Exercice 3 — Une très grosse puissance

**Énoncé.** Pour trois entiers `a`, `b` et `m`, calculez `a^b mod m` — le reste de la
division de `a` puissance `b` par `m`.

Une instance contient **plusieurs cas**, un par ligne. Vous ne savez pas combien : lisez
jusqu'à la fin de l'entrée. Les instances cachées en comptent une vingtaine.

**Format d'entrée.** Chaque ligne contient trois entiers séparés par des espaces :

```
a b m
```

Les bornes ne sont pas les mêmes d'un jeu de données à l'autre :

| | `a` | `b` | `m` |
|---|---|---|---|
| **petit jeu** | `0 ≤ a ≤ 10^18` | `0 ≤ b ≤ 2·10^6` | `1 ≤ m ≤ 2·10^9` |
| **gros jeu** | `0 ≤ a ≤ 10^18` | `0 ≤ b ≤ 10^18` | `1 ≤ m ≤ 2·10^9` |

**Format de sortie.** **Une ligne par ligne d'entrée**, dans le même ordre, contenant le
seul entier `a^b mod m`. Rien d'autre sur la sortie standard : ni en-tête, ni numéro de
cas, ni ligne de séparation.

**Deux conventions**, pour qu'aucun cas n'ait deux réponses possibles : `a^0 = 1` quel que
soit `a`, y compris `0^0 = 1` ; et si `m = 1`, la réponse est `0`.

**L'instance publique.** `exemple.in` contient les deux cas suivants, et `exemple.out` les
deux réponses :

```
2 10 1000          →  24
5 0 7              →  1
```

Le premier vaut la peine d'être regardé : 2^10 = 1024, et 1024 mod 1000 = **24**. Si votre
programme répond `1024`, vous avez oublié le modulo — et vous le saurez avant même d'être
jugé, puisque c'est la seule instance dont vous avez la réponse.

**La multiplication modulaire, en deux minutes.** `x mod m` est le **reste** de la division
entière de `x` par `m` — l'opérateur `%` en C, C++, Rust et Java (`17 % 5` vaut `2`). Toutes
les valeurs de cet exercice sont positives ou nulles : vous n'aurez pas à vous soucier du
comportement de `%` sur les nombres négatifs.

La propriété sur laquelle repose tout l'exercice s'appelle la **multiplication modulaire** :

```
(x × y) mod m  =  ( (x mod m) × (y mod m) ) mod m
```

Autrement dit, **le reste d'un produit ne dépend que des restes des facteurs**. Vous n'avez
donc *jamais* à construire `a^b`, qui aurait des milliards de chiffres : vous pouvez réduire
modulo `m` après *chaque* multiplication, et le résultat final est identique.

Concrètement : partir de `r = 1 % m`, puis répéter `r = (r × a) % m`. Voici `7^5 mod 100`,
en réduisant à chaque pas :

| pas | calcul | `r` |
|---|---|---|
| départ | | `1` |
| × 7 | 1 × 7 = 7, reste 7 | `7` |
| × 7 | 7 × 7 = 49, reste 49 | `49` |
| × 7 | 49 × 7 = 343, reste 43 | `43` |
| × 7 | 43 × 7 = 301, reste 1 | `1` |
| × 7 | 1 × 7 = 7, reste 7 | `7` |

Or `7^5 = 16 807`, dont le reste par 100 vaut bien **7**. Aucun nombre manipulé n'a dépassé
343, là où `7^5` en vaut déjà 16 807.

La même règle vaut pour les carrés, qui sont des produits comme les autres :
`(x × x) mod m = ((x mod m) × (x mod m)) mod m`.

**Contraintes de rendu.** Dans le dossier `s0-ex03/` de votre dépôt : vos sources, et un
`Makefile` déclarant les deux cibles du contrat.

```make
.PHONY: compile run
compile:
	cc -Wall -Wextra -std=c11 -O2 -o puissance puissance.c
run:
	./puissance
```

Tous les langages de l'image sont acceptés — C, C++, Rust, Java, Haskell. Contrairement à
`s0-ex01`, le nom du fichier est libre : c'est votre `Makefile` qui dit comment le compiler
et comment le lancer.

**Attention à la taille de vos entiers.** Les valeurs de cet exercice sont grandes, et les
produits intermédiaires qu'elles engendrent le sont encore davantage. Choisissez vos types
en conséquence : un débordement ne se voit pas, il donne simplement une mauvaise réponse.

**Ce que le juge vous répond.** Le vérificateur de cet exercice compte les cas justes et
vous le dit, même quand il en reste de faux : « 19/20 cases correct — first wrong answer on
line 2 ». Un rendu qui ne rate qu'un cas limite ne ressemble donc pas à un rendu qui ne
marche pas, et vous saurez lequel des deux vous avez écrit.
