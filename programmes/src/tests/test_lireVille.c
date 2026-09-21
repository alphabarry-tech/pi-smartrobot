#include "afficherOrdres.h"
#include <stdio.h>
#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>
#include <string.h>
#include <stdbool.h>


int init_suite_success(void) { 
  return 0; 
}

int clean_suite_success(void) { 
  return 0; 
}

void test_lireVille(void){
  
  Ville laVille = creerVilleAPartirDeFichier("notreVille.txt");
  int obj[] = {14,15};
  int i;
  Labyrinthe lab =  *V_labyrinthe(&laVille);
  Direction dir = O;
  CU_ASSERT_TRUE(L_obtenirTaille(lab) == 5);
  CU_ASSERT_TRUE(L_obtenirPositionDepart(lab) == 18);
  CU_ASSERT_EQUAL(L_obtenirDirectionDepart(lab), dir);
  CU_ASSERT_TRUE(G_nbSommets(L_obtenirConnexions(lab)) == 24);
  for (i = 0; i < 2; i++) {
    CU_ASSERT_TRUE(V_obtenirIemeObjectif(laVille, i) == obj[i]);
  }
  V_detruire(laVille);
}

void test_lireConnexion(void) {
    Ville laVille = V_creer(L_creer(0, N, 0));
    lireConnexion(&laVille, "3-4");
    Labyrinthe lab = *V_labyrinthe(&laVille);
    CU_ASSERT_TRUE(G_estSommet(L_obtenirConnexions(lab), 3));
    CU_ASSERT_TRUE(G_estSommet(L_obtenirConnexions(lab), 4));
    CU_ASSERT_TRUE(S_estVoisin(G_obtenirSommet(L_obtenirConnexions(lab), 3), 4));
    CU_ASSERT_TRUE(S_estVoisin(G_obtenirSommet(L_obtenirConnexions(lab), 4), 3));
}

void test_lirePositionInitial(void){
  int pos;
  Direction dir;
  Direction directionAttendu = E;
  lirePositionInitial("3E\n", &pos, &dir);
  CU_ASSERT_TRUE(pos == 3);
  CU_ASSERT_EQUAL(dir, directionAttendu);
}

void test_copierUneSousChaine(void){
  char resultat[12];
  char* resultatAttendu = "sous-chaine";
  copierUneSousChaine("Ceci est une sous-chaine de caractères", resultat, 13, 24);
  CU_ASSERT_STRING_EQUAL(resultat, resultatAttendu);
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

  if ((NULL == CU_add_test(suite, "créer la ville", test_lireVille)) || (NULL == CU_add_test(suite, "mettre à jour une connexion", test_lireConnexion)) || (NULL == CU_add_test(suite, "lire la position initiale", test_lirePositionInitial)) || (NULL == CU_add_test(suite, "copier une sous-chaine", test_copierUneSousChaine))) {
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
