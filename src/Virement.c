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
getIndexVirement(){
    FILE *file;
	file = fopen("data/Clients/index.txt", "r");
	int index;
    if(file != NULL){
        fscanf(file, "%d\n", &index);
    }
    else{printf("ERROR READING FILE INDEX.TXT\n");}
    printf("%d", index);
    fclose(file);
	return index;
}

void incrementerIndexVirement(int index)
{
    FILE *file;
    file = fopen("data/Virement/index.txt", "w");
    index++;
    if(file != NULL) fprintf(file, "%d", index);
    fclose(file);
}


void cr_virement(Virement LCvirement, int id_compteFrom, int id_compteTo, double montant)
{
    Virement res;
    res = malloc(sizeof(Virement));
    res->id_compteFrom = id_compteFrom;
    res->id_compteTo = id_compteTo;
    res->date = getDate_today();
    res->montant = montant;
    printf("%s\n", getDate_today());
    printf("%d %d %d %s %lf\n", getIndexVirement(), res->id_compteFrom, res->id_compteTo, res->date, res->montant);
    creer_fichier_json_virement(getIndexVirement(), res->id_compteFrom, res->id_compteTo, res->date, res->montant);
    incrementerIndexVirement(getIndexVirement());
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

void setIdCompteFrom(Virement vir, int id)
{
    vir->id_compteFrom = id;
}

void setIdCompteTo(Virement vir, int id)
{
    vir->id_compteTo = id;
}

void setDate(Virement vir, char *date)
{
    vir->date = date;
}

void setVMontant(Virement vir, double montant)
{
    vir->montant = montant;
}