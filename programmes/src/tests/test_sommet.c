#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>

#include "sommet.h"

void test_creation_sommet(void) {
    Sommet s = S_creer(5);

    CU_ASSERT_EQUAL(S_obtenirNumSommet(s), 5);
    CU_ASSERT_EQUAL(S_nombreVoisins(s), 0);
}

void test_ajouter_voisin(void) {
    Sommet s = S_creer(1);

    S_ajouterVoisin(&s, 2);
    CU_ASSERT_EQUAL(S_nombreVoisins(s), 1);
    CU_ASSERT_TRUE(S_estVoisin(s, 2));
    CU_ASSERT_EQUAL(S_obtenirIemeVoisin(s, 0), 2);
}

void test_ajouter_voisin_doublon(void) {
    Sommet s = S_creer(1);

    S_ajouterVoisin(&s, 2);
    S_ajouterVoisin(&s, 2);  // tentative d'ajout en double
    CU_ASSERT_EQUAL(S_nombreVoisins(s), 1);
}

void test_limite_voisins(void) {
    Sommet s = S_creer(10);

    for (int i = 0; i < MAX_VOISINS + 2; i++) {
        S_ajouterVoisin(&s, 100 + i);
    }
    CU_ASSERT_EQUAL(S_nombreVoisins(s), MAX_VOISINS);
    for (int i = 0; i < MAX_VOISINS; i++) {
        CU_ASSERT_TRUE(S_estVoisin(s, 100 + i));
    }
}

void test_obtenir_ieme_voisin_hors_borne(void) {
    Sommet s = S_creer(2);

    S_ajouterVoisin(&s, 7);
    CU_ASSERT_EQUAL(S_obtenirIemeVoisin(s, -1), -1);
    CU_ASSERT_EQUAL(S_obtenirIemeVoisin(s, 1), -1);
}

int main(void) {
    CU_pSuite suite_sommet = NULL;

    /* initialisation du registre de tests */
    if (CUE_SUCCESS != CU_initialize_registry())
        return CU_get_error();

    /* ajout d'une suite de test */
    suite_sommet = CU_add_suite("Suite_Sommet", NULL, NULL);
    if (suite_sommet == NULL) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    CU_add_test(suite_sommet, "Création d'un sommet", test_creation_sommet);
    CU_add_test(suite_sommet, "Ajout d'un voisin", test_ajouter_voisin);
    CU_add_test(suite_sommet, "Ajout doublon", test_ajouter_voisin_doublon);
    CU_add_test(suite_sommet, "Limite de voisins", test_limite_voisins);
    CU_add_test(suite_sommet, "Ieme voisin hors borne", test_obtenir_ieme_voisin_hors_borne);

    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();

    CU_cleanup_registry();
    return CU_get_error();
}

