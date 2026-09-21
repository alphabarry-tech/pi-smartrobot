/**
 * @file graphe.h
 * @brief Définition du TAD Graphe
 *
 * Un graphe représente l'ensemble des sommets et des passages entre eux.
 * La structure interne contient :
 *  - un tableau de sommets (TAD Sommet)
 *  - le nombre de sommets actuellement présents
 */

#ifndef GRAPHE_H
#define GRAPHE_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "sommet.h"

// ######### PUBLIC #########

/**
 * @struct Graphe
 * @brief Structure interne du TAD Graphe
*/
typedef struct {
    Sommet *sommets; ///< Ensemble des sommets utiles
    int nbSommets;               ///< Nombre actuel de sommets présents
} Graphe;

/**
 * @brief Crée un graphe vide 
 *  une fonction qui retourne le nombre de sommets du graphe 
 * @return Un graphe initialisé sans sommet
 */
Graphe G_creer(int n);

/**
 * @brief Trouve l'indice d'un sommet dans le tableau à partir de son nom
 * @param g Graphe
 * @param n Nom du sommet recherché
 * @return indice (>=0) ou -1 s'il n'existe pas
 */
int G_indiceSommet(Graphe g, int n);

/**
 * @brief Renvoie le nombre de sommets présents dans le graphe
 * @param g Graphe
 * @return Nombre de sommets (Naturel)
 */
int G_nbSommets(Graphe g);

/**
 * @brief Vérifie si un sommet avec ce nom existe dans le graphe
 * fonction qui vérifie si un sommet identifié par son num est un sommet
 * @param g Graphe
 * @param n Numéro du sommet cherché
 * @return true si présent, false sinon
 */
bool G_estSommet(Graphe g, int n);

/**
 * @brief Récupère un sommet du graphe à partir de son nom
 * fonction qui permet d'obtenir un sommet connaissant son num
 * @param g Graphe
 * @param n Numéro du sommet à récupérer
 * @return Sommet
 *
 * @warning Précondition : estSommet(g, n)
 */
Sommet G_obtenirSommet(Graphe g, int n);

/**
 * @brief Ajoute un sommet dans le graphe s'il n'existe pas déjà
 * fonction qui permet d'ajouter un sommet au graphe
 * @param g Pointeur sur le graphe à modifier
 * @param s Sommet à ajouter
 */
void G_ajouterSommet(Graphe* g, Sommet s);

/**
 * @brief Ajoute un passage bidirectionnel entre deux sommets a et b
 * fonction qui permet d'ajouter un passage entre deux sommets
 * @param g Pointeur sur le graphe à modifier
 * @param a Numéro du premier sommet
 * @param b Numéro du second sommet
 */
void G_fixerPassage(Graphe* g, int a, int b);

/**
 * @brief Libère la mémoire allouée pour le graphe
 * Ajoute un passage bidirectionnel entre deux sommets a et b
 * @param g Pointeur sur le graphe à libérer
 */
void G_detruire(Graphe* g);

#endif
