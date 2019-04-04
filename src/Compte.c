#include "../include/Compte.h"

struct Compte_s
{
    int id_compte;
    char type;
    int id_client1;
    int id_client2; //-1 si pas de deuxieme proprio
    double montant;
    char locker;
    Compte compte_suivant;
};

int
getIndexCompte(){
    //TODO théau
}

void
cr_compte(Compte LCcompte, int id_client1, int id_client2, char type) {
    Compte res;
    res = malloc(sizeof(Compte));
    res->id_compte = getIndexCompte();
    res->type = type; // a : livret a | c : courant | p : pel
    res->id_client1 = id_client1;
    res->id_client2 = id_client2;
    res->montant = 0;
    res->locker = 1;
    res->compte_suivant = NULL;
    creer_fichier_json_compte(res->id_compte, res->type, res->id_client1, res->id_client2, res->montant, res->locker);
    addLCCompte(LCcompte, res);
}

void
LCinitCompte(int index, Compte LCcompte) {
    Compte res;
    res = malloc(sizeof(Compte));
    //TODO theau : chercher le bon fichier puis remplir res par lecture du fichier
    addLCCompte(LCcompte, res);
}

void
toprintcompte(Compte compte) {
    //TODO: ajouter nom + saucisse   
    if (compte->type == 'c') {
        printf("%d C.COURANT %d %d %d\n",
        compte->id_compte,
        compte->id_client1,
        compte->id_client2,
        compte->montant);
    }
    if (compte->type == 'a') {
        printf("%d LIVRET A %d %d\n",
        compte->id_compte,
        compte->id_client1,
        compte->montant);
    }
    if (compte->type == 'p') {
        printf("%d PEL %d %d\n",
        compte->id_compte,
        compte->id_client1,
        compte->montant);
    }
}

void
afficherComptes(Compte LCcompte) {
    Compte etude = LCcompte;
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
    //TODO
    int jfrom, mfrom, afrom, jto, mto, ato;
    jfrom = from[0]*10 + from[1];
    mfrom = from[2]*10 + from[3];
    afrom = from[4]*1000 + from[5]*100 + from[6]*10 + from[7];
    jto = to[0]*10 + to[1];
    mto = to[2]*10 + to[3];
    ato = to[4]*1000 + to[5]*100 + to[6]*10 + to[7];
    FILE * fichierexport = NULL;
    fichierexport = fopen(???); /* todo theau : peux tu
        faire en sorte que le nom du fichier créé (dans data/export/) soit de la forme:
        "idcompte datefrom dateto.csv" stp et ouvert en écriture
    */
    fputs("From,To,Date,Value", fichierexport);
    Virement etude = LCvir;
    while(etude != NULL) {
        if (getIdCompteFrom(etude) == compte || getIdCompteTo(etude) == compte) {
            int jetude, metude, aetude;
            jetude = getDate(etude)[0]*10 + getDate(etude)[1];
            metude = getDate(etude)[2]*10 + getDate(etude)[3];
            aetude = getDate(etude)[4]*1000 + getDate(etude)[5]*100 + getDate(etude)[6]*10 + getDate(etude)[7];
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
            fprintf(fichierexport, "%d,%d,%d/%d/%d,%lf", 
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

void
supprimerCompte(Compte LCcompte, Compte compte) {
    //LE COMPTE DOIT EXISTER !!!
    //TODO théau : remove le json
    Compte etude = LCcompte;
    if (etude->compte_suivant == NULL) {
        LCcompte = NULL;
        free(etude);
        return;
    }
    while(etude->compte_suivant != compte){
        etude = etude->compte_suivant;
    }
    etude->compte_suivant = compte->compte_suivant;
    free(compte);
}

void
titulairesCompte(Compte compte) {
    //TODO: ajouter nom ?
    if (compte->id_client2 != NULL) {
        printf("%d %d\n", compte->id_client1, compte->id_client2);
    } else {
        printf("%d\n", compte->id_client1);
    }    
}

void
afficherVirements(Compte compte, Virement LCvir) {
    Virement etude = LCvir;
    while(etude != NULL){
        if (getIdCompteFrom(etude) == compte || getIdCompteTo(etude) == compte){
            //TODO afficher avec diff si from ou to
        }
    }    
}

void
addLCCompte(Compte LCCompte, Compte compte) {
    if (LCCompte == NULL) {
        LCCompte = compte;
    } else {
        Compte etude = LCCompte;
        while(etude->compte_suivant != NULL){
            etude = etude->compte_suivant;
        }
        etude->compte_suivant = compte;
    }    
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