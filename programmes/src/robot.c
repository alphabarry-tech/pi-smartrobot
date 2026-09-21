#include "robot.h"

// SCREEN
#define I2C_SCREEN 0x27  // adresse I2C pour ecran

#define AF_BASE 64
#define AF_RS (AF_BASE + 0)
#define AF_RW (AF_BASE + 1)
#define AF_E (AF_BASE + 2)
#define AF_LED (AF_BASE + 3)

#define AF_DB4 (AF_BASE + 4)
#define AF_DB5 (AF_BASE + 5)
#define AF_DB6 (AF_BASE + 6)
#define AF_DB7 (AF_BASE + 7)

// RGB
#define RGB_I2C 0x29          // adresse I2C pour capteur RGB
#define RGB_COMMAND_BIT 0x80  // Commande pour accéder aux registres
#define RGB_R_BIT 0x16        // Registre pour R
#define RGB_G_BIT 0x18        // Registre pour G
#define RGB_B_BIT 0x1A        // Registre pour B
#define RGB_BUZZER 4          // GPIO 23

// CAPTEUR
#define CAPTEUR_GAUCHE 25         // GPIO 26
#define CAPTEUR_CENTRE_GAUCHE 5   // GPIO 24
#define CAPTEUR_CENTRE_DROITE 29  // GPIO 21
#define CAPTEUR_DROITE 2          // GPIO 27

// MOTEUR
#define MOTEUR_EN1 26  // GPIO 12 : PWM2
#define MOTEUR_EN2 24  // GPIO 19 : PWM1

#define MOTEUR_IN1 27  // GPIO 16
#define MOTEUR_IN2 22  // GPIO 6
#define MOTEUR_IN3 21  // GPIO 5
#define MOTEUR_IN4 6   // GPIO 25

// VITESSES
#define ROTATION_LEFT_SPEED_LEFT 0
#define ROTATION_LEFT_SPEED_RIGHT 70 

#define ROTATION_RIGHT_SPEED_LEFT 70
#define ROTATION_RIGHT_SPEED_RIGHT 0

#define LEFT_SPEED 70
#define RIGHT_SPEED 70

#define LOW_SPEED_QUALIBRATE 40 
#define HIGH_SPEED_QUALIBRATE 70

// TEMPS
#define MS 1000
#define S 1000000

#define WAIT_BEFORE_START 5       // temps d'attente en s
#define WAIT_TO_ALIGN 100         // temps d'attente en ms
#define CHECK_EVERY 1000          // temps d'attente en us
#define TIME_BETWEEN_ACTIONS 50  // temps d'attente en ms

#define ANIMATION 50  // temps d'attente en ms

// Variables globales :
static int lcdHandle;
int fileDescriptor;

bool capteur_DO_gauche = false;
bool capteur_DO_centre_gauche = false;
bool capteur_DO_centre_droite = false;
bool capteur_DO_droite = false;

int compteurEcran = 0;

int init_capteurRGB() {
    pinMode(RGB_BUZZER, OUTPUT);

    digitalWrite(RGB_BUZZER, LOW);

    fileDescriptor = wiringPiI2CSetup(RGB_I2C);
    if (fileDescriptor == -1) {
        fprintf(stderr, "Erreur I2C RGB\n");
        exit(EXIT_FAILURE);
    }

    // 1) Activer le capteur
    wiringPiI2CWriteReg8(fileDescriptor, RGB_COMMAND_BIT | 0x00, 0x01);  // PON = Power ON
    wiringPiI2CWriteReg8(fileDescriptor, RGB_COMMAND_BIT | 0x00, 0x03);  // Power on est l'activation de l'ADC

    // 2) le temps necessaire pour accumuler la lumière
    wiringPiI2CWriteReg8(fileDescriptor, RGB_COMMAND_BIT | 0x01, 250);  // la formule c'est (256 -ATIME) * 2,5

    // 3) Gain du capteur
    wiringPiI2CWriteReg8(fileDescriptor, RGB_COMMAND_BIT | 0x0F, 0x02);  // CONTROL (gain x4)

    return fileDescriptor;
}

void init_screen() {
    pcf8574Setup(AF_BASE, 0x27);

    lcdHandle = lcdInit(2, 16, 4, AF_RS, AF_E, AF_DB4, AF_DB5, AF_DB6, AF_DB7, 0, 0, 0, 0);
    if (lcdHandle < 0) {
        fprintf(stderr, "lcdInit failed\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < 8; i++) {
        pinMode(AF_BASE + i, OUTPUT);
    }

    digitalWrite(AF_LED, 1);
    digitalWrite(AF_RW, 0);
}

void init_capteur() {
    pinMode(CAPTEUR_GAUCHE, INPUT);
    pinMode(CAPTEUR_CENTRE_GAUCHE, INPUT);
    pinMode(CAPTEUR_CENTRE_DROITE, INPUT);
    pinMode(CAPTEUR_DROITE, INPUT);
}

void init_motor() {
    pinMode(MOTEUR_IN1, OUTPUT);
    pinMode(MOTEUR_IN2, OUTPUT);
    pinMode(MOTEUR_IN3, OUTPUT);
    pinMode(MOTEUR_IN4, OUTPUT);

    pinMode(MOTEUR_EN1, PWM_OUTPUT);
    pinMode(MOTEUR_EN2, PWM_OUTPUT);

    pwmSetRange(100);  // met en pourcentage
}

void setup() {
    if (wiringPiSetup() < 0) {
        fprintf(stderr, "wiringPi Setup failed!\n");
        exit(EXIT_FAILURE);
    }

    init_screen();

    init_capteur();

    init_motor();

    init_capteurRGB();

    motor_stop();
}

void print_on_screen(char* newChaine, int ligne) {
    lcdPosition(lcdHandle, 0, ligne);
    lcdPrintf(lcdHandle, "%s", newChaine);
}

void clear_screen() {
    print_on_screen("                ", 0);
    print_on_screen("                ", 1);
}

bool check_for_color(bool lastInstruction) {
    int r = wiringPiI2CReadReg16(fileDescriptor, RGB_COMMAND_BIT | RGB_R_BIT);
    int g = wiringPiI2CReadReg16(fileDescriptor, RGB_COMMAND_BIT | RGB_G_BIT);
    int b = wiringPiI2CReadReg16(fileDescriptor, RGB_COMMAND_BIT | RGB_B_BIT);

    if (r == -1 || g == -1 || b == -1) {
        fprintf(stderr, "Erreur avec wiringPiI2CReadReg16\n");
    }

    float diffR = 1.2;
    float diffB = 1.2;
    float diffG = 1.10;

    if ((r > g * diffR) && (r > b * diffR)) {  // rouge
        if (lastInstruction) {
            return true;
        } else {
            compteurEcran++;
            digitalWrite(RGB_BUZZER, HIGH);
            if (compteurEcran == 3) {  // on attend un peu avant d'afficher pour eviter les fausses detections
                                       // On le fait que 1 fois pour eviter de spammer l'ecran
                print_on_screen("Couleur: Rouge", 1);
            }
        }

    } else if ((b > g * diffB) && (b > r * diffB)) {  // bleu
        compteurEcran++;
        digitalWrite(RGB_BUZZER, HIGH);
        if (compteurEcran == 3) {
            print_on_screen("Couleur: Bleu", 1);
        }
    } else if ((g > r * diffG) && (g > b * diffG)) {  // vert
        compteurEcran++;
        digitalWrite(RGB_BUZZER, HIGH);
        if (compteurEcran == 3) {
            print_on_screen("Couleur: Vert", 1);
        }
    } else {  // autre
        compteurEcran = 0;
        digitalWrite(RGB_BUZZER, LOW);
    }

    return false;
}

void update_sensors() {
    capteur_DO_gauche = digitalRead(CAPTEUR_GAUCHE);
    capteur_DO_centre_gauche = digitalRead(CAPTEUR_CENTRE_GAUCHE);
    capteur_DO_centre_droite = digitalRead(CAPTEUR_CENTRE_DROITE);
    capteur_DO_droite = digitalRead(CAPTEUR_DROITE);

    wait(CHECK_EVERY);
}

void motor_speed(int speedLeft, int speedRight) {
    pwmWrite(MOTEUR_EN1, speedLeft);
    pwmWrite(MOTEUR_EN2, speedRight);
}

void motor_go_front() {
    motor_speed(LEFT_SPEED, RIGHT_SPEED);

    digitalWrite(MOTEUR_IN1, LOW);
    digitalWrite(MOTEUR_IN2, HIGH);
    digitalWrite(MOTEUR_IN3, LOW);
    digitalWrite(MOTEUR_IN4, HIGH);
}

void motor_go_left() {
    motor_speed(ROTATION_LEFT_SPEED_LEFT, ROTATION_LEFT_SPEED_RIGHT);

    digitalWrite(MOTEUR_IN1, HIGH);
    digitalWrite(MOTEUR_IN2, LOW);
    digitalWrite(MOTEUR_IN3, LOW);
    digitalWrite(MOTEUR_IN4, HIGH);
}

void motor_go_right() {
    motor_speed(ROTATION_RIGHT_SPEED_LEFT, ROTATION_RIGHT_SPEED_RIGHT);

    digitalWrite(MOTEUR_IN1, LOW);
    digitalWrite(MOTEUR_IN2, HIGH);
    digitalWrite(MOTEUR_IN3, HIGH);
    digitalWrite(MOTEUR_IN4, LOW);
}

void go_back() {
    digitalWrite(MOTEUR_IN1, HIGH);
    digitalWrite(MOTEUR_IN2, LOW);
    digitalWrite(MOTEUR_IN3, HIGH);
    digitalWrite(MOTEUR_IN4, LOW);
}

void motor_stop() {
    digitalWrite(MOTEUR_IN1, LOW);
    digitalWrite(MOTEUR_IN2, LOW);
    digitalWrite(MOTEUR_IN3, LOW);
    digitalWrite(MOTEUR_IN4, LOW);
}

void trajectory_correction() {
    if (!capteur_DO_centre_gauche && capteur_DO_centre_droite) {
        // Le robot dévie à gauche

        motor_speed(HIGH_SPEED_QUALIBRATE, LOW_SPEED_QUALIBRATE);

        wait(MS * WAIT_TO_ALIGN);

        motor_speed(LEFT_SPEED, RIGHT_SPEED);

    } else if (capteur_DO_centre_gauche && !capteur_DO_centre_droite) {
        // Le robot dévie à droite

        motor_speed(LOW_SPEED_QUALIBRATE, HIGH_SPEED_QUALIBRATE);

        wait(MS * WAIT_TO_ALIGN);

        motor_speed(LEFT_SPEED, RIGHT_SPEED);
    }
}

bool AV(bool lastInstruction) {
    clear_screen();
    print_on_screen("Avancer", 0);

    motor_go_front();

    // Avance jusqu'a perdre l'ancienne ligne (si il y en avait une)
    while ((capteur_DO_gauche || capteur_DO_droite) && !check_for_color(lastInstruction)) {
        update_sensors();
        trajectory_correction();
    }

    // Avance jusqu'a retrouver une ligne
    while (!(capteur_DO_gauche || capteur_DO_droite) && !check_for_color(lastInstruction)) {
        update_sensors();
        trajectory_correction();
    }

    motor_stop();

    wait(MS * TIME_BETWEEN_ACTIONS);

    return check_for_color(lastInstruction);
}

void TG() {
    clear_screen();
    print_on_screen("Tourner Gauche", 0);

    motor_go_left();

    // Tourne jusqu'a lacher la ligne centrale
    while ((capteur_DO_centre_gauche)) {
        update_sensors();
    }

    // Tourne jusqu'a recuperer la ligne centrale
    while (!(capteur_DO_centre_gauche)) {
        update_sensors();
    }

    motor_stop();

    wait(MS * TIME_BETWEEN_ACTIONS);
}

void TD() {
    clear_screen();
    print_on_screen("Tourner Droite", 0);

    motor_go_right();

    // Tourne jusqu'a lacher la ligne centrale
    while ((capteur_DO_centre_droite)) {
        update_sensors();
    }

    // Tourne jusqu'a recuperer la ligne centrale
    while (!(capteur_DO_centre_droite)) {
        update_sensors();
    }

    motor_stop();

    wait(MS * TIME_BETWEEN_ACTIONS);
}

void start() {
    // Demare le robot et lui donne les inscructions a suivre
    clear_screen();
    print_on_screen("Demarage", 0);

    // lit l'entree standard et fait les bonne actions
    char buffer[16];

    while (fgets(buffer, sizeof(buffer), stdin) != NULL && buffer[0] != '.') {
        if (strncmp(buffer, "AV", 2) == 0) {
            bool lastInstruction = false;

            // Vérifie si c'est la dernière instruction (fin de fichier après cette ligne)
            int c = fgetc(stdin);
            if (c == '.' || c == '\n' || c == EOF) {
                lastInstruction = true;
                fprintf(stderr, "Derniere instruction\n");
            }
            if (c != EOF) {
                ungetc(c, stdin);  // Remet le caractère pour la prochaine lecture
            }

            if (AV(lastInstruction)) {
                fprintf(stderr, "Couleur rouge detectee, arret du robot\n");
            }
        } else if (strncmp(buffer, "TG", 2) == 0) {
            TG();
        } else if (strncmp(buffer, "TD", 2) == 0) {
            TD();
        }
    }
}

void wait_to_alignement() {
    // Attend que le robot soit bien place (evite de le faire partir si il n'est pas droit)
    clear_screen();
    print_on_screen("Allignement", 0);
    print_on_screen("En attente...", 1);

    int compteur = -1;

    while ((compteur < WAIT_BEFORE_START * S / CHECK_EVERY) ) {
        if (!capteur_DO_centre_gauche && !capteur_DO_centre_droite) {
            // Robot bien place
            compteur += 1;
        } else {
            // Robot mal
            compteur = -1;
        }

        if (compteur % ((int)(S / CHECK_EVERY)) == 0) {
            char chaine[32];
            snprintf(chaine, sizeof(chaine), "En attente %2ds", WAIT_BEFORE_START - compteur / ((int)(S / CHECK_EVERY)));
            print_on_screen("Allignement", 0);
            print_on_screen(chaine, 1);
        }

        update_sensors();
    }

    clear_screen();
    print_on_screen("Allignement", 0);
    print_on_screen("Valide", 1);
}

void end(){
    // Animation de fin

    print_on_screen("             #  ", 0);
    print_on_screen("-------------#--", 1);

    wait(ANIMATION * MS);

    print_on_screen("o            #  ", 0);
    print_on_screen("-------------#--", 1);

    wait(ANIMATION * MS);

    print_on_screen(" o           #  ", 0);
    print_on_screen("-------------#--", 1);

    wait(ANIMATION * MS);

    print_on_screen("  o          #  ", 0);
    print_on_screen("-------------#--", 1);

    wait(ANIMATION * MS);

    print_on_screen("   o         #  ", 0);
    print_on_screen("-------------#--", 1);

    wait(ANIMATION * MS);

    print_on_screen("    o        #  ", 0);
    print_on_screen("-------------#--", 1);

    wait(ANIMATION * MS);

    print_on_screen("     o       #  ", 0);
    print_on_screen("-------------#--", 1);

    wait(ANIMATION * MS);

    print_on_screen("      o      #  ", 0);
    print_on_screen("-------------#--", 1);

    wait(ANIMATION * MS);

    print_on_screen("       o     #  ", 0);
    print_on_screen("-------------#--", 1);

    wait(ANIMATION * MS);

    print_on_screen("        o    #  ", 0);
    print_on_screen("-------------#--", 1);

    wait(ANIMATION * MS);

    print_on_screen("         o   #  ", 0);
    print_on_screen("-------------#--", 1);
    wait(ANIMATION * MS);

    print_on_screen("          o  #  ", 0);
    print_on_screen("-------------#--", 1);
    wait(ANIMATION * MS);

    print_on_screen("           o #  ", 0);
    print_on_screen("-------------#--", 1);
    wait(ANIMATION * MS);

    print_on_screen("            o#  ", 0);
    print_on_screen("-------------#--", 1);
    wait(ANIMATION * MS);

    print_on_screen("             o  ", 0);
    print_on_screen("-------------#--", 1);
    wait(ANIMATION * MS);

    print_on_screen("             #o ", 0);
    print_on_screen("-------------#--", 1);

    for (int i = 0; i < 3; i++) {
        digitalWrite(RGB_BUZZER, HIGH);
        wait(150 * MS);
        digitalWrite(RGB_BUZZER, LOW);
        wait(100 * MS);
    }

    print_on_screen("  |          |  ", 0);
    print_on_screen("   ----------   ", 1);
}

void wait(int microsecondes) {
    delayMicroseconds(microsecondes);
}

int main(int argc, char* argv[]) {
    setup();

    clear_screen();

    wait_to_alignement();

    motor_speed(LEFT_SPEED, RIGHT_SPEED);

    start();

    end();

    return EXIT_SUCCESS;
}
