
#include "sommet.h"

// ######### PUBLIC #########

Sommet S_creer(int n) {
    Sommet s;
    s.num = n;
    s.nbVoisins = 0;

    for (int i = 0; i < MAX_VOISINS; i++) {
        s.voisins[i] = -1;  // valeur vide
    }

    return s;
}

int S_obtenirNumSommet(Sommet s) {
    return s.num;
}

int S_nombreVoisins(Sommet s) {
    return s.nbVoisins;
}

bool S_estVoisin(Sommet s, int v) {
    for (int i = 0; i < s.nbVoisins; i++) {
        if (s.voisins[i] == v)
            return true;
    }
    return false;
}

void S_ajouterVoisin(Sommet* s, int v) {
    if (S_estVoisin(*s, v)) return;

    if (s->nbVoisins < MAX_VOISINS) {
        s->voisins[s->nbVoisins] = v;
        s->nbVoisins++;
    }
}

int S_obtenirIemeVoisin(Sommet s, int i) {
    if (i < 0 || i >= s.nbVoisins)
        return -1;

    return s.voisins[i];
}
