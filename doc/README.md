# Arcade - README

Bienvenue dans le projet **Arcade**, dont l’objectif est de recréer une borne d’arcade. Le programme principal ("Core”) peut charger dynamiquement des jeux et des bibliothèques graphiques, permettant ainsi de basculer d’une librairie graphique à une autre (ou d’un jeu à un autre) durant l’exécution.

---

## Ce README décrit :

[1. La structure générale du projet](#1-structure-générale)

[2. Le fonctionnement global (logique de chargement, exécution, interactions)](#2-fonctionnement-global)

[3. Comment créer un nouveau jeu](#3-créer-un-nouveau-jeu)

[4. Comment créer une nouvelle bibliothèque graphique](#4-créer-une-nouvelle-bibliothèque-graphique)

[5. Compilation et exécution](#5-compilation-et-exécution)

[6. Support](#6-support)

---

## 1. Structure générale

Voici les éléments clés :

### Core
Cycle principal de l’application (boucle de jeu, chargement/déchargement des bibliothèques).

Interagit avec les bibliothèques graphiques et les jeux.

### ICore (interface)
Spécifie les fonctions du core :

- `load` : charge un .so (librairie graphique ou jeu)
- `run` : boucle principale (appelle les différentes fonctions des librairies graphiques et des jeux)


### IGame (interface)
Spécifie les fonctions de base que doit implémenter un jeu :

- `update` : met à jour la logique.
- `handleEvent` : traite les événements.

### IGraphic (interface)
Spécifie les fonctions que doit implémenter une bibliothèque graphique :

- `display(data_t)`: affiche les différents éléments.
- `event_t getEvent()` : récupérer les événements.

### dlManager
Classe utilitaire pour charger dynamiquement les bibliothèques (`.so`), et instancier les classes via une interface simple.

### Exemples :
- **Jeux** : Centipede, Snake, Minesweeper...
- **Librairies graphiques** : SFML, SDL2, NCurses...

---

## 2. Fonctionnement global

### Lancement
L'utilisateur lance le programme (`arcade`) avec en paramètre la bibliothèque graphique à charger par défaut.

### Chargement d'une bibliothèque graphique
- Le Core utilise `dlManager`.
- Exemple : `arcade_sdl.so`

### Chargement d’un jeu
- Le Core utilise `dlManager`.
- Exemple : `arcade_nibbler.so`

### Boucle principale
1. Récupération des événements via `getEvent()` -> `IGraphic`
2. Transmission des évènements à `handleEvent()` -> `IGame`
3. Mise à jour des éléments avec `update()` -> `IGame`
4. Affichage avec `display()` -> `IGraphic`

### Changement de jeu ou bibliothèque
Possibilité de switcher dynamiquement sans quitter le programme:
- *échap* en retournant au menu via la touche
- *a* pour changer de librairie graphique durant le jeu
- *e* pour changer de jeu durant un jeu
- *r* pour recommencer une partie sur le même jeu

### Fermeture
Libération des ressources (fenêtre, librairies...).

---

## 3. Créer un nouveau jeu

### Étapes :

1. Créez une classe (ex: `myGameLib`) qui descend de `IGame`.
2. Implémentez les méthodes :

```cpp
#include "IGame.hpp"

class myGameLib : public IGame {
  public:
    myGameLib() {}
    ~myGameLib() override {}

    data_t update() override {}
    void handleEvent(event_t) override {}
};
```

### La fonction de création :

```cpp
extern "C" IGame *makeGame() {
    return new myGameLib();
}
```

## 4. Créer une nouvelle bibliothèque graphique

### Étapes :

1. Créez une classe (ex: `MyGraphicLib`) qui descend de `IGraphicalLib`.
2. Implémentez les méthodes nécessaires :

```cpp
#include "IGraphic.hpp"

class MyGraphicLib : public IGraphic {
  public:
    MyGraphicLib() {}
    ~MyGraphicLib() override {}

    event_t getEvent() override {}
    void display(data_t) override {}
};
```

### La fonction de création :

```cpp
extern "C" IGraphic *makeGraphic() {
    return new MyGraphicLib();
}
```

## 5. Compilation et exécution

### Compilation:

Construisez votre fichier CMake pour chaque jeu/librairie graphique implémentée (il faut placez le `.so` dans le dossier */lib*) et reliez-le dans le CMakeLists.txt à la root.

Puis:

```
sh compile -re
```

### Exécution :

```
./arcade arcade_graphique.so
```

## 6. Support

- Consultez la **documentation dans le code**.

- Contactez les participants de ce répertoire: pierre.pruvost@epitech.eu, jules.delteil@epitech.eu, baptiste.dunes@epitech.eu

- Vous pouvez contacter aussi les autres personnes qui ont contribué à l'architecture : jason.zohou@epitech.eu, mikal.zheng@epitech.eu, paul.berlioz@epitech.eu, luigi.gomes@epitech.eu, celian.raguin@epitech.eu, kerwan.clavier@epitech.eu, swan.grandin@epitech.eu, benoit.thomas@epitech.eu, mariia.semenchenko@epitech.eu 


## Annexes:

- Répertoire Github avec les Interfaces et Structures nécessaires : https://github.com/JulesDELTEIL/ArcadeMultiGroup

- Répertoire Github contenant quelques librairies créées via l'architecture présente dans le répertoire ci-dessus : https://github.com/JulesDELTEIL/ArcadeMultiGroup

- Documentation (format notion) : https://www.notion.so/Documentation-Arcade-1cb3873e4fad80c68b52d587d9cc5df9

- UML Diagramme (contient la logique de l'architecture) : https://www.figma.com/board/ZFgV0zjDJrcWFSmiYQkggJ/UML-Arcade-Dream-Team?node-id=0-1&p=f&t=iePrRdGghth1AQBv-0
