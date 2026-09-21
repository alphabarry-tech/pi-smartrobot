/**
 * @file labyrinthe.h
 * @brief Définition du TAD Labyrinthe
 *
 * Le labyrinthe regroupe :
 *  - une position de départ
 *  - une direction initiale du robot
 *  - un graphe représentant la structure du labyrinthe
 *  - la taille du labyrinthe
 */

#ifndef LABYRINTHE_H
#define LABYRINTHE_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "graphe.h"
#include "sommet.h"

// ######### PUBLIC #########

/**
 * @brief Directions possibles du robot dans le labyrinthe
 */
typedef enum {N, S, E, O} Direction;

/**
 * @struct Labyrinthe
 * @brief Structure interne du TAD Labyrinthe
 */
typedef struct {
    int positionDepart;  ///< Case où démarre le robot
    Direction directionDepart;  ///< Orientation initiale du robot
    Graphe connexions;   ///< Structure des passages (Graphe)
    int taille;       ///< Nombre total de sommets utiles
} Labyrinthe;


/**
 * @brief Crée un labyrinthe
 * @param p Numéro de case de départ (> 0)
 * @param d Direction initiale du robot
 * @param n Nombre de sommets utiles (> 0)
 * @return Labyrinthe créé
 */
Labyrinthe L_creer(int p, Direction d, int n);

/**
 * @brief Ajoute un passage entre deux cases du labyrinthe
 * @param l Pointeur sur le labyrinthe à modifier
 * @param a Numéro du premier sommet (> 0)
 * @param b Numéro du second sommet (> 0)
 */
void L_ajouterPassage(Labyrinthe* l, int a, int b);

/**
 * @brief Retourne les connexions du labyrinthe
 * @param l Labyrinthe
 * @return Le graphe d'interconnexions
 */
Graphe L_obtenirConnexions(Labyrinthe l);

/**
 * @brief Récupère le nombre de sommets du labyrinthe
 * @param l Labyrinthe
 * @return Nombre de sommets (Naturel)
 */
int L_obtenirTaille(Labyrinthe l);

/**
 * @brief Récupère la position de départ du robot
 * @param l Labyrinthe
 * @return Numéro de la case de départ
 */
int L_obtenirPositionDepart(Labyrinthe l);

/**
 * @brief Récupère la direction de départ du robot
 * @param l Labyrinthe
 * @return Direction initiale du robot
 */
Direction L_obtenirDirectionDepart(Labyrinthe l);

/**
 * @brief Affiche les informations du labyrinthe
 * @param l Labyrinthe à afficher
 */
void L_afficherLabyrinthe(Labyrinthe l);

/**
 * @brief Libère les ressources associées au labyrinthe
 * @param l Pointeur vers le labyrinthe à détruire
 */
void L_detruire(Labyrinthe *l);

#endif
