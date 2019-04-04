#ifndef VIREMENT_H
#define VIREMENT_H

//--------------INCLUDE--------------

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

//--------------STRUCT--------------

typedef struct Virement_s * Virement;

//--------------METHODS--------------

int getIndex();

Virement cr_virement(int id_comptefrom, int id_compteto, char date[8], double montant);
void LCinitVirement(int index, Virement LCVirement);
    /*
    Retourne la file chainée des virements
    */
void addLCVirement(Virement LCVirement, Virement vir);
    /*
    Ajoute un virement a une liste chainée de virements
    */

//#GET
int getIdCompteFrom(Virement vir);
int getIdCompteTo(Virement vir);
char * getDate(Virement vir);
double getMontantVir(Virement vir);
Virement getNextVir(Virement vir);

#endif