# PI SmartRobot — un robot qui résout un labyrinthe

Projet intégrateur (PI) de l'INSA Rouen Normandie, année 2025-2026 : un **robot suiveur de ligne** piloté par une **Raspberry Pi**, capable de parcourir un labyrinthe en passant par des objectifs puis de revenir à son point de départ par les chemins les plus courts.

Le code est écrit en **C**. Le projet s'appuie sur l'algorithmique de graphes et sur des **types abstraits de données (TAD)**, ainsi que sur l'électronique embarquée (capteurs, moteurs, bus I2C).

> Projet de groupe réalisé en équipe de 5 étudiants. Résultat : **3ᵉ au classement du temps de résolution** du labyrinthe.

## Fonctionnement

Deux programmes, enchaînés par `start.sh` :

1. **`afficherOrdres`** (réflexion, sur PC ou Raspberry Pi) lit la description de la « ville » (`ville.txt`), calcule le parcours et écrit la suite d'**ordres** `AV` (avancer), `TD` (tourner à droite), `TG` (tourner à gauche) ; le point `.` marque la fin.
2. **`robot`** (sur la Raspberry Pi) lit ces ordres, suit la ligne avec ses capteurs, repère les intersections, exécute chaque ordre et s'arrête à la fin.

```bash
bin/afficherOrdres ville.txt > direction.txt
sudo bin/robot < direction.txt
```

### Exemple

`ville.txt` décrit un labyrinthe de 5 × 5 cases : la taille, la position et la direction de départ (`1E` : case 1, cap est), les liaisons `a-b` entre cases, puis les cases objectifs (`4 13 16`).

Pour ce fichier, le robot passe par les objectifs 4, 13 et 16 puis revient au départ :

```
1-2-3-4-5-10-15-14-9-8-13-18-23-22-21-16-11-6-7-2-1
AV AV AV TD AV TD AV TD AV TG AV TG AV TD AV TD AV TD AV TG AV TG AV .
```

## Algorithme

- Le labyrinthe est un **graphe** : chaque case est un sommet, chaque passage une arête. Les TAD `Sommet`, `Graphe`, `Labyrinthe` et `Ville` (labyrinthe + objectifs) séparent les responsabilités.
- Le chemin le plus court est cherché par un **parcours en largeur (BFS)**, adapté au robot :
  - **pas de demi-tour** pendant le calcul, car trop risqué mécaniquement ;
  - on va toujours à **l'objectif le plus proche** plutôt que de chercher le parcours global optimal, pour garder un calcul rapide ;
  - le coût d'un chemin est sa **distance + son nombre de virages**, car le robot ralentit dans les intersections : un chemin de 5 cases sans virage est préféré à un chemin de 3 cases avec 3 virages.
- Le chemin est ensuite converti en ordres `AV`/`TD`/`TG` selon les changements de direction.
- Pistes d'amélioration : essayer Dijkstra ou A*, optimiser le placement des capteurs pour accélérer le robot, utiliser le multithreading.

## Matériel

Schéma de câblage : [`docs/schema-electrique.png`](docs/schema-electrique.png) (réalisé avec Fritzing).

| Élément | Rôle |
|---|---|
| Raspberry Pi 4 Model B | Calcul et pilotage |
| 4 capteurs infrarouges (modules FC-51) | Suivi de ligne et détection des intersections |
| Capteur de couleur RGB TCS34725 (I2C `0x29`) | Détection des pastilles |
| Buzzer | Signal sonore |
| Pont en H L293D + 2 moteurs DC | Déplacement (rotation d'une seule roue pour tourner) |
| Écran LCD I2C (`0x27`) | Prévu, non installé faute d'adaptateur |

Alimentation : une batterie externe de 10 000 mAh pour la Raspberry Pi et deux accumulateurs Li-ion 3,7 V / 3 400 mAh en série (7,4 V) pour les moteurs.

## Compilation

Prérequis :
- `gcc`, `make`, [`wiringPi`](https://github.com/WiringPi/WiringPi) (sur la Raspberry Pi), `CUnit` (tests), `doxygen` (documentation) ;
- les bibliothèques pédagogiques **`libcollections`** et **`libsdd`** fournies par l'INSA (non incluses dans ce dépôt), attendues dans `~/.local/lib` et `~/.local/include`.

```bash
cd programmes
make prg     # afficherOrdres et robot
make tests   # tests unitaires (CUnit)
make doc     # documentation Doxygen
make clean
```

`robot` dépend de `wiringPi` et ne compile donc que sur Raspberry Pi. Pour tester seulement le calcul des ordres sur un PC : `make bin/afficherOrdres LDFLAGS="-L$HOME/.local/lib -lcollections -lsdd -lm"`.

## Structure

```
programmes/
├── src/          afficherOrdres.c, robot.c, graphe.c, labyrinthe.c, ville.c, sommet.c,
│                 trouverPlusCourtChemin.c, lireVille.c, listeChaineeDEntier.c
├── src/tests/    tests unitaires
├── include/      fichiers d'en-tête
├── ville.txt     exemple de labyrinthe
└── start.sh      calcul des ordres puis exécution par le robot
docs/schema-electrique.png
```

## Ma contribution

- conception et implémentation des TAD **Graphe**, **Labyrinthe** et **Ville** ;
- **algorithme du plus court chemin** : versions successives (première version, suppression des demi-tours, nouvelle distance tenant compte des virages) et son pseudo-code ;
- **tests unitaires** du plus court chemin ;
- documentation Doxygen, mesure du temps d'exécution dans `start.sh`, rédaction de la partie algorithmique du rapport.

## Équipe

Projet réalisé à cinq à l'INSA Rouen Normandie. Le rapport du projet n'est pas publié ici.
