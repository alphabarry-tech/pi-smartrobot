#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>

#include "labyrinthe.h"
#include "graphe.h"
#include "sommet.h"

int init_suite_success(void) { return 0; }
int clean_suite_success(void) { return 0; }

void test_L_creer(void) {
    int p = 6;
    int n = 5;
    Direction d = N;

    Labyrinthe l = L_creer(p, d, n);

    CU_ASSERT_EQUAL(L_obtenirPositionDepart(l), p);
    CU_ASSERT_EQUAL(L_obtenirDirectionDepart(l), d);
    CU_ASSERT_EQUAL(L_obtenirTaille(l), n);

    Graphe g = L_obtenirConnexions(l);
    CU_ASSERT_EQUAL(G_nbSommets(g), 0);

    L_detruire(&l);
}

void test_L_ajouterPassage(void){
    Labyrinthe l = L_creer(0, 4, 10);
    int a = 1;
    int b = 2; 
    L_ajouterPassage(&l, a, b);

    Graphe g = L_obtenirConnexions(l);
    Sommet sa = G_obtenirSommet(g, a);
    Sommet sb = G_obtenirSommet(g, b);

    CU_ASSERT_EQUAL(S_estVoisin(sa, b), true);
    CU_ASSERT_EQUAL(S_estVoisin(sb, a), true);
}

void test_L_detruire(void){
    Labyrinthe l = L_creer(6, O, 5);

    L_ajouterPassage(&l, 1, 2);

    L_detruire(&l);

    CU_ASSERT_EQUAL(L_obtenirPositionDepart(l), 0);
    CU_ASSERT_EQUAL(L_obtenirDirectionDepart(l), N);
    CU_ASSERT_EQUAL(L_obtenirTaille(l), 0);

    CU_ASSERT_EQUAL(G_nbSommets(L_obtenirConnexions(l)), 0);
}



int main(void){
    CU_pSuite suite_labyrinthe = NULL;

    if(CUE_SUCCESS != CU_initialize_registry()){
        return CU_get_error();
    }
    suite_labyrinthe = CU_add_suite("Suite Labyrinthe", NULL, NULL);
    if (suite_labyrinthe == NULL) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if (CU_add_test(suite_labyrinthe, "Creation labyrinthe", test_L_creer) == NULL ||
        CU_add_test(suite_labyrinthe, "Ajouter un Passage", test_L_ajouterPassage) == NULL ||
        CU_add_test(suite_labyrinthe, "Destruction", test_L_detruire) == NULL) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();

    CU_cleanup_registry();
    return CU_get_error();
}