#include "ville.h"

// ######### PUBLIC #########

Ville V_creer(Labyrinthe lab) {
    Ville v;
    v.labyrinthe = lab;
    v.objectifs = LCL_liste(&copierInt, &supprimerInt);

    return v;
}

void V_ajouterObjectif(Ville* v, int objectif) {
    LCL_inserer(&v->objectifs, &objectif, LCL_longueur(v->objectifs));
}


int V_obtenirIemeObjectif(Ville v, int i) {
    return *(int*)LCL_element(v.objectifs, i);
}

int V_obtenirNbObjectifs(Ville v) {
    return LCL_longueur(v.objectifs);
}

Labyrinthe *V_labyrinthe(Ville *v) {
    return &v->labyrinthe;
}

void V_detruire(Ville v) {
    LCL_vider(&v.objectifs);
    L_detruire(V_labyrinthe(&v));
}

void V_afficherVille(Ville v) {
    Labyrinthe* l = V_labyrinthe(&v);

    L_afficherLabyrinthe(*l);

    int nbObjectifs = V_obtenirNbObjectifs(v);
    fprintf(stderr, "Nombre d'objectifs : %d\n", nbObjectifs);
    for (int i = 0; i < nbObjectifs; i++) {
        int obj = V_obtenirIemeObjectif(v, i);
        fprintf(stderr, "  Objectif %d : %d\n", i + 1, obj);
    }
}