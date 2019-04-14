#include "../include/Virement.h"

struct Virement_s
{
    int id_compteFrom;
    int id_compteTo;
    char * date;
    double montant;
    Virement virement_suivant;
};

/*

    retourne l'index indiqué dans le fichier index.txt

*/

int
getIndexVirement(){
    FILE *file;
	file = fopen("data/Virements/index.txt", "r");
	int index;
    if(file != NULL){
        fscanf(file, "%d\n", &index);
    }
    else{printf("ERROR READING FILE INDEX.TXT\n");}
    fclose(file);
	return index;
}

/*

    incrémente l'index du fichier index.txt

*/

void incrementerIndexVirement(int index)
{
    FILE *file;
    file = fopen("data/Virements/index.txt", "w");
    index++;
    if(file != NULL) fprintf(file, "%d", index);
    fclose(file);
}

/*

    créer un virement, son fichier correspondant et l'ajoute à la liste chaînée

*/

void cr_virement(Virement LCvirement, int id_compteFrom, int id_compteTo, double montant)
{
    Virement res;
    res = malloc(sizeof(Virement));
    res->id_compteFrom = id_compteFrom;
    res->id_compteTo = id_compteTo;
    res->date = getDate_today();
    res->montant = montant;
    printf("%d %d %d %s %lf\n", getIndexVirement(), res->id_compteFrom, res->id_compteTo, res->date, res->montant);
    creer_fichier_json_virement(getIndexVirement(), res->id_compteFrom, res->id_compteTo, res->date, res->montant);
    incrementerIndexVirement(getIndexVirement());
    addLCVirement(&LCvirement, res);
}

/*

    rempli le virement correspondant à l'index passé en paramètre et l'ajoute
    à la liste chaînée

*/

void LCinitVirement(int index, Virement * LCVirement)
{
    Virement res;
    res = malloc(sizeof(Virement));
    res->date = malloc(sizeof(char)*32);
    lecture_fichier_json_virement(index, res);
    addLCVirement(LCVirement, res);
}

/*

    ajoute le virement passé en paramètre à la liste chaînée des virements

*/

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

/*

    GETTERS

*/

int getIdCompteFrom(Virement virement)
{
    return virement->id_compteFrom;
}

int getIdCompteTo(Virement virement)
{
    return virement->id_compteTo;
}

char * getDate(Virement virement)
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

/*

    SETTERS

*/

void
setSuivVNull(Virement virement) {
    virement->virement_suivant = NULL;
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
    strcpy(vir->date, date);
}

void setVMontant(Virement vir, double montant)
{
    vir->montant = montant;
}