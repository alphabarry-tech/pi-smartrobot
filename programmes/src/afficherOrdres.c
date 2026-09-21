#include "afficherOrdres.h"

int main(int argc, char* argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <nom_du_fichier>\n", argv[0]);
        return 1;
    }

    Ville ville = creerVilleAPartirDeFichier(argv[1]);

    V_afficherVille(ville);

    listeOrdre(&ville);

    V_detruire(ville);

    return 0;
}
