#ifndef KARADOCUTIL_H
#define KARADOCUTIL_H

//--------------INCLUDE--------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "type.h"
#include "Compte.h"
#include "TitulaireCompte.h"
#include "Virement.h"

//--------------METHODS--------------

void initialisation(Compte * LC_Compte, Client * LC_Client, Virement * LC_Virement);
    /*
    LCinitcompte + LCinitClient+ LCinitVirement
    Les 3 pointeurs en arguments deviennent les listes chainés
    */

char *getDate_today();

void lecture_fichier_json_client(int id, Client client);
    /*
    retourne les infos du client dont l'id est mise en paramètre
    */

void lecture_fichier_json_compte(int id, Compte compte);
    /*
    retourne les infos du compte dont l'id est mise en paramètre
    */

void lecture_fichier_json_virement(int id, Virement virement); //TODO : RESOUDRE PROBLEME ID VIREMENT
    /*
    retourne les infos du virement dont l'id est mise en paramètre
    */

void creer_fichier_json_client(Client client);
    /*
    crée un nouveau fichier client rempli avec les infos données en paramètres
    */

void creer_fichier_json_compte(Compte compte);
    /*
    crée un nouveau fichier compte rempli avec les infos données en paramètres
    */

void creer_fichier_json_virement(int id, int id_compteFrom, int id_compteTo, char *date, double montant);
    /*
    crée un nouveau fichier virement rempli avec les infos données en paramètres
    */

Client login(Client LCClient);
    /*
    demande id + demande mdp + hache le mdp 
    + vérifie corespondance dans la LCclient
    (si id -1 ---> session admin)
    puis retourne le client de la session courante
    retourne NULL si inconnu pour que le programme main boucle
    */

char * hachage_mdp(char * mdp);
    /*
    retourne la version md5 de l'entrée
    */

void menu_admin(Client LC_Client, Compte LC_Compte, Virement LC_Virement);
    /*
    affiche le menu des possibilités de l'admin
    + retourne son choix d'action
    */

void menu_client(Client client, Client LC_Client, Compte LC_Compte, Virement LC_Virement);
    /*
    affiche le menu des possibilités pour un client
    + retourne son choix d'action
    */

void menu_client_gestionComptes(Client client, Client LC_Client, Compte LC_Compte, Virement LC_Virement);

void menu_client_administration(Client client, Client LC_Client, Compte LC_Compte, Virement LC_Virement);

void menu_admin_gestionComptes(Client LC_Client, Compte LC_Compte, Virement LC_Virement);

void menu_admin_gestionClients(Client LC_Client, Compte LC_Compte, Virement LC_Virement);

void menu_admin_administration(Client LC_Client, Compte LC_Compte, Virement LC_Virement);

void menu_c(Client LC_Client, Compte LC_Compte, Virement LC_Virement);

#endif