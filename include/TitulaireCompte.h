#ifndef TITULAIRECOMPTE_H
#define TITULAIRECOMPTE_H

//--------------INCLUDE--------------

#include <stdio.h>
#include <stdlib.h>
#include "type.h"
#include "KaradocUtil.h"

//--------------METHODS--------------


int getIndexClient();
void cr_client(Client LCclient, char nom[15], char prenom[15], int numero_tel, char mdp[32]);
void LCinitClient(int index, Client * LCclient);
    /*
    Retourne la liste chainée des clients
    */
void addLCClient(Client * LCClient, Client client);
    /*
    Ajoute un client a une liste chainée de client
    */

Client findClient(int id, Client LCClient);

//#SET
void setId(Client client, int id);
void setNom(Client client, char nom[15]);
void setPrenom(Client client, char prenom[15]);
void setNum(Client client, int num);
void setMdp(Client client, char mdp[32]);
void setSuivClNull(Client client);

//#GET
int getIdClient(Client client);
char * getNom(Client client);
char * getPrenom(Client client);
int getNum(Client client);
char * getMdp(Client client);


#endif