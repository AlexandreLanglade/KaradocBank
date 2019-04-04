#include "../include/Virement.h"

struct Virement_s
{
    int id_compteFrom;
    int id_compteTo;
    char *date;
    double montant;
    Virement virement_suivant;
};

int
getIndex(){
    //TODO
}

Virement cr_virement(int id_compteFrom, int id_compteTo, char *date, double montant)
{
    Virement res;
    res = malloc(sizeof(Virement));
    res->id_compteFrom = id_compteFrom;
    res->id_compteTo = id_compteTo;
    res->date = date; // pas en param mais ici, non?
    res->montant = montant;
    return res;
}

Virement LCinitVirement()
{
    FILE *f;
    char compt[100];
    int  i, i_compt;
    Virement LCVirement, virement;
    LCVirement = NULL;
    virement = cr_virement(0, 0, "00000000", 0);
    sprintf(compt, "ls ../data/Virements | wc -l");
    f = popen (compt, "r") ;
    fgets(compt, 100, f);
    i_compt = atoi(compt);
    for(i = 1; i <= i_compt; i++){
        virement = lecture_fichier_json_virement(i, virement);
        addLCVirement(LCVirement, virement);
    }
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

Virement
getNextVir(Virement vir) {
    return vir->virement_suivant;
}