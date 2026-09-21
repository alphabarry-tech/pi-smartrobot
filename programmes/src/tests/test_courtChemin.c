#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>
#include <stdio.h>

#include "trouverPlusCourtChemin.h"


void test_reconstituerChemin(void) {
    int taille = 3;
    int predecesseurs[9];
    for (int i=0;i<9;i++) predecesseurs[i] = 0;

    // chemin: 1 -> 2 -> 3 -> 6 -> 5
    predecesseurs[2] = 1;
    predecesseurs[3] = 2;
    predecesseurs[6] = 3;
    predecesseurs[5] = 6;

    int chemin[9];

    for (int i=0;i<9;i++) chemin[i] = -1;

    int tournants = 0;

    int nbArrets = reconstituerChemin( predecesseurs, chemin, 1, 5, E, taille, &tournants);

    CU_ASSERT_EQUAL(nbArrets, 4); 
    CU_ASSERT_EQUAL(tournants, 2); 

    CU_ASSERT_EQUAL(chemin[0], 1);
    CU_ASSERT_EQUAL(chemin[1], 2);
    CU_ASSERT_EQUAL(chemin[2], 3);
    CU_ASSERT_EQUAL(chemin[3], 6);
    CU_ASSERT_EQUAL(chemin[4], 5);
}


void test_explorerVoisins(void) {
    Graphe graphe = G_creer(10);
    G_fixerPassage(&graphe,1,2);
    G_fixerPassage(&graphe,2,3);
    G_fixerPassage(&graphe,3,6);
    G_fixerPassage(&graphe,6,5);
    G_fixerPassage(&graphe,5,2);
    G_fixerPassage(&graphe,2,3);
    G_fixerPassage(&graphe, 8,5);

    bool visite[9] ;
    int predecesseurs[9];
    LCF_ListeChaineeFile file;

    initialiserBFS(3, visite,predecesseurs, &file);
    int sommetaExplorer = 5 ;
    int *a=&sommetaExplorer;

    int parent = 2;

    explorerVoisins(&graphe, sommetaExplorer, visite, predecesseurs, &file, parent);

    CU_ASSERT_FALSE(visite[2]);      
    CU_ASSERT_TRUE(visite[6]);
    CU_ASSERT_TRUE(visite[8]);

    CU_ASSERT_EQUAL(predecesseurs[6], 5);
    CU_ASSERT_EQUAL(predecesseurs[8], 5);

    a = (int*) LCF_defiler(&file);

    CU_ASSERT_EQUAL(*a,6);

    a = (int*) LCF_defiler(&file);

    CU_ASSERT_EQUAL(*a, 8);

    G_detruire(&graphe);
}

void test_trouverPredecesseurEtTrouverDirectionEntreSommets(void) {

    int taille = 3;
    CU_ASSERT_EQUAL(trouverPredecesseur(5, N, taille), 8); 
    CU_ASSERT_EQUAL(trouverPredecesseur(5, S, taille), 2); 
    CU_ASSERT_EQUAL(trouverPredecesseur(5, E, taille), 4); 
    CU_ASSERT_EQUAL(trouverPredecesseur(5, O, taille), 6); 

    CU_ASSERT_EQUAL(trouverDirectionEntreSommets(5, 4, taille), E);
    CU_ASSERT_EQUAL(trouverDirectionEntreSommets(5, 6, taille), O);
    CU_ASSERT_EQUAL(trouverDirectionEntreSommets(5, 8, taille), N);
    CU_ASSERT_EQUAL(trouverDirectionEntreSommets(5, 2, taille), S);
}


void test_distanceEntreDeuxSommets(void){

    Ville ville;

    Direction directionInitiale = E;

    int positionInitial = 1;

    int taille = 3;

    Labyrinthe lab = L_creer(positionInitial,directionInitiale,taille);

    L_ajouterPassage(&lab, 1, 2);
    L_ajouterPassage(&lab, 2, 3);
    L_ajouterPassage(&lab, 3, 6);
    L_ajouterPassage(&lab, 5, 6);
    L_ajouterPassage(&lab, 5, 8);
    L_ajouterPassage(&lab, 7, 8);
    L_ajouterPassage(&lab, 4, 7);
    L_ajouterPassage(&lab, 9, 6);
    
    ville = V_creer(lab);

    int d = distance(1, 4, taille, ville);

    CU_ASSERT_EQUAL(d, 12);

    V_detruire(ville); 
}

void test_sommetLePlusProche(void) {
    int taille = 3;

    Direction directionInitiale = E;

    int positionInitiale = 1;

    Labyrinthe lab = L_creer(positionInitiale, directionInitiale, taille);

    
    L_ajouterPassage(&lab, 1, 2);
    L_ajouterPassage(&lab, 2, 3); 
    L_ajouterPassage(&lab, 3, 6);
    L_ajouterPassage(&lab, 5, 6); 
    L_ajouterPassage(&lab, 5, 8); 
    L_ajouterPassage(&lab, 7, 8); 
    L_ajouterPassage(&lab, 4, 7);
    L_ajouterPassage(&lab, 9, 6);
    L_ajouterPassage(&lab, 9, 8);

    Ville ville = V_creer(lab);


    V_ajouterObjectif(&ville, 5); 
    V_ajouterObjectif(&ville, 4); 

    int nb = V_obtenirNbObjectifs(ville);

    
    bool estAtteint[2] = {false};
    for (int i = 0; i < nb; i++) estAtteint[i] = false;

    int indice = sommetLePlusProche(positionInitiale, ville, taille, estAtteint);

    CU_ASSERT_EQUAL(indice, 0);          
    CU_ASSERT_TRUE(estAtteint[0]);       
    CU_ASSERT_FALSE(estAtteint[1]);      

    V_detruire(ville); 
}

void  test_courtCheminEntreDeuxSommets(void) {

    Direction directionInitiale = E;

    int positionInitial = 1;

    int taille = 3;

    bool possible;

    Direction directionFinale;

    int positionFinal = 4;

    Labyrinthe lab = L_creer(positionInitial,directionInitiale,taille);

    int chemin [9];

    L_ajouterPassage(&lab, 1, 2);
    L_ajouterPassage(&lab, 2, 3);
    L_ajouterPassage(&lab, 3, 6);
    L_ajouterPassage(&lab, 5, 6);
    L_ajouterPassage(&lab, 5, 8);
    L_ajouterPassage(&lab, 7, 8);
    L_ajouterPassage(&lab, 4, 7);
    L_ajouterPassage(&lab, 9, 6);
    L_ajouterPassage(&lab, 9, 8);

    
    int distance = courtCheminBFS(lab,positionInitial, taille*taille, positionFinal, chemin, &possible, directionInitiale, &directionFinale);
   
    CU_ASSERT_EQUAL(possible, true);
    CU_ASSERT_EQUAL(distance, 12); // c'est le nombre d'arrêts + les tournants
    CU_ASSERT_EQUAL(directionFinale, N);
    L_detruire(&lab);
}

void test_courtCheminAvecPlusieursObjectifs(void) {

    Ville ville;

    LCL_Liste chemins;

    Direction directionInitiale = E;

    int positionInitial = 1;

    int taille = 3;

    bool possible;

    Labyrinthe lab = L_creer(positionInitial,directionInitiale,taille);

    L_ajouterPassage(&lab, 1, 2);
    L_ajouterPassage(&lab, 2, 3);
    L_ajouterPassage(&lab, 3, 6);
    L_ajouterPassage(&lab, 5, 6);
    L_ajouterPassage(&lab, 5, 8);
    L_ajouterPassage(&lab, 7, 8);
    L_ajouterPassage(&lab, 4, 7);
    L_ajouterPassage(&lab, 9, 6);
    L_ajouterPassage(&lab, 9, 8);
    L_ajouterPassage(&lab, 4, 1);
    
    ville = V_creer(lab);

    V_ajouterObjectif(&ville,5);
    V_ajouterObjectif(&ville,4);
    
    int distance = plusCourtCheminAvecBFS(ville, &possible, &chemins);
   
    CU_ASSERT_EQUAL(possible, true);
    CU_ASSERT_EQUAL(distance, 14); // c'est le nombre d'arrêts + les tournants

    V_detruire(ville);
   
}

int main(void) {
    CU_pSuite suite_courtChemin = NULL;

    /* initialisation du registre de tests */
    if (CUE_SUCCESS != CU_initialize_registry())
        return CU_get_error();

    /* ajout d'une suite de test */
    suite_courtChemin = CU_add_suite("Suite_Sommet", NULL, NULL);
    if (suite_courtChemin == NULL) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    CU_add_test(suite_courtChemin, "Reconstitutions de chemins à partir de la liste des predecesseurs",test_reconstituerChemin);
    CU_add_test(suite_courtChemin, "Explorer les voisins",test_explorerVoisins);
    CU_add_test(suite_courtChemin, "Trouver le predecesseur selon la direction et trouver la direction selon le predecesseur", test_trouverPredecesseurEtTrouverDirectionEntreSommets);
    CU_add_test(suite_courtChemin, "Distance entre deux points", test_distanceEntreDeuxSommets);
    CU_add_test(suite_courtChemin, "Indice du plus proche objecifs",test_sommetLePlusProche);
    CU_add_test(suite_courtChemin, "Court chemin entre deux objectifs", test_courtCheminEntreDeuxSommets);
    CU_add_test(suite_courtChemin, "Court chemin avec plusieurs objectifs", test_courtCheminAvecPlusieursObjectifs);

    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();

    CU_cleanup_registry();
    return CU_get_error();
}

