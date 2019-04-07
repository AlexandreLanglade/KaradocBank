#ifndef VIREMENT_H
#define VIREMENT_H

//--------------INCLUDE--------------

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "type.h"
#include "KaradocUtil.h"

//--------------METHODS--------------

int getIndexVirement();

void cr_virement(Virement LCvirement, int id_comptefrom, int id_compteto, double montant);
void LCinitVirement(int index, Virement * LCVirement);
    /*
    Retourne la file chainée des virements
    */
void addLCVirement(Virement * LCVirement, Virement vir);
    /*
    Ajoute un virement a une liste chainée de virements
    */

//#SET
void setSuivVNull(Virement virement);
void setIdCompteFrom(Virement vir, int id);
void setIdCompteTo(Virement vir, int id);
void setDate(Virement vir, char* date);
void setVMontant(Virement vir, double montant);

//#GET
int getIdCompteFrom(Virement vir);
int getIdCompteTo(Virement vir);
char * getDate(Virement vir);
double getMontantVir(Virement vir);
Virement getNextVir(Virement vir);

#endif