/**
 * @file listeChaineeDEntier.h
 * @brief Définition de la liste chaînée d'entiers, avec des fonctions de copie et de suppression.
 * @note On cree file et liste d'entier.
 */

#ifndef LISTE_CHAINEE_D_ENTIER_H
#define LISTE_CHAINEE_D_ENTIER_H

#include "ListeChaineeFile.h"
#include "ListeChaineeListe.h"
#include <stdlib.h>

// ######### PUBLIC #########

/**
 * @brief Fonction qui permet de copier un entier.
 * @param element Le pointeur vers l'entier à copier.
 * @return Un pointeur vers la copie de l'entier.
 * @warning Fonction privée, à n'utiliser que pour les tests.
 */
void* copierInt(void* element);

/**
 * @brief Fonction qui permet de supprimer un entier.
 * @param element Le pointeur vers l'entier à supprimer.
 * @warning Fonction privée, à n'utiliser que pour les tests.
 */
void supprimerInt(void* element);

#endif
