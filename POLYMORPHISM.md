# Comprendre le Polymorphisme : ClapTrap* ptr = new ScavTrap("Robot")

## 1. La relation d'héritage

```
        ClapTrap (classe de base)
            ↑
            |  hérite de
            |
        ScavTrap (classe dérivée)
```

Quand ScavTrap hérite de ClapTrap avec `class ScavTrap : public ClapTrap`, cela signifie que **ScavTrap EST UN ClapTrap** (relation "is-a").

## 2. Comment fonctionne la ligne mystérieuse

```cpp
ClapTrap* ptr = new ScavTrap("Robot");
```

### Décomposition étape par étape :

#### Étape 1 : Création de l'objet
```
new ScavTrap("Robot")  →  Crée un objet ScavTrap en mémoire
```

#### Étape 2 : Ce qui se passe en mémoire

```
Adresse : 0x1000
┌─────────────────────┐
│   ClapTrap part     │  ← Partie héritée
│  ┌───────────────┐  │
│  │ _name         │  │
│  │ _hitPoints    │  │
│  │ _energyPoints │  │
│  │ _attackDamage │  │
│  └───────────────┘  │
│                     │
│   ScavTrap part     │  ← Partie spécifique
│  ┌───────────────┐  │
│  │ (données      │  │
│  │ additionnelles│  │
│  │  si présentes)│  │
│  └───────────────┘  │
└─────────────────────┘
```

#### Étape 3 : Le pointeur
```cpp
ClapTrap* ptr  →  pointe vers l'adresse 0x1000
                  mais ne "voit" que la partie ClapTrap
```

## 3. Schéma visuel du polymorphisme

```
   PILE (Stack)                    TAS (Heap)
┌──────────────┐              ┌─────────────────┐
│              │              │                 │
│  ptr         │─────────────>│  Objet ScavTrap │
│  (ClapTrap*) │              │                 │
│              │              │  ┌───────────┐  │
└──────────────┘              │  │ ClapTrap  │  │
                              │  │   part    │  │
                              │  ├───────────┤  │
                              │  │ ScavTrap  │  │
                              │  │   part    │  │
                              │  └───────────┘  │
                              └─────────────────┘
```

## 4. Pourquoi c'est possible ?

### Principe de substitution de Liskov
Un objet d'une classe dérivée peut toujours remplacer un objet de sa classe de base.

```cpp
// Ces deux lignes sont valides :
ClapTrap* ptr1 = new ClapTrap("Base");    // Pointeur vers ClapTrap
ClapTrap* ptr2 = new ScavTrap("Derived"); // Pointeur vers ScavTrap

// Mais l'inverse n'est PAS possible :
ScavTrap* ptr3 = new ClapTrap("Error");   // ❌ ERREUR DE COMPILATION
```

## 5. Exemple pratique avec comportement

```cpp
// Sans fonction virtuelle
class ClapTrap {
public:
    void attack() { std::cout << "ClapTrap attacks!" << std::endl; }
    ~ClapTrap() { std::cout << "ClapTrap destroyed" << std::endl; }
};

class ScavTrap : public ClapTrap {
public:
    void attack() { std::cout << "ScavTrap attacks!" << std::endl; }
    ~ScavTrap() { std::cout << "ScavTrap destroyed" << std::endl; }
};

// Utilisation
ClapTrap* ptr = new ScavTrap();
ptr->attack();     // Affiche "ClapTrap attacks!" (pas ce qu'on veut!)
delete ptr;        // Affiche seulement "ClapTrap destroyed" (PROBLÈME!)
```

## 6. La solution : fonctions virtuelles

```cpp
class ClapTrap {
public:
    virtual void attack() { std::cout << "ClapTrap attacks!" << std::endl; }
    virtual ~ClapTrap() { std::cout << "ClapTrap destroyed" << std::endl; }
};

// Maintenant :
ClapTrap* ptr = new ScavTrap();
ptr->attack();     // Affiche "ScavTrap attacks!" ✓
delete ptr;        // Affiche "ScavTrap destroyed" puis "ClapTrap destroyed" ✓
```

## 7. Table des pointeurs virtuels (vtable)

Quand tu utilises `virtual`, chaque objet contient un pointeur caché vers sa vtable :

```
Objet ScavTrap en mémoire :
┌─────────────────────┐
│ vptr ───────────────┼────▶ ScavTrap vtable
├─────────────────────┤      ┌──────────────┐
│ _name               │      │ &attack()    │ → ScavTrap::attack
│ _hitPoints          │      │ &~destructor │ → ScavTrap::~ScavTrap
│ _energyPoints       │      └──────────────┘
│ _attackDamage       │
└─────────────────────┘
```

## 8. Analogie du monde réel

- **ClapTrap** = "Véhicule" (classe de base)
- **ScavTrap** = "Voiture" (classe dérivée)

```cpp
Vehicule* monTransport = new Voiture("Lambo");
// C'est logique : une voiture EST un véhicule
// Le pointeur "Vehicule" peut pointer vers n'importe quel véhicule
```

## Points clés à retenir

1. **Un pointeur de classe de base peut pointer vers un objet de classe dérivée** (mais pas l'inverse)
2. **Sans `virtual`**, le compilateur utilise le type du pointeur (ClapTrap*) pour décider quelle fonction appeler
3. **Avec `virtual`**, le compilateur utilise le type réel de l'objet (ScavTrap) pour décider
4. **Le destructeur virtuel est CRUCIAL** pour éviter les fuites mémoire et les comportements indéfinis
