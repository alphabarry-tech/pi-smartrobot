
#include "trouverPlusCourtChemin.h"

// ######### PUBLIC #########

void listeOrdre(Ville* ville) {
    LCL_Liste chemins;
    bool possible;

    plusCourtCheminAvecBFS(*ville, &possible, &chemins);

    Labyrinthe* lab = V_labyrinthe(ville);
    Direction directionDepart = L_obtenirDirectionDepart(*lab);
    int taille = L_obtenirTaille(*lab);

    if (possible) {
        int l = LCL_longueur(chemins);

        Graphe g = L_obtenirConnexions(*lab);

        if (S_nombreVoisins(G_obtenirSommet(g, *((int*)LCL_element(chemins, 0)))) <=
            2) {
            // On demare le robot si il est en ligne droite
            // le reste du temps il demarera après un premier virage
            afficherOrdreAvancer();
        }

        for (int i = 0; i < l - 1; i++) {
            int* initial = (int*)LCL_element(chemins, i);
            int* suivant = (int*)LCL_element(chemins, i + 1);

            if (*initial != *suivant) {
                fprintf(stderr, "%d-%d\n", *initial, *suivant);
                directionDepart = afficherOrdre(G_obtenirSommet(g, *initial),
                                                G_obtenirSommet(g, *suivant),
                                                directionDepart, taille);
            }
        }

    } else {
        fprintf(stderr, "problème avec le court chemin");
    }

    printf(".");
}

// ######### PRIVATE (ONLY USE FOR TEST) #########

int plusCourtCheminAvecBFS(Ville v, bool* possible, LCL_Liste* chemins) {
    Labyrinthe* lab = V_labyrinthe(&v);
    int positionInitiale = L_obtenirPositionDepart(*lab);
    int taille = L_obtenirTaille(*lab);
    int nbSommet = taille * taille;
    int cheminEntreDeuxPoints[nbSommet];
    *possible = true;
    Direction directionInitiale = L_obtenirDirectionDepart(*lab);
    int indicePassage = 0;
    int distance = 0;

    remettreTableauAZero(cheminEntreDeuxPoints, nbSommet);

    V_ajouterObjectif(&v, positionInitiale);  // on ajoute le depart comme objectif

    int nb_objectifs = V_obtenirNbObjectifs(v);

    *chemins = LCL_liste(copierInt, supprimerInt);

    LCL_inserer(chemins, &positionInitiale, 0);

    bool estAtteint[nb_objectifs];  // On marque tous les objectifs comme non
                                    // atteint (false) au debut
    for (int i = 0; i < nb_objectifs; i++) {
        estAtteint[i] = false;
    }

    for (int k = 0; k < nb_objectifs; k++) {
        int but;
        int indiceBut = sommetLePlusProche(positionInitiale, v, taille, estAtteint);  // la postion du plus proche dans la liste des objectifs

        if (indiceBut == -1)  // pour le dernier objectif qui est le point de positionInitiale
            indiceBut = k;

        but = V_obtenirIemeObjectif(v, indiceBut);

        Direction directionFinale;
        distance += courtCheminBFS(*lab, positionInitiale, taille, but, cheminEntreDeuxPoints, possible, directionInitiale, &directionFinale);
        directionInitiale = directionFinale;

        if (*possible) {
            positionInitiale = but;
            int i = 0;

            while (i < nbSommet && cheminEntreDeuxPoints[i] != 0) {
                LCL_inserer(chemins, &cheminEntreDeuxPoints[i], indicePassage++);
                i++;
            }
        
            remettreTableauAZero(cheminEntreDeuxPoints, i);
        } else {
            fprintf(stderr, "Problème de calcul du chemin entre %d et %d", positionInitiale, but);
        }
    }

    return distance;
}

void initialiserBFS(int taille, bool visite[], int predecesseurs[], LCF_ListeChaineeFile* file) {
    int nbSommets = taille * taille;

    for (int i = 0; i < nbSommets; i++) {
        visite[i] = false;
        predecesseurs[i] = 0;
    }

    *file = LCF_file(copierInt, supprimerInt);
}

int courtCheminBFS(Labyrinthe lab, int positionInital, int taille, int positionFinal, int chemin[], bool* possible, Direction directionInitiale, Direction* directionFinale) {
    int predParent = trouverPredecesseur(positionInital, directionInitiale, taille);

    int nbSommets = taille * taille;
    int distance = 0;
    int predecesseurs[nbSommets + 1];
    bool visite[nbSommets + 1];

    LCF_ListeChaineeFile file;

    Graphe grapheDeConnexions = L_obtenirConnexions(lab);

    initialiserBFS(taille, visite, predecesseurs, &file);

    visite[positionInital] = true;

    predecesseurs[positionInital] = predParent;

    LCF_enfiler(&file, &positionInital);

    bool trouve = false;

    while (!LCF_estVide(file) && !trouve) {
        int* courant = (int*)LCF_defiler(&file);

        if (courant != NULL) {
            if (*courant == positionFinal) {
                trouve = true;
            } else {
                int parent = predecesseurs[*courant];
                explorerVoisins(&grapheDeConnexions, *courant, visite, predecesseurs,
                                &file, parent);
            }

            free(courant);
        } else {
            fprintf(stderr, "Erreur d'allocaton de l'entier");
        }
    }

    int nbrTournants = 0;

    if (!trouve) {
        *possible = false;
    } else {
        *possible = true;

        distance = reconstituerChemin(predecesseurs, chemin, positionInital, positionFinal, directionInitiale, taille, &nbrTournants);
    }

    *directionFinale = trouverDirectionEntreSommets(positionFinal, chemin[distance - 1], taille);

    return distance + nbrTournants;
}

void explorerVoisins(Graphe* grapheDeConnexions, int num, bool visite[], int predecesseurs[], LCF_ListeChaineeFile* file, int parent) {
    Sommet sommetCourant = G_obtenirSommet(*grapheDeConnexions, num);
    for (int i = 0; i < S_nombreVoisins(sommetCourant); i++) {
        int voisin = S_obtenirIemeVoisin(sommetCourant, i);
        if (!visite[voisin] && (parent <= 0 || voisin != parent)) {
            visite[voisin] = true;
            predecesseurs[voisin] = num;
            LCF_enfiler(file, &voisin);
        }
    }
}

int reconstituerChemin(int predecesseurs[], int chemin[], int positionInitiale, int positionFinale, Direction directionInitiale, int taille, int* nbrTournants) {
    int indiceChemin = 0;
    int numSommetActuel = positionFinale;

    while (numSommetActuel != 0 && numSommetActuel != positionInitiale) {
        numSommetActuel = predecesseurs[numSommetActuel];
        chemin[indiceChemin] = numSommetActuel;
        indiceChemin++;
    }

    for (int i = 0; i < indiceChemin / 2; i++) {
        int tmp = chemin[i];
        chemin[i] = chemin[indiceChemin - 1 - i];
        chemin[indiceChemin - 1 - i] = tmp;
    }

    chemin[indiceChemin] = positionFinale;
    indiceChemin++;

    *nbrTournants = 0;
    Direction directionPrecedente = directionInitiale;

    for (int i = 0; i < indiceChemin - 1; i++) {
        if (trouverDirectionEntreSommets(chemin[i + 1], chemin[i], taille) != directionPrecedente) {
            *nbrTournants += 1;
        }
        directionPrecedente = trouverDirectionEntreSommets(chemin[i + 1], chemin[i], taille);
    }

    return indiceChemin - 1;  // le nombre d'arrêts
}

int distance(int sommet1, int sommet2, int taille, Ville ville) {
    int distance;
    int chemin[taille * taille];
    bool possible;

    Labyrinthe* lab = V_labyrinthe(&ville);

    Direction directionDepart = L_obtenirDirectionDepart(*lab);
    Direction directionFinale;

    distance = courtCheminBFS(*lab, sommet1, taille, sommet2, chemin, &possible, directionDepart, &directionFinale);  // peut être optimisable à revoir

    if (!possible) {
        distance = 0;
    }

    return distance;
}

int sommetLePlusProche(int positionInitiale, Ville ville, int taille, bool estAtteint[]) {
    int distanceMin = taille * taille;
    int indiceProche = -1;

    int nombreObjectifs = V_obtenirNbObjectifs(ville);

    for (int i = 0; i < nombreObjectifs - 1; i++) {  // l-1 pour ne pas inclure le depart qui est le dernier objectif à atteindre
        int but = V_obtenirIemeObjectif(ville, i);
        if (!estAtteint[i] && positionInitiale != but) {
            int distanceCalculee = distance(positionInitiale, but, taille, ville);
            if (distanceCalculee < distanceMin) {
                distanceMin = distanceCalculee;
                indiceProche = i;
            }
        }
    }

    if (indiceProche != -1)
        estAtteint[indiceProche] = true;

    return indiceProche;  // -1 si aucun objectif dispo
}

void remettreTableauAZero(int chemin[], int n) {
    for (int i = 0; i < n; i++) {
        chemin[i] = 0;
    }
}

void afficherOrdreAvancer() {
    printf("AV\n");
}

void afficherOrdreTournerDroite() {
    printf("TD\n");
    afficherOrdreAvancer();
}

void afficherOrdreTournerGauche() {
    printf("TG\n");
    afficherOrdreAvancer();
}

Direction afficherOrdre(Sommet initiale, Sommet suivant, Direction direction, int taille) {
    if (S_obtenirNumSommet(initiale) == S_obtenirNumSommet(suivant) + 1) {
        // On doit avancer à O
        switch (direction) {
            case O:
                if (S_nombreVoisins(initiale) > 2) {
                    afficherOrdreAvancer();
                }
                break;
            case E:
                fprintf(stderr, "ERREUR demi tour impossible\n");
                exit(EXIT_FAILURE);
                break;
            case N:
                afficherOrdreTournerGauche();
                break;
            case S:
                afficherOrdreTournerDroite();
                break;
        }
        return O;
    } else if (S_obtenirNumSommet(initiale) == S_obtenirNumSommet(suivant) - 1) {
        // On doit avancer à E
        switch (direction) {
            case O:
                fprintf(stderr, "ERREUR demi tour impossible\n");
                exit(EXIT_FAILURE);
                break;
            case E:
                if (S_nombreVoisins(initiale) > 2) {
                    afficherOrdreAvancer();
                }
                break;
            case N:
                afficherOrdreTournerDroite();
                break;
            case S:
                afficherOrdreTournerGauche();
                break;
        }
        return E;
    } else if (S_obtenirNumSommet(initiale) == S_obtenirNumSommet(suivant) + taille) {
        // On doit avancer à N
        switch (direction) {
            case O:
                afficherOrdreTournerDroite();
                break;
            case E:
                afficherOrdreTournerGauche();
                break;
            case N:
                if (S_nombreVoisins(initiale) > 2) {
                    afficherOrdreAvancer();
                }
                break;
            case S:
                fprintf(stderr, "ERREUR demi tour impossible\n");
                exit(EXIT_FAILURE);
                break;
        }
        return N;
    } else if (S_obtenirNumSommet(initiale) == S_obtenirNumSommet(suivant) - taille) {
        // On doit avancer à S
        switch (direction) {
            case O:
                afficherOrdreTournerGauche();
                break;
            case E:
                afficherOrdreTournerDroite();
                break;
            case N:
                fprintf(stderr, "ERREUR demi tour impossible\n");
                exit(EXIT_FAILURE);
                break;
            case S:
                if (S_nombreVoisins(initiale) > 2) {
                    afficherOrdreAvancer();
                }
                break;
        }
        return S;
    }
    return direction;
}

int trouverPredecesseur(int sommet, Direction direction, int taille) {
    switch (direction) {
        case N:
            return sommet + taille;
        case S:
            return sommet - taille;
        case E:
            return sommet - 1;
        case O:
            return sommet + 1;
    }
    return N;
}

Direction trouverDirectionEntreSommets(int sommet, int predecesseur, int taille) {
    if (predecesseur == sommet - 1) {
        return E;
    } else if (predecesseur == sommet + 1) {
        return O;
    } else if (predecesseur == sommet + taille) {
        return N;
    } else if (predecesseur == sommet - taille) {
        return S;
    }
    return N;
}
