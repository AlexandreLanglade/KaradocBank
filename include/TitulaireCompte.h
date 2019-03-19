#ifndef TITULAIRECOMPTE_H
#define TITULAIRECOMPTE_H

//--------------INCLUDE--------------


//--------------STRUCT--------------

typedef struct TitulaireCompte_s * Client;

//--------------METHODS--------------

Client cr_client(char nom[15], char prenom[15], int numero_tel, char mdp[32]);
void supprimerClient(Client client);
Client LCinitClient();
    /*
    Retourne la liste chainée des clients
    */
void addLCClient(Client LCClient, Client client);
    /*
    Ajoute un client a une liste chainée de client
    */


void setNom(Client client, char nom[15]);
void setPrenom(Client client, char prenom[15]);
void setNum(Client client, int num);
void setMdp(Client client, char mdp[32]);

int getIdClient(Client client);
char * getNom(Client client);
char * getPrenom(Client client);
int getNum(Client client);
char * getMdp(Client client);


#endif