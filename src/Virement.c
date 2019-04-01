#include "../include/Virement.h"

struct Virement_s
{
    int id_compteFrom;
    int id_compteTo;
    char *date;
    double montant;
    Virement virement_suivant;
};

Virement cr_virement(int id_compteFrom, int id_compteTo, char *date, double montant)
{
    Virement res;
    res = malloc(sizeof(Virement));
    res->id_compteFrom = id_compteFrom;
    res->id_compteTo = id_compteTo;
    res->date = date;
    res->montant = montant;
    return res;
}

Virement LCinitVirement()
{
    Virement LCVirement;
    LCVirement = malloc(sizeof(Virement));
    LCVirement = NULL;
    return LCVirement;
}

void addLCVirement(Virement LCVirement, Virement vir)
{
    if (LCVirement == NULL) {
        LCVirement = vir;
    } else {
        Virement etude = LCVirement;
        while(etude->virement_suivant != NULL){
            etude = etude->virement_suivant;
        }
        etude->virement_suivant = vir;
    }
}

int getIdCompteFrom(Virement virement)
{
    return virement->id_compteFrom;
}

int getIdCompteTo(Virement virement)
{
    return virement->id_compteTo;
}

char *getDate(Virement virement)
{
    return virement->date;
}

double getMontantVir(Virement virement)
{
    return virement->montant;
}