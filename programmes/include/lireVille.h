/** @file lireVille.h
 * @brief Définition des fonctions pour afficher les ordres et créer une ville à partir d'un fichier.
 */

#ifndef LIRE_VILLE_H
#define LIRE_VILLE_H

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "graphe.h"
#include "labyrinthe.h"
#include "sommet.h"
#include "ville.h"

// ######### PUBLIC #########

/**
 * @brief Crée une ville à partir d'un fichier de description.
 * @param nomFichier Le nom du fichier.
 * @return La ville créée.
 */
Ville creerVilleAPartirDeFichier(const char* nomFichier);

// ######### PRIVATE (ONLY USE FOR TEST) #########

/**
 * @brief Donne la taille d'une chaîne de caractères.
 * @param str La chaîne de caractères.
 * @return La longueur de la chaîne.
 * @warning Fonction privée, à n'utiliser que pour les tests.
 */
int tailleChaine(const char* str);

/**
 * @brief Trouve la position d'un caractère dans une chaîne.
 * @param str La chaîne de caractères.
 * @param caractere Le caractère à chercher.
 * @return L'indice du caractère dans la chaîne, ou -1 s'il n'est pas trouvé.
 * @warning Fonction privée, à n'utiliser que pour les tests.
 */
int positionCharDansChaine(const char* str, char caractere);

/**
 * @brief Vérifie si une chaîne contient un caractère donné.
 * @param str La chaîne de caractères.
 * @param caractere Le caractère à chercher.
 * @return true si le caractère est trouvé, false sinon.
 * @warning Fonction privée, à n'utiliser que pour les tests.
 */
bool contientCaractere(const char* str, char caractere);

/**
 * @brief Convertit une chaîne de caractères en entier.
 * @param str La chaîne de caractères représentant un entier.
 * @return L'entier converti.
 * @warning Fonction privée, à n'utiliser que pour les tests.
 */
int chaineEnEntier(const char* str);

/**
 * @brief Convertit un caractère en une direction.
 * @param c Le caractère ('N', 'S', 'E', 'O').
 * @return La direction correspondante.
 * @warning Fonction privée, à n'utiliser que pour les tests.
 */
Direction charEnDirection(char c);

/**
 * @brief Copie une sous-chaîne de source dans destination, de l'indice debut (inclus) à fin (exclu).
 * @param source La chaîne source.
 * @param destination La chaîne destination (doit être assez grande).
 * @param debut Indice de début (inclus).
 * @param fin Indice de fin (exclu).
 * @warning Fonction privée, à n'utiliser que pour les tests.
 */
void copierUneSousChaine(const char* source, char* destination, int debut, int fin);

/**
 * @brief
 * @param ligne La ligne à parser (ex: "3N" ou "24S").
 * @param position Pointeur vers l'entier où stocker la position.
 * @param direction Pointeur vers la direction où stocker la direction.
 * @warning Fonction privée, à n'utiliser que pour les tests.
 */
void lirePositionInitial(const char* ligne, int* position, Direction* direction);

/**
 * @brief
 * @param ville Pointeur vers la ville à modifier.
 * @param connexion La chaîne décrivant la connexion (ex: "1-2").
 * @warning Fonction privée, à n'utiliser que pour les tests.
 */
void lireConnexion(Ville* ville, const char* connexion);

#endif
