#include "labyrinthe.h"

// ######### PUBLIC #########

Labyrinthe L_creer(int p, Direction d, int n) {
    Labyrinthe l;
    l.positionDepart = p;
    l.directionDepart = d;
    l.taille = n;

    l.connexions = G_creer(n * n);

    return l;
}

void L_ajouterPassage(Labyrinthe* l, int a, int b) {
    G_fixerPassage(&l->connexions, a, b);
}

Graphe L_obtenirConnexions(Labyrinthe l) {
    return l.connexions;
}

int L_obtenirTaille(Labyrinthe l) {
    return l.taille;
}

int L_obtenirPositionDepart(Labyrinthe l) {
    return l.positionDepart;
}

Direction L_obtenirDirectionDepart(Labyrinthe l) {
    return l.directionDepart;
}

void L_afficherLabyrinthe(Labyrinthe l) {
    fprintf(stderr, "Taille du labyrinthe : %d\n", L_obtenirTaille(l));
    fprintf(stderr, "Position de depart   : %d\n", L_obtenirPositionDepart(l));
    fprintf(stderr, "Direction initiale   : %c\n", "NSEO"[L_obtenirDirectionDepart(l)]);

    Graphe g = L_obtenirConnexions(l);

    int nb = G_nbSommets(g);

    fprintf(stderr, "Nombre de sommets : %d\n\n", nb);

    for (int i = 1; i < nb + 1; i++) {
        Sommet s = G_obtenirSommet(g, i);

        int num = S_obtenirNumSommet(s);
        int nv = S_nombreVoisins(s);

        fprintf(stderr, "Sommet %d : ", num);

        if (nv == 0) {
            fprintf(stderr, "aucun voisin");
        } else {
            fprintf(stderr, "voisins = ");
            for (int j = 0; j < nv; j++) {
                fprintf(stderr, "%d ", S_obtenirIemeVoisin(s, j));
            }
        }
        fprintf(stderr, "\n");
    }
}

void L_detruire(Labyrinthe* l) {
    if (l != NULL) {
        G_detruire(&l->connexions);
        l->positionDepart = 0;
        l->directionDepart = N;
        l->taille = 0;
    }
}
