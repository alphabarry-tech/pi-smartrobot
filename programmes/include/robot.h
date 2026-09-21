/**
 * @file robot.h
 * @brief Programme principal pour suivre les instructions AV, TG et TD données dans l'entrée standard.
 */

#include <errno.h>
#include <fcntl.h>
#include <lcd.h>
#include <pcf8574.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <wiringPi.h>
#include <wiringPiI2C.h>

// ######### PUBLIC #########

// ######### PRIVATE (ONLY USE FOR TEST) #########

/**
 * @brief Initialisation du capteur RGB
 * @warning Fonction privée, à n'utiliser que pour les tests.
 */
int init_capteurRGB();

/**
 * @brief Initialisation de l'écran LCD
 * @warning Fonction privée, à n'utiliser que pour les tests.
 */
void init_screen();

/**
 * @brief Initialisation des capteurs de ligne
 * @warning Fonction privée, à n'utiliser que pour les tests.
 */
void init_capteur();

/**
 * @brief Initialisation des moteurs
 * @warning Fonction privée, à n'utiliser que pour les tests.
 */
void init_motor();

/**
 * @brief Configuration initiale du robot
 * @warning Fonction privée, à n'utiliser que pour les tests.
 */
void setup();

/**
 * @brief Affiche une chaîne de caractères sur l'écran LCD
 * @param newChaine Chaîne de caractères à afficher (16 caractères max)
 * @param ligne Ligne de l'écran (0 ou 1)
 * @warning Fonction privée, à n'utiliser que pour les tests.
 */
void print_on_screen(char* newChaine, int ligne);

/**
 * @brief Nettoie l'écran LCD
 * @warning Fonction privée, à n'utiliser que pour les tests.
 */
void clear_screen();

/**
 * @brief Vérifie la couleur détectée par le capteur RGB
 * @param lastInstruction Indique si c'est la dernière instruction
 * @return true si la couleur rouge est détectée et que c'est la dernière instruction ou si on a du vert ou du bleu, false sinon
 * @warning Fonction privée, à n'utiliser que pour les tests.
 */
bool check_for_color(bool lastInstruction);

/**
 * @brief Met à jour l'état des capteurs de ligne
 * @warning Fonction privée, à n'utiliser que pour les tests.
 */
void update_sensors();

/**
 * @brief Définit la vitesse des moteurs
 * @param speedLeft Vitesse du moteur gauche
 * @param speedRight Vitesse du moteur droit
 * @warning Fonction privée, à n'utiliser que pour les tests.
 */
void motor_speed(int speedLeft, int speedRight);

/**
 * @brief Met les roues du robot dans la configuration pour avancer tout droit et démarre les moteurs à la bonne vitesse
 * @warning Fonction privée, à n'utiliser que pour les tests.
 */
void motor_go_front();

/**
 * @brief Met les roues du robot dans la configuration pour reculer tout droit et démarre les moteurs à la bonne vitesse
 * @warning Fonction privée, à n'utiliser que pour les tests.
 */
void motor_go_back();

/**
 * @brief Met les roues du robot dans la configuration pour tourner à gauche et démarre les moteurs à la bonne vitesse
 * @warning Fonction privée, à n'utiliser que pour les tests.
 */
void motor_go_left();

/**
 * @brief Met les roues du robot dans la configuration pour tourner à droite et démarre les moteurs à la bonne vitesse
 * @warning Fonction privée, à n'utiliser que pour les tests.
 */
void motor_go_right();

/**
 * @brief Arrête les moteurs du robot
 * @warning Fonction privée, à n'utiliser que pour les tests.
 */
void motor_stop();

/**
 * @brief Corrige la trajectoire du robot en fonction des capteurs de ligne
 * @note Ralentit une roue si le robot dévie
 * @warning Fonction privée, à n'utiliser que pour les tests.
 */
void trajectory_correction();

/**
 * @brief Attend que le robot soit bien positionné avant de démarrer
 * @warning Fonction privée, à n'utiliser que pour les tests.
 */
void wait_to_alignement();

/**
 * @brief Fait avancer le robot jusqu'à la prochaine intersection
 * @param lastInstruction Indique si c'est la dernière instruction
 * @return true si la couleur rouge est détectée, false sinon
 * @note Avance jusqu'à la prochaine intersection ou jusqu'à la détection de la couleur rouge (pour la dernière instruction)
 * @warning Fonction privée, à n'utiliser que pour les tests.
 */
bool AV(bool lastInstruction);

/**
 * @brief Fait tourner le robot de 90° vers la gauche
 * @note Tourne jusqu'à ce que le capteur de ligne central droit détecte la ligne, puis jusqu'à ce qu'il la perde
 * @warning Fonction privée, à n'utiliser que pour les tests.
 */
void TG();

/**
 * @brief Fait tourner le robot de 90° vers la droite
 * @note Tourne jusqu'à ce que le capteur de ligne central gauche détecte la ligne, puis jusqu'à ce qu'il la perde
 * @warning Fonction privée, à n'utiliser que pour les tests.
 */
void TD();

/**
 * @brief Démarre le robot et lui fait suivre les instructions lues depuis l'entrée standard
 * @warning Fonction privée, à n'utiliser que pour les tests.
 */
void start();

/**
 * @brief Annimation de fin et son
 * @warning Fonction privée, à n'utiliser que pour les tests.
 */
void end();

/**
 * @brief Attend un certain temps
 * @param microsecondes Temps d'attente en microsecondes
 * @note permet de faire des tests sans raspberry pi
 * @warning Fonction privée, à n'utiliser que pour les tests.
 */
void wait(int microsecondes);
