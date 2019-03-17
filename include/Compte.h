#ifndef COMPTE_H
#define COMPTE_H

typedef struct Compte_s * Compte;

Compte cr_compte(int id_client1, int id_client2, char type);
void setMontant(Compte compte, double montant);
double getMontant(Compte compte);
char getType(Compte compte);
void setClient1(int id_client1, Compte compte);
void setClient2(int id_client2, Compte compte);
int getIdCompte(Compte compte);
int getIdClient1(Compte compte);
int getIdClient2(Compte compte);
void afficherCompte(Compte compte);
void exporterCompte(Compte compte);
void supprimerCompte(Compte compte);
void titulairesCompte(Compte compte);
void afficherVirements(Compte compte);

#endif