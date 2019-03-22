#ifndef COMPTE_H
#define COMPTE_H

//--------------INCLUDE--------------


//--------------STRUCT--------------

typedef struct Compte_s * Compte;

//--------------METHODS--------------

Compte cr_compte(int id_client1, int id_client2, char type);
void afficherComptes(Compte compte);
    /*
    Affiche la liste des comptes par type(pour l'admin)
    */
void exporterCompte(Compte compte, char from[8], char to[8]);
    /*
    exporter liste des opérations sur une période choisie
    dans le format CSV
    */
void supprimerCompte(Compte compte);
void titulairesCompte(Compte compte);
    /*
    Affiche les titulaires du compte
    */
void afficherVirements(Compte compte);
    /*
    Affiche la liste des virements du compte
    */
Compte LCinitCompte();
    /*
    Retourne la liste chainée des comptes
    */
void addLCCompte(Compte LCCompte, Compte compte);
    /*
    Ajoute un compte a une liste chainée de comptes
    */

//#SET
void setMontant(Compte compte, double montant);
void setClient1(int id_client1, Compte compte);
void setClient2(int id_client2, Compte compte);
void setLock(Compte compte);
void setType(char type);

//#GET
void getLock(Compte compte);
double getMontant(Compte compte);
char getType(Compte compte);
int getIdCompte(Compte compte);
int getIdClient1(Compte compte);
int getIdClient2(Compte compte);


#endif