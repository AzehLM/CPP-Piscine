# Héritage

## Ressources

- [Programming Idiom](https://en.wikipedia.org/wiki/Programming_idiom)
- [Semantics (Computer Science)](https://en.wikipedia.org/wiki/Semantics_(computer_science))

## Sémantique

La sémantique informatique est l'étude des significations des programmes informatiques vus en tant qu'objets mathématiques.

## Idiomes de Programmation

Un idiome de programmation est une implémentation d'un concept dans un langage de programmation qui ne fournit pas nativement une construction pour ce concept.

- Un idiome représente une action sur un concept de programmation qui suit un pattern.
- Connaître les idiomes d'un langage est un aspect important de sa maîtrise.
- Exemple : boucle infinie.

### Idiomatique vs Idiosyncrasique

- **Idiosyncrasie** : C'est l'inverse de l'idiomatique ([FR](https://fr.wikipedia.org/wiki/Idiosyncrasie), [EN](https://en.wikipedia.org/wiki/Idiosyncrasy))
  - Exemple d'idiosyncrasie : la façon de gérer l'allocation dynamique en C serait d'utiliser les fonctions de la librairie standard de C (malloc et free)
  - Exemple d'idiomatique : fait référence à la gestion manuelle de la mémoire comme un rôle sémantique récurrent, réalisable avec malloc en C, new en C++.

Dans les deux cas, la sémantique du code est compréhensible pour des développeurs familiers avec le C ou le C++. La logique idiomatique est plus généralement utilisée, sauf dans des cas spécifiques d'utilisation des API, où l'idiosyncrasie est fréquemment utilisée.

## Rule of Three

La [Rule of Three](https://en.wikipedia.org/wiki/Rule_of_three_(C%2B%2B_programming)) part du principe que si une classe possède l'un de ces trois éléments, alors elle devrait posséder les trois :

1. **Destructeur**
2. **Constructeur par copie**
3. **Opérateur d'assignement par copie**

### Fonctions Membres Spéciales

Ces 3 fonctions sont des **fonctions membres spéciales** qui, si elles ne sont pas définies par un développeur, seront implicitement implémentées par le compilateur avec les propriétés sémantiques par défaut suivantes :

- **Destructeur** : Appelle le destructeur de tous les membres de type "class"
- **Constructeur par copie** : Construit tous les membres de l'objet à partir du membre correspondant à l'argument du constructeur de copie
- **Opérateur d'assignement par copie** : Assigne tous les membres correspondants

## Exception Safety

La sécurité des exceptions est un concept important en programmation C++.

### Ressources complémentaires

- [Exception Safety (Wikipedia)](https://en.wikipedia.org/wiki/Exception_safety)
- [Guru of the Week #59](http://gotw.ca/gotw/059.htm)



### Virtual Keyword:

Deux choses importante sur le mot cle `virtual`:
- L'implementation de fonctions virtuelles est completement dependante du **compilateur**
- Le standard C++ ne definit pas son implementation, il decrit son comportement


#### Aparté (Behavioral Functions)

Une behavioral function est une fonction qui **definie le comportement specifique d'un objet**. C'est le terme generique qui designes les fonctions membres qui vont varier selon le type de l'objet.

Exemple avec differents types de connexion (WIFI, Ethernet, Bluetooth...)
- Chaque type aura sa propre facon de s'authentifier et de ce connecter
```C++
wifi::authenticate()
wifi::connect()

ethernet::authenticate()
ethernet::connect()

bluetooth::authenticate()
bluetooth::connect()
```

- **Le comportement change en fonction du type reel de l'objet**
- Le mot cle `virtual` **est l'outil** permettant de **creer des fonctions comportementales**.

#### A quoi servent les fonctions `virtual`

- **Polymorphisme a l'execution**: Le **système détermine automatiquement**, au moment de l'exécution, quelle implémentation spécifique d'une méthode doit être exécutée. Cette décision se base sur la nature réelle de l'objet manipulé plutôt que sur la façon dont il est référencé dans le code
- **Réutilisabilité**: Il devient possible d'écrire des algorithmes et des processus qui opèrent sur des concepts abstraits plutôt que sur des implémentations concrètes. Le code peut manipuler des entités à travers leur interface commune sans avoir besoin de connaître leur nature spécifique.
- **Élimination de la logique conditionnelle**: Au lieu de disperser des structures de contrôle conditionnelles à travers le code pour gérer différents cas (`if`, `elseif`, `else`, etc...), le mécanisme de dispatch virtuel **centralise** cette **logique de sélection**. La complexité de choisir le bon comportement est **déléguée au système d'exécution** plutôt que d'être explicitement codée. Cela réduit la quantité de code nécessaire et **élimine les répétitions structurelles**.


Plus loin:
- [All about virtual keyword in C++](https://dev.to/visheshpatel/part-1-all-about-virtual-keyword-in-c-how-does-virtual-function-works-internally-2ebk)
- [you should not call the virtual function in constructor (from above link)](https://stackoverflow.com/questions/962132/why-is-a-call-to-a-virtual-member-function-in-the-constructor-a-non-virtual-call)
