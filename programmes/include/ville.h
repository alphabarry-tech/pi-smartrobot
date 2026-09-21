/** @file ville.h
 * @brief Définitions du TAD Ville
 */

#ifndef VILLE_H
#define VILLE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "labyrinthe.h"
#include "listeChaineeDEntier.h"

// ######### PUBLIC #########

/**
 * @brief Structure interne du TAD Ville
 */
typedef struct {
    Labyrinthe labyrinthe;  ///< Le labyrinthe de la ville
    LCL_Liste objectifs;    ///< La liste des objectifs de la ville
} Ville;

/**
 * @brief Crée une ville à partir d'un labyrinthe.
 * @param lab le Labyrinthe
 * @return La ville créée.
 */
Ville V_creer(Labyrinthe lab);

/** @brief Ajoute un objectif à la ville.
 * @param v Pointeur vers la ville.
 * @param objectif L'objectif à ajouter.
 */
void V_ajouterObjectif(Ville* v, int objectif);

/** @brief Obtient le i-ème objectif de la ville.
 * @param v La ville.
 * @param i L'indice de l'objectif à obtenir.
 * @return L'objectif à l'indice i.
 */

int V_obtenirIemeObjectif(Ville v, int i);

/** @brief Obtient le nombre d'objectifs dans la ville.
 * @param v La ville.
 * @return Le nombre d'objectifs.
 */
int V_obtenirNbObjectifs(Ville v);

/** @brief Obtient un pointeur vers le labyrinthe de la ville.
 * @param v Pointeur vers la ville.
 * @return Pointeur vers le labyrinthe.
 */
Labyrinthe *V_labyrinthe(Ville *v);

/** @brief Affiche les informations de la ville.
 * @param v La ville à afficher.
 */
void V_afficherVille(Ville v);

/** @brief Détruit la ville et libère les ressources associées.
 * @param v La ville à détruire.
 */
void V_detruire(Ville v);

#endif