#include "../include/Compte.h"

struct Compte_s
{
    int id_compte;
    char type;
    int id_client1;
    int id_client2;
    double montant;
    char locker;
    Compte compte_suivant;
};

//TODO 2 fonctions
Compte
cr_compte(int id_client1, int id_client2, char type) {
    Compte res;
    res = malloc(sizeof(Compte));
    //TODO: int id_compte + incrementer index
    res->type = type; // a : livret a | c : courant | p : pel
    res->id_client1 = id_client1;
    res->id_client2 = id_client2;
    res->montant = 0;
    res->locker = 1;
    res->compte_suivant = NULL;
    //Enregistrer nouveau json
    return res;
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
exporterCompte(Compte compte, char from[8], char to[8]) {
    //TODO
}

void
supprimerCompte(Compte LCcompte, Compte compte) {
    //LE COMPTE DOIT EXISTER !!!
    //TODO : remove le json
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

Compte
LCinitCompte() {
    //TODO
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