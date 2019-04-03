#ifndef TITULAIRECOMPTE_H
#define TITULAIRECOMPTE_H

//--------------INCLUDE--------------

#include <stdio.h>
#include <stdlib.h>

//--------------STRUCT--------------

typedef struct TitulaireCompte_s * Client;

//--------------METHODS--------------

Client cr_client(char nom[15], char prenom[15], int numero_tel, char mdp[32]);
Client LCinitClient();
    /*
    Retourne la liste chainée des clients
    */
void addLCClient(Client LCClient, Client client);
    /*
    Ajoute un client a une liste chainée de client
    */


//#SET
void setNom(Client client, char nom[15]);
void setPrenom(Client client, char prenom[15]);
void setNum(Client client, int num);
void setMdp(Client client, char mdp[32]);

//#GET
int getIdClient(Client client);
char * getNom(Client client);
char * getPrenom(Client client);
int getNum(Client client);
char * getMdp(Client client);


#endif