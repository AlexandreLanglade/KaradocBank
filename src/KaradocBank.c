#include "../include/KaradocBank.h"

int main(int argv, char *argc)
{
    Client LC_Client = NULL;
    Compte LC_Compte = NULL;
    Virement LC_Virement = NULL;
    initialisation(&LC_Compte, &LC_Client, &LC_Virement);
    Client client_actif = NULL;
    while(client_actif == NULL) {
        client_actif = login(LC_Client);
    }
    if(getIdClient(client_actif) == 0){
        menu_admin(LC_Client, LC_Compte, LC_Virement);
    } else {
        menu_client(client_actif, LC_Client, LC_Compte, LC_Virement);
    }
	return EXIT_SUCCESS;
}