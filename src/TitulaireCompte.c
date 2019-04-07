#include "../include/TitulaireCompte.h"

struct TitulaireCompte_s
{
    int id_client;
    char nom[15];
    char prenom[15];
    int numero_tel;
    char mdp[35];
    Client client_suivant;
};

//TODO VarGlobSize

int
getIndexClient(){
    FILE *file;
	file = fopen("data/Clients/index.txt", "r");
	int index;
    if(file != NULL){
        fscanf(file, "%d\n", &index);
    }
    else{printf("ERROR READING FILE INDEX.TXT\n");}
    printf("%d", index);
    fclose(file);
	return index;
}

void incrementerIndexClient(int index)
{
    FILE *file;
    file = fopen("data/Client/index.txt", "w");
    index++;
    if(file != NULL) fprintf(file, "%d", index);
    fclose(file);
}


void
cr_client(Client LCclient, char nom[15], char prenom[15], int numero_tel, char mdp[32]) {
    int i;
    Client res;
    res = malloc(sizeof(Client));
    res->id_client = getIndexClient();
    printf("YES !  \n");
    for(i = 0; i < 15; i++) {
        res->nom[i] = nom[i];
    }
    for(i = 0; i < 15; i++) {
        res->prenom[i] = prenom[i];
    }
    for(i = 0; i < 15; i++) {
        res->mdp[i] = mdp[i];
    }    
    res->numero_tel = numero_tel;
    res->client_suivant = NULL;
    creer_fichier_json_client(res);
    addLCClient(&LCclient, res);
}

void
LCinitClient(int index, Client * LCclient){
    Client res;
    res = malloc(sizeof(Client));
    lecture_fichier_json_client(index, res);
    addLCClient(LCclient, res);
}

void
addLCClient(Client * LCClient, Client client){
    if (*LCClient == NULL) {
        *LCClient = malloc(sizeof(Client));
        *LCClient = client;
    } else {
        Client etude = *LCClient;
        while(etude->client_suivant != NULL){
            etude = etude->client_suivant;
        }
        etude->client_suivant = client;
    }
}


Client
findClient(int id, Client LCClient) {
    Client etude = malloc(sizeof(Client));
    etude = LCClient;
    while(etude != NULL && getIdClient(etude) != id){
        etude = etude->client_suivant;
    }
    return etude;
}

void
setId(Client client, int id)
{
    client->id_client = id;
}

void
setNom(Client client, char nom[15]){
    int i;
    for(i = 0; i < 15; i++)
    {
        client->nom[i] = nom[i];
    }    
}

void
setPrenom(Client client, char prenom[15]){
    int i;
    for(i = 0; i < 15; i++)
    {
        client->prenom[i] = prenom[i];
    } 
}

void
setNum(Client client, int num){
    client->numero_tel = num;
}

void
setMdp(Client client, char mdp[32]){
    int i;
    for(i = 0; i < 32; i++)
    {
        client->mdp[i] = mdp[i];
    } 
}

void
setSuivClNull(Client client) {
    client->client_suivant = NULL;
}

int
getIdClient(Client client){
    return client->id_client;
}

char *
getNom(Client client){
    return client->nom;
}

char *
getPrenom(Client client){
    return client->prenom;
}

int
getNum(Client client){
    return client->numero_tel;
}

char *
getMdp(Client client){
    return client->mdp;
}