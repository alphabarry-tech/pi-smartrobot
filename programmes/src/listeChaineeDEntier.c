#include "listeChaineeDEntier.h"

// ######### PUBLIC #########

void* copierInt(void* element) {
    int* copie = malloc(sizeof(int));
    if (copie) {
        *copie = *(int*)element;
    }
    return copie;
}

void supprimerInt(void* element) {
    free(element);
}