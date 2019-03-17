#include "../include/Virement.h"

struct Virement_s
{
    int id_compteFrom;
    int id_compteTo;
    char date[8];
    double montant;
    Virement virement_suivant;
};

Virement cr_virement(int id_comptefrom, int id_compteto, char date[8], double montant);
int getIdCompteFrom(Virement vir);
int getIdCompteTo(Virement vir);
char * getDate(Virement vir);
double getMontantVir(Virement vir);