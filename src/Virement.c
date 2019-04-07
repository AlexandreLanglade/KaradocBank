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
    FILE *file;
	file = fopen("../data/Virements/index.txt", "r");
	char temp[10];
	fgets(temp, 10, file);
	int index = atoi(temp);
    return index;
}

void cr_virement(Virement LCvirement, int id_compteFrom, int id_compteTo, double montant)
{
    Virement res;
    res = malloc(sizeof(Virement));
    res->id_compteFrom = id_compteFrom;
    res->id_compteTo = id_compteTo;
    res->date = getDate_today();
    res->montant = montant;
    creer_fichier_json_virement(getIndex(), res->id_compteFrom, res->id_compteTo, res->date, res->montant);
    addLCVirement(&LCvirement, res);
}

void LCinitVirement(int index, Virement * LCVirement)
{
    Virement res;
    res = malloc(sizeof(Virement));
    lecture_fichier_json_virement(index, res);
    addLCVirement(LCVirement, res);
}

void addLCVirement(Virement * LCVirement, Virement vir)
{
    if (*LCVirement == NULL) {
        *LCVirement = malloc(sizeof(Virement));
        *LCVirement = vir;
    } else {
        Virement etude = *LCVirement;
        while(etude->virement_suivant != NULL){
            etude = etude->virement_suivant;
        }
        etude->virement_suivant = vir;
    }
}

void
setSuivVNull(Virement virement) {
    virement->virement_suivant = NULL;
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