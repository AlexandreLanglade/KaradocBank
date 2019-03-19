#include "../include/Virement.h"

struct Virement_s
{
    int id_compteFrom;
    int id_compteTo;
    char date[8];
    double montant;
    Virement virement_suivant;
};