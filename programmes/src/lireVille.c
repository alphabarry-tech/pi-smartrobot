#include "lireVille.h"

// ######### PUBLIC #########

Ville creerVilleAPartirDeFichier(const char* nomFichier) {
    Ville ville;
    int taille, depart;
    Direction direction;
    char ligne[256];

    FILE* fichier = fopen(nomFichier, "r");
    if (!fichier) {
        perror("Erreur lors de l'ouverture du fichier");
        ville = V_creer(L_creer(0, N, 0));
        return ville;  // Retourne une ville vide en cas d'erreur
    }
    if (fgets(ligne, sizeof(ligne), fichier)) {
        taille = chaineEnEntier(ligne);
    }

    if (fgets(ligne, sizeof(ligne), fichier)) {
        lirePositionInitial(ligne, &depart, &direction);
    }

    ville = V_creer(L_creer(depart, direction, taille));

    while (fgets(ligne, sizeof(ligne), fichier) && contientCaractere(ligne, '-')) {
        lireConnexion(&ville, ligne);
    }

    bool estNonFini = true;
    while (estNonFini && !contientCaractere(ligne, '.')) {
        V_ajouterObjectif(&ville, chaineEnEntier(ligne));
        estNonFini = fgets(ligne, sizeof(ligne), fichier);
    }

    fclose(fichier);

    return ville;
}

// ######### PRIVATE (ONLY USE FOR TEST) #########

int tailleChaine(const char* str) {
    return strlen(str);
}

int positionCharDansChaine(const char* str, char caractere) {
    const char* ptr = strchr(str, caractere);
    if (ptr) {
        return ptr - str;
    }
    return -1;  // Caractère non trouvé
}

bool contientCaractere(const char* str, char caractere) {
    return positionCharDansChaine(str, caractere) != -1;
}

int chaineEnEntier(const char* str) {
    return atoi(str);
}

Direction charEnDirection(char c) {
    switch (c) {
        case 'N':
            return N;
        case 'S':
            return S;
        case 'E':
            return E;
        case 'O':
            return O;
        default:
            return N;
    }
}

void copierUneSousChaine(const char* source, char* destination, int debut, int fin) {
    int j = 0;
    for (int i = debut; i < fin && source[i] != '\0'; i++) {
        destination[j] = source[i];
        j++;
    }
    destination[j] = '\0';
}

void lirePositionInitial(const char* ligne, int* position, Direction* direction) {
    if (tailleChaine(ligne) >= 2) {
        char positionStr[16];
        copierUneSousChaine(ligne, positionStr, 0, tailleChaine(ligne) - 1);
        *position = chaineEnEntier(positionStr);
        *direction = charEnDirection(ligne[tailleChaine(ligne) - 2]);
    } else {
        fprintf(stderr, "Erreur: ligne de position initiale invalide.\n");
    }
}

void lireConnexion(Ville* ville, const char* connexion) {
    Labyrinthe* leLabyrinthe = V_labyrinthe(ville);
    int position = positionCharDansChaine(connexion, '-');
    if (position != -1) {
        char sommetAGaucheStr[16];  // statique car taille max petite
        char sommetADroiteStr[16];
        copierUneSousChaine(connexion, sommetAGaucheStr, 0, position);
        copierUneSousChaine(connexion, sommetADroiteStr, position + 1, tailleChaine(connexion));
        int sommet1 = chaineEnEntier(sommetAGaucheStr);
        int sommet2 = chaineEnEntier(sommetADroiteStr);
        L_ajouterPassage(leLabyrinthe, sommet1, sommet2);
    } else {
        fprintf(stderr, "Erreur: ligne de passage invalide.\n");
    }
}
