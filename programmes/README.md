# Programmes du projet SmartRobot

Ce dossier contient les programmes développés pour le projet SmartRobot.  

## Structure des dossiers

- `src/` : Contient le code source des programmes.
- `include/` : Contient les fichiers d'en-tête.
- `tests/` : Contient les tests unitaires.
- `doc/` : Contient la documentation générée.

robot.c : Programme principal pour la gestion du robot.
afficherOrdres.c : Programme pour afficher les ordres à donnés au robot.
tout les autres programme sont des sous programmes pour afficherOrdres.c.
## Compilation

Utilisez `make prg` à la racine du projet pour compiler l'ensemble des programmes.

```bash
make prg
```

Utilisez `make tests` pour compiler les tests.

```bash
make tests
```

Utilisez `make doc` pour compiler la documentation.

```bash
make doc
```

Utilisez `make all` pour faire tout.

```bash
make all
```

Utilisez `make clean` pour nettoyer les fichiers compilés.

```bash
make clean
```

## Exécution

Lancez le programme principal (pour ville.txt) avec :

```bash
./start.sh
```
