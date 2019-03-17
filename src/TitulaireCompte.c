#include "../include/TitulaireCompte.h"

struct TitulaireCompte_s
{
    int id_client;
    char nom[15];
    char prenom[15];
    int numero_tel;
    char mdp[32];
    Client client_suivant;
};
