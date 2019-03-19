#ifndef TITULAIRECOMPTE_H
#define TITULAIRECOMPTE_H

typedef struct TitulaireCompte_s * Client;

Client cr_client(char nom[15], char prenom[15], int numero_tel, char mdp[32]);
int getIdClient(Client client);
char * getNom(Client client);
char * getPrenom(Client client);
int getNum(Client client);
void setIdClient(Client client, int id_client); //Sinon je vois pas comment faire l'authetification
void setNom(Client client, char nom[15]);
void setPrenom(Client client, char prenom[15]);
void setNum(Client client, int num);
void setMdp(Client client, char mdp[32]);
void supprimerClient(Client client);
Client connexion(Client client);

#endif