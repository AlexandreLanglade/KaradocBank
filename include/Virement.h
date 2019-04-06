#ifndef VIREMENT_H
#define VIREMENT_H

//--------------INCLUDE--------------

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "type.h"
#include "KaradocUtil.h"

//--------------METHODS--------------

int getIndex();

Virement cr_virement(int id_comptefrom, int id_compteto, double montant);
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