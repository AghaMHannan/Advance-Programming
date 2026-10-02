# Aide-mémoire — représenter un ensemble avec les bits d'un entier

Ce document explique une **représentation**, utile dès qu'on manipule des ensembles pris
dans une collection d'au plus **64 éléments**. Il ne traite d'aucun exercice en
particulier : à vous de juger s'il vous sert.

## 1. L'idée : un bit par élément

Vous disposez d'un tableau de `n` éléments, `n` allant de 0 à 64, et vous voulez désigner
un **sous-ensemble** de ces éléments. La manière habituelle est un tableau de booléens :

```c
int present[64];    /* present[i] = 1 si l'élément d'indice i est dans l'ensemble */
```

Un `unsigned long long` fait exactement 64 bits. Chacun de ces bits peut jouer le rôle
d'une case de ce tableau :

> **le bit d'indice `i` vaut 1 si l'élément d'indice `i` est présent, 0 s'il est absent.**

L'ensemble tout entier tient alors dans **une seule variable**. Un ensemble qui contient
trois éléments est un entier dont l'écriture binaire comporte **exactement trois `1`** —
peu importe lesquels, et peu importe la taille du tableau de départ.

Deux cas particuliers qui tombent juste tout seuls :

| ensemble | entier |
|---|---|
| l'ensemble vide | `0` |
| les 64 éléments présents | tous les bits à 1 |

## 2. Un exemple sur 16 bits

Prenons une liste de **6 éléments**, d'indices 0 à 5, et l'ensemble qui contient les
éléments **1, 2 et 5**. Sur 16 bits :

```
indice du bit :  15 14 13 12 11 10  9  8  7  6  5  4  3  2  1  0
        valeur :  0  0  0  0  0  0  0  0  0  0  1  0  0  1  1  0
                                               ↑        ↑  ↑
                                          élément 5     2  1
```

Soit `0000 0000 0010 0110` en binaire, c'est-à-dire **38** en décimal — parce que
`2^5 + 2^2 + 2^1 = 32 + 4 + 2 = 38`.

Trois remarques que l'on paie cher si on les découvre en déboguant :

- **Le bit 0 est à DROITE.** L'écriture binaire se lit dans le sens inverse des indices du
  tableau. C'est la source d'erreur numéro un ; dessinez votre exemple une fois, comme
  ci-dessus, et gardez-le sous les yeux.
- **Les bits 6 à 15 sont à zéro** et le resteront : la liste n'a que 6 éléments. Un entier
  de 64 bits représente sans changer d'un iota un ensemble pris dans une liste de 6, de 20
  ou de 64 éléments — les bits en trop dorment.
- **Deux ensembles différents donnent deux entiers différents.** La correspondance est
  exacte dans les deux sens : à chaque sous-ensemble son entier, à chaque entier son
  sous-ensemble.

## 3. Tester la présence d'un élément

Pour savoir si l'élément d'indice `i` est présent, on fabrique un entier dont **seul** le
bit `i` vaut 1 — c'est `1ULL << i` — et on le confronte à l'ensemble avec un `&` :

```c
if (E & (1ULL << i)) { /* l'élément i est présent */ }
```

Le `&` compare les deux entiers bit à bit et ne garde un 1 que là où les **deux** en ont
un. Comme `1ULL << i` n'a qu'un seul bit, le résultat ne peut être que `0` (absent) ou
`1ULL << i` (présent).

**Exemple**, avec `E = 38` de la section 2.

L'élément 2 est-il présent ?

```
E           = 0000 0000 0010 0110      (38)
1ULL << 2   = 0000 0000 0000 0100      (4)
E & (1<<2)  = 0000 0000 0000 0100      (4)   → non nul : PRÉSENT
```

Et l'élément 3 ?

```
E           = 0000 0000 0010 0110      (38)
1ULL << 3   = 0000 0000 0000 1000      (8)
E & (1<<3)  = 0000 0000 0000 0000      (0)   → nul : ABSENT
```

> **Le piège à ne pas rater.** Écrivez `1ULL << i`, jamais `1 << i`. `1` est un `int` de
> 32 bits : à partir de `i = 31`, `1 << i` déborde et votre programme fait n'importe quoi
> **sans rien signaler**. Avec 64 éléments possibles, vous passerez forcément par là.

Les deux opérations voisines, pour mémoire :

```c
E |=  (1ULL << i);    /* ajouter l'élément i    */
E &= ~(1ULL << i);    /* retirer l'élément i    */
```

## 4. Union et intersection

C'est là que la représentation paie : les opérations d'ensemble deviennent **une seule
instruction machine**, quelle que soit la taille des ensembles.

| ensembles | bits | opérateur C |
|---|---|---|
| union `A ∪ B` | 1 si l'un **ou** l'autre a un 1 | `A \| B` |
| intersection `A ∩ B` | 1 si l'un **et** l'autre ont un 1 | `A & B` |
| différence `A \ B` | dans A et pas dans B | `A & ~B` |
| différence symétrique | dans l'un ou l'autre, pas les deux | `A ^ B` |

**Exemple.** Reprenons `A = {1, 2, 5}` et prenons `B = {0, 2, 3}`.

```
A = 0000 0000 0010 0110      (38)   = {1, 2, 5}
B = 0000 0000 0000 1101      (13)   = {0, 2, 3}
```

**Union** — on garde un 1 partout où au moins l'un des deux en a un :

```
A     = 0000 0000 0010 0110      (38)
B     = 0000 0000 0000 1101      (13)
A | B = 0000 0000 0010 1111      (47)   = {0, 1, 2, 3, 5}
```

**Intersection** — on ne garde un 1 que là où les deux en ont un :

```
A     = 0000 0000 0010 0110      (38)
B     = 0000 0000 0000 1101      (13)
A & B = 0000 0000 0000 0100      (4)    = {2}
```

Seul l'élément 2 appartient aux deux ensembles, et c'est bien le seul bit qui survit.

Quelques tests utiles écrits avec ça :

```c
if ((A & B) == 0)  /* A et B sont disjoints           */
if ((A & B) == A)  /* A est inclus dans B             */
if (A == B)        /* A et B sont le même ensemble    */
```

## 5. Le plus petit et le plus grand élément présent

Un compilateur sait compter les zéros d'un entier en une instruction.

**Le plus petit indice présent** est le nombre de zéros **à droite** du premier `1` — les
« trailing zeros ». Si le bit 0 est à 1, il y a zéro zéro à droite, et le plus petit
élément est bien le 0 :

```c
int plus_petit = __builtin_ctzll(E);        /* count trailing zeros */
```

**Le plus grand indice présent** se déduit des zéros **à gauche** — les « leading
zeros ». Sur 64 bits, le bit le plus à gauche est le 63, donc :

```c
int plus_grand = 63 - __builtin_clzll(E);   /* count leading zeros */
```

**Exemple**, toujours avec `E = 38 = {1, 2, 5}`, écrit cette fois sur ses 64 bits :

```
E = 000…000 0010 0110
    └─ 58 zéros ─┘  └┘ un zéro à droite
```

- à droite du premier `1`, il y a **1** zéro → `__builtin_ctzll(E) = 1` → le plus petit
  élément présent est le **1**. ✓
- à gauche, il y a **58** zéros → `__builtin_clzll(E) = 58`, et `63 - 58 = 5` → le plus
  grand élément présent est le **5**. ✓

> **Le piège.** `__builtin_ctzll(0)` et `__builtin_clzll(0)` sont **indéfinis** : sur un
> ensemble vide, il n'y a pas de « plus petit élément » et la fonction ne renvoie rien de
> sensé. Testez `E != 0` avant d'appeler.

Deux tournures qui vont avec :

```c
unsigned long long bas = E & -E;    /* l'ensemble réduit à son plus petit élément */
E &= E - 1;                         /* retirer le plus petit élément              */
```

`E & -E` isole le bit de poids faible ; `E & (E - 1)` l'efface. La deuxième donne la façon
habituelle de **parcourir les éléments d'un ensemble**, du plus petit indice au plus
grand :

```c
unsigned long long reste = E;
while (reste) {
    int i = __builtin_ctzll(reste);   /* indice du plus petit élément restant */
    /* ... faire quelque chose de l'élément i ... */
    reste &= reste - 1;               /* on le retire, et on recommence        */
}
```

La boucle tourne exactement autant de fois qu'il y a d'éléments — pas 64 fois.

## 6. Compter les éléments

Le nombre d'éléments de l'ensemble est le nombre de bits à 1 :

```c
int combien = __builtin_popcountll(E);      /* population count */
```

Sur `E = 38`, il vaut 3 — les éléments 1, 2 et 5.

## 7. Selon votre langage

Les cinq langages acceptés savent tous faire ces trois comptages. Notez la colonne de
droite : en Rust, en Java et en Haskell, le cas de l'entier nul est **défini** et vaut 64,
là où C et C++ le laissent indéfini.

| | C / C++ | Rust | Java | Haskell (`Data.Bits`) | sur 0 |
|---|---|---|---|---|---|
| zéros à droite | `__builtin_ctzll(x)` | `x.trailing_zeros()` | `Long.numberOfTrailingZeros(x)` | `countTrailingZeros x` | C/C++ : **indéfini** |
| zéros à gauche | `__builtin_clzll(x)` | `x.leading_zeros()` | `Long.numberOfLeadingZeros(x)` | `countLeadingZeros x` | C/C++ : **indéfini** |
| nombre de 1 | `__builtin_popcountll(x)` | `x.count_ones()` | `Long.bitCount(x)` | `popCount x` | 0 partout |

En C++20, `<bit>` offre les noms standards `std::countr_zero`, `std::countl_zero` et
`std::popcount`, qui valent mieux que les `__builtin_` propres à GCC.

Le type à utiliser : `unsigned long long` en C et C++, `u64` en Rust, `long` en Java
(attention, il est signé — préférez les méthodes de `Long` plutôt que `>>`), `Word64` en
Haskell.

## 8. Ce que cette représentation ne fait pas

Elle est **gratuite** : un ensemble tient dans un registre, l'union et l'intersection
coûtent une instruction, le test d'appartenance aussi.

Mais elle ne rend rien rapide par elle-même. Elle change la façon d'**écrire** un
ensemble, pas le **nombre** d'ensembles que votre programme regarde — et c'est ce nombre-là
qui décide si votre programme finit. Une liste de 64 éléments a 2⁶⁴ sous-ensembles ;
aucune représentation, si compacte soit-elle, n'y changera quoi que ce soit.

Autrement dit : c'est un outil, pas une méthode.
