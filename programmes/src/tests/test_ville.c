#include <stdio.h>
#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>
#include <string.h>
#include <stdbool.h>
#include "ville.h"


int init_suite_success(void) {
  return 0; 
}

int clean_suite_success(void) {
  return 0; 
}

void test_V_creer(void){
  int p = 2;
  Direction d = E;
  int n = 4;
  Ville v = V_creer(L_creer(p,d,n));
  CU_ASSERT_EQUAL(LCL_longueur(v.objectifs), 0);
  Labyrinthe l = v.labyrinthe;
  CU_ASSERT_EQUAL(L_obtenirPositionDepart(l), p);
  CU_ASSERT_EQUAL(L_obtenirDirectionDepart(l), d);
  CU_ASSERT_EQUAL(L_obtenirTaille(l), n);
  Graphe g = L_obtenirConnexions(l);
  CU_ASSERT_EQUAL(G_nbSommets(g), 0);
  LCL_vider(&v.objectifs);
  L_detruire(&l);

}

void test_V_ajouterObjectif(void){
  Ville v = V_creer(L_creer(0,N,0));
  V_ajouterObjectif(&v, 2);
  int obj = *(int*)LCL_element(v.objectifs, 0);
  CU_ASSERT_EQUAL(obj, 2);
  CU_ASSERT_EQUAL(LCL_longueur(v.objectifs), 1);
  LCL_vider(&v.objectifs);
  L_detruire(&v.labyrinthe);
}

void test_V_obtenirIemeObjectif(void){
  Ville v = V_creer(L_creer(0,N,0));
  V_ajouterObjectif(&v, 2);
  V_ajouterObjectif(&v, 5);
  V_ajouterObjectif(&v, 3);
  V_ajouterObjectif(&v, 8);
  int obj = V_obtenirIemeObjectif(v, 2);
  CU_ASSERT_EQUAL(obj, 3);
  LCL_vider(&v.objectifs);
  L_detruire(&v.labyrinthe);
}

void test_V_obtenirNbObjectifs(void){
  Ville v = V_creer(L_creer(0,N,0));
  V_ajouterObjectif(&v, 2);
  V_ajouterObjectif(&v, 5);
  V_ajouterObjectif(&v, 3);
  int nbObj = V_obtenirNbObjectifs(v);
  CU_ASSERT_EQUAL(nbObj, 3);
  LCL_vider(&v.objectifs);
  L_detruire(&v.labyrinthe);
}

void test_V_detruire(void){
  Ville v = V_creer(L_creer(2,E,4));
  V_detruire(v);
  CU_ASSERT_EQUAL(V_obtenirNbObjectifs(v), 0);
  CU_ASSERT_EQUAL(G_nbSommets(L_obtenirConnexions(v.labyrinthe)), 0);
}

int main(int argc, char* *argv){
  CU_pSuite suite = NULL;

  /* initialisation du registre de tests */
  if (CUE_SUCCESS != CU_initialize_registry())
    return CU_get_error();

  /* ajout d'une suite de test */
  suite = CU_add_suite("Tests", init_suite_success, clean_suite_success);
  if (NULL == suite) {
    CU_cleanup_registry();
    return CU_get_error();
  }

  if ((NULL == CU_add_test(suite, "créer la ville", test_V_creer))||(NULL == CU_add_test(suite, "ajouter un objectif", test_V_ajouterObjectif))||(NULL == CU_add_test(suite, "obtenir le ième objectif", test_V_obtenirIemeObjectif))||(NULL == CU_add_test(suite, "obtenir le nombre d'objectifs", test_V_obtenirNbObjectifs))||(NULL == CU_add_test(suite, "détruire la ville", test_V_detruire))) {
      CU_cleanup_registry();
      return CU_get_error();
  }

  /* Lancement des tests */
  CU_basic_set_mode(CU_BRM_VERBOSE);
  CU_basic_run_tests();
  printf("\n");
  CU_basic_show_failures(CU_get_failure_list());
  printf("\n\n");

  /* Nettoyage du registre */
  CU_cleanup_registry();
  return CU_get_error();
}
