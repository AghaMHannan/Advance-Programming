# Aide-mémoire — lire et représenter un graphe

Ce document explique comment **ranger en mémoire** une carte donnée sous forme de liste de
frontières, et ce que chaque rangement rend facile ou coûteux. Il ne dit rien de ce qu'on
peut ensuite en faire.

## 1. Ce que donne l'entrée

Une ligne décrit une carte entière : le nombre de régions, le nombre de frontières, puis
les frontières, chacune donnée par les deux régions qu'elle sépare.

```
6 8 1 2 2 3 1 3 3 4 4 5 3 5 5 6 6 1
│ │ └───────────── les 8 frontières ─────────────┘
│ └── m = 8 frontières
└──── n = 6 régions
```

Les frontières arrivent **dans un ordre quelconque** : ne comptez pas dessus. Et `m` peut
valoir 0 — une carte sans aucune frontière est une carte valide.

## 2. Une frontière va dans les deux sens

C'est l'erreur la plus fréquente, et elle est silencieuse. La frontière `1 2` dit que la
région 1 touche la région 2 **et** que la région 2 touche la région 1. Si vous n'enregistrez
qu'un seul sens, la moitié de votre carte est fausse et rien ne proteste :

```c
adj[a][b] = 1;
adj[b][a] = 1;   /* ← celle-ci s'oublie */
```

## 3. Trois rangements

**La liste de voisins.** Pour chaque région, la liste de celles qu'elle touche, et sa
longueur à côté. C'est le bon choix quand on veut parcourir les voisins d'une région. Les
cartes de cet exercice ayant au plus 55 régions, un tableau fixe suffit et évite toute
allocation :

```c
int voisins[64][64];       /* voisins[i][0 … degre[i]-1] */
int degre[64] = {0};

voisins[a][degre[a]++] = b;
voisins[b][degre[b]++] = a;
```

**La matrice d'adjacence.** Un tableau `n × n`, `adj[i][j]` valant 1 si `i` et `j` se
touchent. Elle répond en temps constant à « ces deux régions se touchent-elles ? », ce que
la liste ne sait faire qu'en parcourant.

```c
int adj[64][64] = {0};
```

**Une ligne de bits par région.** C'est la matrice, mais chaque ligne tenue dans **un seul
entier de 64 bits** : le bit `j` de `adj[i]` vaut 1 si les régions `i` et `j` se touchent.
Les cartes de cet exercice ont au plus 55 régions, donc une ligne tient tout entière dans
un `unsigned long long`.

```c
unsigned long long adj[64];
adj[a] |= 1ULL << b;
adj[b] |= 1ULL << a;
```

L'intérêt : l'ensemble des voisins d'une région devient une valeur unique, qu'on peut
comparer, réunir ou intersecter d'une instruction. Le document
[`bitset.md`](../s1-06-caisse/bitset.md), dans le dossier de l'exercice 6, détaille ces
opérations.

## 4. L'exemple en entier

Voici la première carte de `exemple.in` — celle de la section 1 — rangée des trois façons.
**Les régions sont numérotées de 1 à 6 dans l'entrée ; ici elles ont été ramenées à 0 … 5**
en retranchant 1 à la lecture.

| région | voisins | degré | ligne de bits | valeur |
|---|---|---|---|---|
| 0 | 1, 2, 5 | 3 | `100110` | 38 |
| 1 | 0, 2 | 2 | `000101` | 5 |
| 2 | 0, 1, 3, 4 | 4 | `011011` | 27 |
| 3 | 2, 4 | 2 | `010100` | 20 |
| 4 | 2, 3, 5 | 3 | `101100` | 44 |
| 5 | 0, 4 | 2 | `010001` | 17 |

Les lignes de bits se lisent comme dans `bitset.md` : le bit de droite est le numéro 0.
Pour la région 0, `100110` porte des 1 en positions 1, 2 et 5 — ses trois voisines.

Les voisins sont écrits ici **en ordre croissant, pour la lisibilité**. Le tableau que
vous remplirez à la lecture les tiendra dans l'ordre où les frontières arrivent : la
région 2 y aura `1 0 3 4`, et non `0 1 3 4`. Cela n'a aucune importance tant que vous ne
supposez pas le contraire.

Deux contrôles que vous pouvez faire sur votre propre lecture :

- **la somme des degrés vaut `2m`**, ici `3+2+4+2+3+2 = 16 = 2 × 8`. Chaque frontière est
  comptée une fois à chaque bout. Si votre somme vaut `m`, vous avez oublié un des deux
  sens ;
- **la matrice est symétrique** : `adj[i][j]` et `adj[j][i]` sont toujours d'accord.

## 5. Le degré d'une région

Le nombre de régions qu'elle touche. Avec la liste, c'est `degre[i]`, tenu à jour à la
lecture ; avec la ligne de bits, c'est le nombre de 1, qui se recompte à la demande :

```c
int d = __builtin_popcountll(adj[i]);
```

## 6. Numérotées à partir de 1, rangées à partir de 0

L'entrée numérote les régions de `1` à `n`, les tableaux de C commencent à `0`. Les deux
solutions se valent, mais il faut **en choisir une et s'y tenir** :

- retrancher 1 à la lecture, et travailler de `0` à `n-1` — c'est ce qui est fait dans le
  tableau ci-dessus ;
- ou allouer `n+1` cases et laisser l'indice 0 inutilisé.

Mélanger les deux dans un même programme donne des décalages d'une case qui ne se voient
qu'à l'exécution, sur certaines cartes seulement.

## 7. Ce que ce document ne fait pas

Il range une carte en mémoire. Il ne dit pas quoi en faire : un graphe bien rangé ne répond
à aucune question par lui-même, et le rangement ne change pas la difficulté de la question
posée — seulement le coût de chaque coup d'œil.

Autrement dit : c'est un outil, pas une méthode.
