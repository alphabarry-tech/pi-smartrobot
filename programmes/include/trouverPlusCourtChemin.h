/**
 * @file trouverPlusCourtChemin.h
 * @brief Fonctions de recherche du plus court chemin dans une ville.
 * Permet de determiner et d'afficher la liste des ordres à effectuer pour suivre le plus court chemin.
 *
 */

#ifndef TROUVER_PLUS_COURT_CHEMIN_H
#define TROUVER_PLUS_COURT_CHEMIN_H

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "labyrinthe.h"
#include "listeChaineeDEntier.h"
#include "ville.h"

// ######### PUBLIC #########

/**
 * @brief procedure qui affiche la liste des ordres à effectuer pour suivre le plus court chemin
 * @param v Pointeur vers la ville
 */
void listeOrdre(Ville* v);

// ######### PRIVATE (ONLY USE FOR TEST) #########

/**
 * @brief Fonction qui calcule le plus court chemin pour atteindre tous les objectifs dans une ville en utilisant BFS.
 * @param v La ville dans laquelle chercher le chemin.
 * @param possible Pointeur vers un booléen indiquant si le chemin est possible.
 * @param chemins Pointeur vers une liste chaînée contenant les chemins.
 * @return La distance totale du chemin trouvé.
 * @warning Fonction privée, à n'utiliser que pour les tests.
 */
int plusCourtCheminAvecBFS(Ville v, bool* possible, LCL_Liste* chemins);

/**
 * @brief Fonction qui initialise les structures nécessaires pour l'algorithme BFS.
 * @param taille La taille du labyrinthe.
 * @param visite Tableau indiquant si un sommet a été visité.
 * @param predecesseurs Tableau des prédécesseurs pour chaque sommet.
 * @param file Pointeur vers la file utilisée dans BFS.
 * @warning Fonction privée, à n'utiliser que pour les tests.
 */
void initialiserBFS(int taille, bool visite[], int predecesseurs[], LCF_ListeChaineeFile* file);

/**
 * @brief Fonction qui implémente l'algorithme BFS pour trouver le plus court chemin entre deux positions dans un labyrinthe.
 * @param lab Le labyrinthe.
 * @param positionInital La position de départ.
 * @param taille La taille du labyrinthe.
 * @param positionFinal La position d'arrivée.
 * @param chemin Tableau pour stocker le chemin trouvé.
 * @param possible Pointeur vers un booléen indiquant si le chemin est possible.
 * @param directionInitiale La direction initiale du robot.
 * @param directionFinale Pointeur vers la direction finale du robot.
 * @return La longueur du chemin trouvé.
 * @warning Fonction privée, à n'utiliser que pour les tests.
 */
int courtCheminBFS(Labyrinthe lab, int positionInital, int taille, int positionFinal, int chemin[], bool* possible, Direction directionInitiale, Direction* directionFinale);

/**
 * @brief Fonction qui explore les voisins d'un sommet dans le graphe pendant l'algorithme BFS.
 * @param grapheDeConnexions Le graphe des connexions du labyrinthe.
 * @param num Le numéro du sommet courant.
 * @param visite Tableau indiquant si un sommet a été visité.
 * @param predecesseurs Tableau des prédécesseurs pour chaque sommet.
 * @param file Pointeur vers la file utilisée dans BFS.
 * @param parent Le sommet parent pour éviter les retours en arrière.
 * @warning Fonction privée, à n'utiliser que pour les tests.
 */
void explorerVoisins(Graphe* grapheDeConnexions, int num, bool visite[], int predecesseurs[], LCF_ListeChaineeFile* file, int parent);

/**
 * @brief Fonction qui reconstitue le chemin entre deux positions à partir des prédécesseurs.
 * @param predecesseurs Tableau des prédécesseurs pour chaque sommet.
 * @param chemin Tableau pour stocker le chemin reconstitué.
 * @param positionInitiale La position de départ.
 * @param positionFinale La position d'arrivée.
 * @param directionInitiale La direction initiale du robot.
 * @param taille La taille du labyrinthe.
 * @param nbrTournants Pointeur vers un entier pour stocker le nombre de tournants dans le chemin.
 * @return La longueur du chemin reconstitué.
 * @warning Fonction privée, à n'utiliser que pour les tests.
 */
int reconstituerChemin(int predecesseurs[], int chemin[], int positionInitiale, int positionFinale, Direction directionInitiale, int taille, int* nbrTournants);

/**
 * @brief Fonction qui calcule la distance entre deux sommets dans une ville.
 * @param sommet1 Le numéro du premier sommet.
 * @param sommet2 Le numéro du second sommet.
 * @param taille La taille du labyrinthe.
 * @param ville La ville contenant le labyrinthe.
 * @return La distance entre les deux sommets, ou 0 si aucun chemin n'est possible.
 * @warning Fonction privée, à n'utiliser que pour les tests.
 */
int distance(int sommet1, int sommet2, int taille, Ville ville);

/**
 * @brief Fonction qui trouve le sommet le plus proche parmi les objectifs non atteints.
 * @param depart Le sommet de départ.
 * @param ville La ville contenant les objectifs.
 * @param taille La taille du labyrinthe.
 * @param estAtteint Tableau indiquant quels objectifs ont été atteints.
 * @return L'indice de l'objectif le plus proche, ou -1 si aucun objectif n'est disponible.
 * @warning Fonction privée, à n'utiliser que pour les tests.
 */
int sommetLePlusProche(int depart, Ville ville, int taille, bool estAtteint[]);

/**
 * @brief Fonction qui remet à zéro un tableau d'entiers.
 * @param chemin Le tableau à remettre à zéro.
 * @param n La taille du tableau.
 * @warning Fonction privée, à n'utiliser que pour les tests.
 */
void remettreTableauAZero(int chemin[], int n);

/**
 * @brief Fonction qui affiche l'ordre d'avancer.
 * @warning Fonction privée, à n'utiliser que pour les tests.
 */
void afficherOrdreAvancer();

/**
 * @brief Fonction qui affiche l'ordre de tourner à droite.
 * @warning Fonction privée, à n'utiliser que pour les tests.
 */
void afficherOrdreTournerDroite();

/**
 * @brief Fonction qui affiche l'ordre de tourner à gauche.
 * @warning Fonction privée, à n'utiliser que pour les tests.
 */
void afficherOrdreTournerGauche();

/**
 * @brief Fonction qui affiche l'ordre à effectuer pour aller du sommet initial au sommet suivant.
 * @param initiale Le sommet initial.
 * @param suivant Le sommet suivant.
 * @param direction La direction actuelle du robot.
 * @param taille La taille du labyrinthe.
 * @return La nouvelle direction du robot après l'ordre.
 * @warning Fonction privée, à n'utiliser que pour les tests.
 */
Direction afficherOrdre(Sommet initiale, Sommet suivant, Direction direction, int taille);

/**
 * @brief Fonction qui trouve le prédécesseur d'un sommet en fonction de la direction.
 * @param sommet Le numéro du sommet.
 * @param direction La direction à partir du sommet.
 * @param taille La taille du labyrinthe.
 * @return Le numéro du prédécesseur du sommet.
 * @warning Fonction privée, à n'utiliser que pour les tests.
 */
int trouverPredecesseur(int sommet, Direction direction, int taille);

/**
 * @brief Fonction qui trouve la direction entre deux sommets.
 * @param sommet Le numéro du sommet actuel.
 * @param predecesseur Le numéro du prédécesseur du sommet.
 * @param taille La taille du labyrinthe.
 * @return La direction entre les deux sommets.
 * @warning Fonction privée, à n'utiliser que pour les tests.
 */
Direction trouverDirectionEntreSommets(int sommet, int predecesseur, int taille);

#endif
