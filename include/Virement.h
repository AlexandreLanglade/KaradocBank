#ifndef VIREMENT_H
#define VIREMENT_H

//--------------INCLUDE--------------

#include <stdio.h>
#include <stdlib.h>

//--------------STRUCT--------------

typedef struct Virement_s * Virement;

//--------------METHODS--------------

Virement cr_virement(int id_comptefrom, int id_compteto, char date[8], double montant);
Virement LCinitVirement();
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

#endif