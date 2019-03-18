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
