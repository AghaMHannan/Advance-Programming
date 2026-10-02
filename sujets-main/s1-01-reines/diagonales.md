# Aide-mémoire — lignes, colonnes et diagonales d'un échiquier

Ce document explique comment **désigner** les quatre alignements d'un échiquier `n × n`, et
comment les numéroter pour s'en servir comme indices de tableau. C'est de la géométrie de
coordonnées : il ne dit rien de la façon de chercher quoi que ce soit.

## 1. Repérer une case

Une case est un couple `(r, c)` — sa rangée et sa colonne, comptées à partir de 0 :

```
        c=0  c=1  c=2  c=3  c=4
 r=0     .    .    .    .    .
 r=1     .    .    .    .    .
 r=2     .    .    .    .    .
 r=3     .    .    .    .    .
 r=4     .    .    .    .    .
```

Deux cases sont sur la **même rangée** si `r` est le même, sur la **même colonne** si `c`
est le même. Jusqu'ici rien de surprenant.

## 2. Les deux familles de diagonales

Il y a deux sortes de diagonales, et elles se comportent différemment.

Une diagonale **`\`** descend vers la droite : en avançant d'une case, `r` augmente de 1 et
`c` augmente de 1. **Leur différence `r - c` ne change donc pas.**

Une diagonale **`/`** monte vers la droite : `r` diminue de 1 pendant que `c` augmente de 1.
**Leur somme `r + c` ne change pas.**

D'où le test complet, en une expression :

```c
/* les cases (r1,c1) et (r2,c2) sont-elles alignées ? */
r1 == r2  ||  c1 == c2  ||  r1 - c1 == r2 - c2  ||  r1 + c1 == r2 + c2
/*  rangée      colonne       diagonale  \          diagonale  /        */
```

## 3. Numéroter les diagonales

Pour se servir d'une diagonale comme **indice de tableau**, il faut que son numéro soit un
entier entre 0 et quelque chose.

Pour les `/`, c'est immédiat : `r + c` vaut 0 dans le coin en haut à gauche et `2n - 2`
dans le coin en bas à droite. La numérotation est prête à l'emploi.

Pour les `\`, `r - c` vaut `n - 1` dans le coin en haut à droite et `-(n - 1)` dans le coin
en bas à gauche : **la moitié des valeurs sont négatives.** On les décale de `n - 1` :

```c
int diagonale_montante   = r + c;           /* « / » :  0 … 2n-2 */
int diagonale_descendante = r - c + n - 1;  /* « \ » :  0 … 2n-2 */
```

## 4. L'exemple en entier

Voici les deux numérotations sur un échiquier **5 × 5**. À gauche `r + c`, à droite
`r - c + 4`. Les cases qui portent le même nombre sont sur la même diagonale :

```
     « / »  :  r + c                 « \ »  :  r - c + n - 1

      0  1  2  3  4                    4  3  2  1  0
      1  2  3  4  5                    5  4  3  2  1
      2  3  4  5  6                    6  5  4  3  2
      3  4  5  6  7                    7  6  5  4  3
      4  5  6  7  8                    8  7  6  5  4
```

Lisez la grille de gauche en biais, du coin bas-gauche vers le coin haut-droit : les `4` y
forment bien une diagonale `/`. Sur celle de droite, les `4` descendent du coin haut-gauche
vers le coin bas-droite — une diagonale `\`.

Vérifions sur deux cases. `(1, 3)` et `(3, 1)` : leurs sommes valent `4` et `4` — même
diagonale `/`. Leurs différences décalées valent `2` et `6` — diagonales `\` différentes.

## 5. Combien y en a-t-il ?

Les deux numérotations vont de 0 à `2n - 2`, soit **`2n - 1` diagonales dans chaque
famille**. Pour un échiquier 5 × 5, 9 de chaque. Pour un 15 × 15, **29 de chaque**.

Ce n'est pas `n` : les diagonales des coins ne contiennent qu'une seule case, et il y en a
presque deux fois plus que de rangées. Un tableau dimensionné à `n` déborde.

> **Le piège.** `r - c` est négatif dès que `c > r`, c'est-à-dire sur toute la moitié
> supérieure droite de l'échiquier. En C, indexer un tableau avec un nombre négatif ne
> provoque aucune erreur : le programme lit ou écrit à côté, et se met à donner des
> résultats faux ailleurs, longtemps après. N'oubliez pas le `+ n - 1`.

## 6. Ce que ce document ne fait pas

Il donne un système de coordonnées, rien de plus. Savoir désigner une diagonale en temps
constant ne dit pas **quelles cases essayer**, ni **dans quel ordre**, ni **quand s'arrêter**
— et c'est là que se joue la différence entre un programme qui répond et un programme qui
tourne encore demain.

Autrement dit : c'est un outil, pas une méthode.
