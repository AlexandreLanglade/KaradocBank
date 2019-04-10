#include "../include/Compte.h"

struct Compte_s
{
    int id_compte;
    char type;
    int id_client1;
    int id_client2; //-1 si pas de deuxieme proprio
    double montant;
    char locker; //1 si lock 0 si normal 2 si demande de suppr
    Compte compte_suivant;
};

int
getIndexCompte(){
    FILE *file;
	file = fopen("data/Comptes/index.txt", "r");
	int index;
    if(file != NULL){
        fscanf(file, "%d\n", &index);
    }
    else{printf("ERROR READING FILE INDEX.TXT\n");}
    fclose(file);
	return index;
}

void incrementerIndexCompte(int index)
{
    FILE *file;
    file = fopen("data/Comptes/index.txt", "w");
    index++;
    if(file != NULL) fprintf(file, "%d", index);
    fclose(file);
}

void
cr_compte(Compte LCcompte, int id_client1, int id_client2, char type) {
    Compte res;
    res = malloc(sizeof(Compte));
    res->id_compte = getIndexCompte();
    incrementerIndexCompte(getIndexCompte());
    res->type = type; // a : livret a | c : courant | p : pel
    res->id_client1 = id_client1;
    res->id_client2 = id_client2;
    res->montant = 0;
    res->locker = 1;
    res->compte_suivant = NULL;
    creer_fichier_json_compte(res);
    addLCCompte(&LCcompte, res);
}

void
LCinitCompte(int index, Compte * LCcompte) {
    Compte res;
    res = malloc(sizeof(Compte));
    lecture_fichier_json_compte(index, res);
    addLCCompte(LCcompte, res);
}

void
toprintcompte(Compte compte) {
    //TODO: ajouter nom + saucisse   
    if (compte->type == 'c') {
        printf("%d C.COURANT %d %d %lf\n",
        compte->id_compte,
        compte->id_client1,
        compte->id_client2,
        compte->montant);
    }
    if (compte->type == 'a') {
        printf("%d LIVRET A %d %lf\n",
        compte->id_compte,
        compte->id_client1,
        compte->montant);
    }
    if (compte->type == 'p') {
        printf("%d PEL %d %lf\n",
        compte->id_compte,
        compte->id_client1,
        compte->montant);
    }
}

void
afficherComptes(Compte LCcompte) {  
    Compte etude = malloc(sizeof(Compte));
    etude = LCcompte;
    while(etude != NULL){
        if (etude->type == 'c') {
            toprintcompte(etude);
        }
        etude = etude->compte_suivant;        
    }
    etude = LCcompte;
    while(etude != NULL){
        if (etude->type == 'a') {
            toprintcompte(etude);
        }
        etude = etude->compte_suivant;        
    }
    etude = LCcompte;
    while(etude != NULL){
        if (etude->type == 'p') {
            toprintcompte(etude);
        }
        etude = etude->compte_suivant;        
    }
}

void
exporterCompte(Virement LCvir, Compte compte, char from[8], char to[8]) {
    int jfrom, mfrom, afrom, jto, mto, ato;
    jfrom = (from[0]-48)*10 + from[1]-48;
    mfrom = (from[2]-48)*10 + from[3]-48;
    afrom = (from[4]-48)*1000 + (from[5]-48)*100 + (from[6]-48)*10 + from[7]-48;
    jto = (to[0]-48)*10 + to[1]-48;
    mto = (to[2]-48)*10 + to[3]-48;
    ato = (to[4]-48)*1000 + (to[5]-48)*100 + (to[6]-48)*10 + to[7]-48;
    FILE * fichierexport = NULL;
    char nom_fichier[50] = "";
    sprintf(nom_fichier, "data/export/%d_%s_%s.csv", getIdCompte(compte), from, to);
    fichierexport = fopen(nom_fichier, "w");
    if(fichierexport != NULL){
        fputs("From,To,Date,Value\n", fichierexport);
        Virement etude = LCvir;
        while(etude != NULL) {
            if (getIdCompteFrom(etude) == getIdCompte(compte) || getIdCompteTo(etude) == getIdCompte(compte)) {
                int jetude, metude, aetude;
                jetude = (getDate(etude)[0]-48)*10 + (getDate(etude)[1]-48);
                metude = (getDate(etude)[2]-48)*10 + (getDate(etude)[3]-48);
                aetude = (getDate(etude)[4]-48)*1000 + (getDate(etude)[5]-48)*100 + (getDate(etude)[6]-48)*10 + getDate(etude)[7]-48;
                if (ato - aetude < 0 || aetude - afrom < 0) {
                    etude = getNextVir(etude);
                    break;
                }
                if ((ato - aetude == 0 && mto - metude < 0) || (aetude - afrom == 0 && metude - mfrom < 0)) {
                    etude = getNextVir(etude);
                    break;
                }
                if ((ato - aetude == 0 && mto - metude == 0 && jto - jetude < 0) || (aetude - afrom == 0 && metude - mfrom == 0 && jetude - jfrom < 0)) {
                    etude = getNextVir(etude);
                    break;
                }
                fprintf(fichierexport, "%d,%d,%d/%d/%d,%lf\n", 
                    getIdCompteFrom(etude),
                    getIdCompteTo(etude),
                    jetude,metude,aetude,
                    getMontantVir(etude)
                );
            }
            etude = getNextVir(etude);    
        }
        fclose(fichierexport);
        }
    }

    void
    supprimerCompte(Compte LCcompte, Compte compte) {
    //LE COMPTE DOIT EXISTER !!!
    char nom_fichier[30] = "";
    sprintf(nom_fichier,"data/Comptes/%d.json", getIdCompte(compte));
    remove(nom_fichier);
    Compte etude = LCcompte;
    if (etude->compte_suivant == NULL) {
        LCcompte = NULL;
        return;
    }
    while(etude->compte_suivant != compte){
        etude = etude->compte_suivant;
    }
    etude->compte_suivant = compte->compte_suivant;
}

void
titulairesCompte(Compte compte) {
    //TODO: ajouter nom ?
    if (compte->id_client2 != -1) {
        printf("%d %d\n", compte->id_client1, compte->id_client2);
    } else {
        printf("%d\n", compte->id_client1);
    }    
}

void
afficherVirements(Compte compte, Virement LCvir) {
    Virement etude;
    etude = malloc(sizeof(Virement));
    etude = LCvir;
    while(etude != NULL){
        if (getIdCompteFrom(etude) == getIdCompte(compte) || getIdCompteTo(etude) == getIdCompte(compte)){
            double montant = getMontantVir(etude);
            if(getIdCompteFrom(etude) == getIdCompte(compte)) montant = montant*(-1);
            printf("From : %d, To : %d, Montant : %lf\n", getIdCompteFrom(etude), getIdCompteTo(etude), montant);
        }
        etude = getNextVir(etude);
    }    
}

void
addLCCompte(Compte * LCCompte, Compte compte) {
    if (*LCCompte == NULL) {
        *LCCompte = malloc(sizeof(Compte));
        *LCCompte = compte;
    } else {
        Compte etude = malloc(sizeof(Compte));
        etude = *LCCompte;
        while(etude->compte_suivant != NULL){
            etude = etude->compte_suivant;
        }
        etude->compte_suivant = compte;
    }    
}

Compte
findCompte(int id, Compte LCCompte) {
    Compte etude = malloc(sizeof(Compte));
    etude = LCCompte;
    while(etude != NULL && getIdCompte(etude) != id){
        etude = etude->compte_suivant;
    }
    return etude;
}

void
setIdCompte(Compte compte, int id) {
    compte->id_compte = id;
}

void
setMontant(Compte compte, double montant) {
    compte->montant = montant;
}

void
setClient1(int id_client1, Compte compte) {
    compte->id_client1 = id_client1;
}

void
setClient2(int id_client2, Compte compte) {
    compte->id_client2 = id_client2;
}

void
setLock(Compte compte, char locker) {
    compte->locker = locker;
}

void
setType(Compte compte, char type) {
    compte->type = type;
}

void
setSuivCNull(Compte compte) {
    compte->compte_suivant = NULL;
}

char
getLock(Compte compte) {
    return compte->locker;
}

double
getMontant(Compte compte) {
    return compte->montant;
}

char
getType(Compte compte) {
    return compte->type;
}

int
getIdCompte(Compte compte) {
    return compte->id_compte;
}
int
getIdClient1(Compte compte) {
    return compte->id_client1;
}

int
getIdClient2(Compte compte) {
    return compte->id_client2;
}

Compte
getNextCompte(Compte compte) {
    return compte->compte_suivant;
}