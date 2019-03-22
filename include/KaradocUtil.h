#ifndef KARADOCUTIL_H
#define KARADOCUTIL_H

//--------------INCLUDE--------------

#include <stdio.h>
#include <stdlib.h>
#include "TitulaireCompte.h"
#include "Compte.h"
#include "TitulaireCompte.h"
#include "Virement.h"

//--------------METHODS--------------

void initialisation(Compte LC_Compte, Client LC_Client, Virement LC_Virement);
    /*
    LCinitcompte + LCinitClient+ LCinitVirement
    Les 3 pointeurs en arguments deviennent les listes chainés
    */

Client login(Client LCClient);
    /*
    demande id + demande mdp + hache le mdp 
    + vérifie corespondance dans la LCclient
    (si id -1 ---> session admin)
    puis retourne le client de la session courante
    retourne NULL si inconnu pour que le programme main boucle
    */

void hachage_mdp(char * mdp);
    /*
    retourne la version md5 de l'entrée
    */

char menuAdmin();
    /*
    affiche le menu des possibilités de l'admin
    + retourne son choix d'action
    */

char menuClient();
    /*
    affiche le menu des possibilités pour un client
    + retourne son choix d'action
    */

#endif