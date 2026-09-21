#include "graphe.h"

// ######### PUBLIC #########
Graphe G_creer(int n) {
    Graphe g;
    g.sommets = (Sommet*)malloc(n * sizeof(Sommet));
    if (g.sommets == NULL) {
        printf("erreur d'allocation");
        exit(0);
    }
    g.nbSommets = 0;
    return g;
}

int G_indiceSommet(Graphe g, int n) {
    for (int i = 0; i < g.nbSommets; i++) {
        if (g.sommets[i].num == n) {
            return i;
        }
    }
    return -1;
}

int G_nbSommets(Graphe g) {
    return g.nbSommets;
}

bool G_estSommet(Graphe g, int n) {
    return G_indiceSommet(g, n) != -1;
}

Sommet G_obtenirSommet(Graphe g, int n) {
    int i = G_indiceSommet(g, n);
    if (i == -1) {  // si le sommet n'existe pas renvoie un sommet vide (car il est juste vide (pas de ligne))
        return S_creer(-1);
    }
    return g.sommets[i];
}

void G_ajouterSommet(Graphe* g, Sommet s) {
    // vérifier si le sommet existe déjà et sinon on l'ajoute
    if (!G_estSommet(*g, s.num)) {
        g->sommets[g->nbSommets] = s;
        g->nbSommets++;
    }
}

void G_fixerPassage(Graphe* g, int a, int b) {
    int ia = G_indiceSommet(*g, a);
    int ib = G_indiceSommet(*g, b);

    if (ia == -1) {
        Sommet sa0 = S_creer(a);
        G_ajouterSommet(g, sa0);
        ia = G_indiceSommet(*g, a);
    }
    if (ib == -1) {
        Sommet sb0 = S_creer(b);
        G_ajouterSommet(g, sb0);
        ib = G_indiceSommet(*g, b);
    }

    // Récupérer les sommets du graphe (copies), les modifier, puis les réécrire
    Sommet sa = g->sommets[ia];
    Sommet sb = g->sommets[ib];

    if (!S_estVoisin(sa, b) && S_nombreVoisins(sa) < MAX_VOISINS) {
        S_ajouterVoisin(&sa, b);
    }
    if (!S_estVoisin(sb, a) && S_nombreVoisins(sb) < MAX_VOISINS) {
        S_ajouterVoisin(&sb, a);
    }

    g->sommets[ia] = sa;
    g->sommets[ib] = sb;
}

void G_detruire(Graphe* g) {
    if (g != NULL) {
        if (g->sommets != NULL) {
            free(g->sommets);
            g->sommets = NULL;
        }
        g->nbSommets = 0;
    }
}
