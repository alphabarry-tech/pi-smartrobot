#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>
#include <stdlib.h>
#include "../include/graphe.h"
#include "../include/sommet.h"

/* Tests pour la création d'un graphe */
void test_creerGraphe(void) {
    Graphe g = G_creer(10);
    CU_ASSERT_EQUAL(G_nbSommets(g), 0);
    CU_ASSERT_PTR_NOT_NULL(g.sommets);
    G_detruire(&g);
}

/* Tests pour vérifier l'existence d'un sommet */
void test_estSommet(void) {
    Graphe g = G_creer(10);
    Sommet s1 = S_creer(1);
    G_ajouterSommet(&g, s1);

    CU_ASSERT_TRUE(G_estSommet(g, 1));
    CU_ASSERT_FALSE(G_estSommet(g, 2));

    G_detruire(&g);
}

/* Tests pour obtenir un sommet */
void test_obtenirSommet(void) {
    Graphe g = G_creer(10);
    Sommet s1 = S_creer(5);
    G_ajouterSommet(&g, s1);

    Sommet s_obtenu = G_obtenirSommet(g, 5);
    CU_ASSERT_EQUAL(S_obtenirNumSommet(s_obtenu), 5);

    G_detruire(&g);
}

/* Tests pour ajouter des sommets */
void test_ajouterSommet(void) {
    Graphe g = G_creer(10);
    Sommet s1 = S_creer(1);
    Sommet s2 = S_creer(2);
    Sommet s3 = S_creer(3);

    G_ajouterSommet(&g, s1);
    CU_ASSERT_EQUAL(G_nbSommets(g), 1);

    G_ajouterSommet(&g, s2);
    CU_ASSERT_EQUAL(G_nbSommets(g), 2);

    G_ajouterSommet(&g, s3);
    CU_ASSERT_EQUAL(G_nbSommets(g), 3);

    /* Ajouter le même sommet ne devrait pas augmenter le nombre */
    G_ajouterSommet(&g, s1);
    CU_ASSERT_EQUAL(G_nbSommets(g), 3);

    G_detruire(&g);
}

/* Tests pour fixer des passages entre sommets */
void test_fixerPassage(void) {
    Graphe g = G_creer(10);

    /* Ajouter un passage créé les sommets s'ils n'existent pas */
    G_fixerPassage(&g, 1, 2);

    CU_ASSERT_TRUE(G_estSommet(g, 1));
    CU_ASSERT_TRUE(G_estSommet(g, 2));
    CU_ASSERT_EQUAL(G_nbSommets(g), 2);

    /* Vérifier que les passages bidirectionnels sont créés */
    Sommet s1 = G_obtenirSommet(g, 1);
    Sommet s2 = G_obtenirSommet(g, 2);

    CU_ASSERT_TRUE(S_estVoisin(s1, 2));
    CU_ASSERT_TRUE(S_estVoisin(s2, 1));

    G_detruire(&g);
}

/* Tests pour plusieurs passages */
void test_multiplesPassages(void) {
    Graphe g = G_creer(10);

    G_fixerPassage(&g, 1, 2);
    G_fixerPassage(&g, 2, 3);
    G_fixerPassage(&g, 1, 3);

    CU_ASSERT_EQUAL(G_nbSommets(g), 3);

    Sommet s1 = G_obtenirSommet(g, 1);
    Sommet s2 = G_obtenirSommet(g, 2);
    Sommet s3 = G_obtenirSommet(g, 3);

    /* Sommet 1 doit avoir 2 voisins */
    CU_ASSERT_EQUAL(S_nombreVoisins(s1), 2);
    CU_ASSERT_TRUE(S_estVoisin(s1, 2));
    CU_ASSERT_TRUE(S_estVoisin(s1, 3));

    /* Sommet 2 doit avoir 2 voisins */
    CU_ASSERT_EQUAL(S_nombreVoisins(s2), 2);
    CU_ASSERT_TRUE(S_estVoisin(s2, 1));
    CU_ASSERT_TRUE(S_estVoisin(s2, 3));

    /* Sommet 3 doit avoir 2 voisins */
    CU_ASSERT_EQUAL(S_nombreVoisins(s3), 2);
    CU_ASSERT_TRUE(S_estVoisin(s3, 1));
    CU_ASSERT_TRUE(S_estVoisin(s3, 2));

    G_detruire(&g);
}

/* Tests pour la destruction du graphe */
void test_detruire(void) {
    Graphe g = G_creer(10);
    Sommet s1 = S_creer(1);
    G_ajouterSommet(&g, s1);

    G_detruire(&g);
    CU_ASSERT_EQUAL(G_nbSommets(g), 0);
    CU_ASSERT_PTR_NULL(g.sommets);
}


int main(void) {
    CU_initialize_registry();
    
    CU_pSuite suite = CU_add_suite("Test Graphe", NULL, NULL);
    
    CU_add_test(suite, "test_creerGraphe", test_creerGraphe);
    CU_add_test(suite, "test_estSommet", test_estSommet);
    CU_add_test(suite, "test_obtenirSommet", test_obtenirSommet);
    CU_add_test(suite, "test_ajouterSommet", test_ajouterSommet);
    CU_add_test(suite, "test_fixerPassage", test_fixerPassage);
    CU_add_test(suite, "test_multiplesPassages", test_multiplesPassages);
    CU_add_test(suite, "test_detruire", test_detruire);
    
    CU_basic_run_tests();
    CU_cleanup_registry();
    
    return CU_get_error();
}
