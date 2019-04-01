#include "../include/KaradocBank.h"

int main(int argv, char *argc)
{
    Client LC_Client;
    Compte LC_Compte;
    Virement LC_Virement;
    initialisation(LC_Compte, LC_Client, LC_Virement);
    Client client_actif = NULL;
    system("clear");
    while(client_actif == NULL) client_actif = login(client_actif);
    int choix;
    if(getIdClient(client_actif) == -1) choix = menuAdmin();
    else choix = menuClient(client_actif);
	return EXIT_SUCCESS;

}