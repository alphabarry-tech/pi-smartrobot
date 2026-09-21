# Constantes de base
SRCDIR = src
LIBDIR = lib
BINDIR = bin
TEST_SRCS_DIR = src/tests
TESTDIR = tests
DOCDIR = doc
INCLUDEDIR = include
CC = gcc
DOXYGEN = doxygen
CFLAGS = -Wall -pedantic -g -I$(INCLUDEDIR) -I$(HOME)/.local/include
LDFLAGS = -L$(HOME)/.local/lib -lcollections -lsdd -lwiringPi -lwiringPiDev -lm
TEST_LDFLAGS = -lcunit

# Configuration de Doxygen
DOXYFILE = Doxyfile
PROJECT_NAME = projet intégratif Smart Robot - 2025-2026


# Lister tous les fichiers .c dans le dossier src/tests
TEST_BINS = $(patsubst $(TEST_SRCS_DIR)/%.c,$(TESTDIR)/%,$(wildcard $(TEST_SRCS_DIR)/*.c))

# Constantes pour la reflexion
REFLEXION_SRCS = graphe.c labyrinthe.c sommet.c trouverPlusCourtChemin.c ville.c lireVille.c listeChaineeDEntier.c
REFLEXION_MAIN = $(SRCDIR)/afficherOrdres.c
REFLEXION_LIBNAME = afficherOrdres
REFLEXION_OBJS = $(patsubst %.c,$(SRCDIR)/%.o,$(REFLEXION_SRCS)) # remplace les .c par .o de REFLEXION_SRCS
LIB_REFLEXION = $(LIBDIR)/lib$(REFLEXION_LIBNAME).a
EXECUTABLE_REFLEXION = $(BINDIR)/afficherOrdres
REFLEXION_MAIN_OBJ = $(patsubst %.c,%.o,$(REFLEXION_MAIN)) # remplace le .c par .o de REFLEXION_MAIN

# Constantes pour le robot
ROBOT_SRCS =
ROBOT_MAIN = $(SRCDIR)/robot.c
ROBOT_LIBNAME = robot
ROBOT_OBJS = $(patsubst %.c,$(SRCDIR)/%.o,$(ROBOT_SRCS)) # remplace les .c par .o de ROBOT_SRCS
LIB_ROBOT = $(LIBDIR)/lib$(ROBOT_LIBNAME).a
EXECUTABLE_ROBOT = $(BINDIR)/robot
ROBOT_MAIN_OBJ = $(patsubst %.c,%.o,$(ROBOT_MAIN)) # remplace le .c par .o de ROBOT_MAIN

# Liste des cibles possibles
.PHONY: all prg tests doc clean dirs

# Lance la compilation des programmes, des tests et de la documentation
all: prg tests doc

# Lance la compilation des programmes (cree les dossiers si necessaire et compile les programmes)
prg: dirs $(EXECUTABLE_REFLEXION) $(EXECUTABLE_ROBOT)

# Lance la compilation des tests (cree les dossiers si necessaire et compile les tests)
tests: dirs $(TEST_BINS)

# Cree les dossiers necessaires (si ils n'existent pas)
dirs:
	@mkdir -p $(LIBDIR) $(BINDIR) $(TESTDIR) $(DOCDIR)

# Cree la librairie de la reflexion (si il y en a une à faire)
ifneq ($(REFLEXION_OBJS),)
$(LIB_REFLEXION): $(REFLEXION_OBJS)
	ar rcs $@ $^
endif

# Cree la librairie du robot (si il y en a une à faire)
ifneq ($(ROBOT_OBJS),)
$(LIB_ROBOT): $(ROBOT_OBJS)
	ar rcs $@ $^
endif

# Compilation des fichiers sources en objets
$(SRCDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Cree l'executable de la reflexion
ifneq ($(REFLEXION_OBJS),) # si on a une lib
$(EXECUTABLE_REFLEXION): $(REFLEXION_MAIN_OBJ) $(LIB_REFLEXION)
	$(CC) $(CFLAGS) -o $@ $(REFLEXION_MAIN_OBJ) -L$(LIBDIR) -l$(REFLEXION_LIBNAME) $(LDFLAGS)
else # si on a pas de lib
$(EXECUTABLE_REFLEXION): $(REFLEXION_MAIN_OBJ)
	$(CC) $(CFLAGS) -o $@ $(REFLEXION_MAIN_OBJ) $(LDFLAGS)
endif

# Cree l'executable du robot
ifneq ($(ROBOT_OBJS),) # si on a une lib
$(EXECUTABLE_ROBOT): $(ROBOT_MAIN_OBJ) $(LIB_ROBOT)
	$(CC) $(CFLAGS) -o $@ $(ROBOT_MAIN_OBJ) -L$(LIBDIR) -l$(ROBOT_LIBNAME) $(LDFLAGS)
else # si on a pas de lib
$(EXECUTABLE_ROBOT): $(ROBOT_MAIN_OBJ)
	$(CC) $(CFLAGS) -o $@ $(ROBOT_MAIN_OBJ) $(LDFLAGS)
endif

# Compilation pour les tests
$(TESTDIR)/%: $(TEST_SRCS_DIR)/%.c $(LIB_REFLEXION) dirs
	$(CC) $(CFLAGS) -o $@ $< -L$(LIBDIR) -l$(REFLEXION_LIBNAME) $(TEST_LDFLAGS) $(LDFLAGS)

# Generation de la documentation (verifie que doxygen est installe, cree un Doxyfile par defaut si necessaire, modifie les champs importants et lance doxygen)
doc: dirs
	@command -v $(DOXYGEN) >/dev/null 2>&1 || { echo "$(DOXYGEN) introuvable — installez doxygen."; exit 1; }
	@if [ ! -f $(DOXYFILE) ]; then echo "Génération de $(DOXYFILE) par défaut..."; $(DOXYGEN) -g $(DOXYFILE); fi
	@sed -i -e "s|^INPUT *=.*|INPUT = $(INCLUDEDIR)|" -e "s|^OUTPUT_DIRECTORY *=.*|OUTPUT_DIRECTORY = $(DOCDIR)|" -e "s|^PROJECT_NAME *=.*|PROJECT_NAME = $(PROJECT_NAME)|" $(DOXYFILE) || true
	@$(DOXYGEN) $(DOXYFILE)

# Nettoyage des fichiers générés
clean:
	rm -f $(BINDIR)/*
	rm -f $(TESTDIR)/*
	rm -f $(LIBDIR)/*
	rm -f $(SRCDIR)/*.o
	rm -rf $(DOCDIR)/*



