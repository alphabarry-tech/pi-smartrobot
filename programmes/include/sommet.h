/**
 * @file sommet.h
 * @brief Définition du TAD Sommet
 *
 * Un sommet représente une case utile du labyrinthe. Il possède :
 *  - un numéro de case (> 0)
 *  - une liste de voisins (max 4)
 *  - un nombre de voisins actuellement enregistrés
 */

#ifndef SOMMET_H
#define SOMMET_H

#include <stdbool.h>

#define MAX_VOISINS 4  ///< Nombre maximum de voisins par sommet

// ######### PUBLIC #########

/**
 * @struct Sommet
 * @brief Structure interne du TAD Sommet
 */
typedef struct {
    int num;                    ///< Numéro de case (> 0)
    int voisins[MAX_VOISINS];   ///< Liste des voisins (numéros de sommets)
    int nbVoisins;              ///< Nombre de voisins valides
} Sommet;

/**
 * @brief Création d’un sommet à partir de son numéro
 * @param n Numéro du sommet (> 0)
 * @return Le sommet créé
 */
Sommet S_creer(int n);

/**
 * @brief Récupère le numéro du sommet
 * @param s Sommet
 * @return Numéro de la case
 */
int S_obtenirNumSommet(Sommet s);

/**
 * @brief Renvoie le nombre de voisins enregistrés
 * @param s Sommet
 * @return Nombre de voisins (Naturel)
 */
int S_nombreVoisins(Sommet s);

/**
 * @brief Vérifie si un numéro est un voisin du sommet
 * @param s Sommet
 * @param v Numéro du voisin à tester
 * @return true si v est un voisin, false sinon
 */
bool S_estVoisin(Sommet s, int v);

/**
 * @brief Ajoute un voisin au sommet si possible
 * @param s Pointeur sur un sommet modifiable
 * @param v Numéro du voisin
 */
void S_ajouterVoisin(Sommet* s, int v);

/**
 * @brief Donne le i-ème voisin du sommet
 * @param s Sommet
 * @param i index (0 <= i < S_nombreVoisins(s))
 * @return Numéro du voisin
 */
int S_obtenirIemeVoisin(Sommet s, int i);

#endif
