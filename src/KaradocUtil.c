#include "../include/KaradocUtil.h"

void initialisation(Compte * LCCompte, Client * LCClient, Virement * LCVirement)
{
    FILE *f;
	int i, i_compt, ind;
	char compt[100]; 
	char commande[100];
	sprintf(compt, "ls data/Clients | wc -l");
    f = popen (compt, "r") ;
    fgets(compt, 100, f);
    i_compt = atoi(compt);
    for(i = 0; i < i_compt-1; i++){
    	sprintf(commande, "ls data/Clients | tail -n%d | head -n1 | cut -f1 -d '.'", i_compt-i);
    	f = popen (commande, "r") ;
    	fgets(commande, 100, f);
    	ind = atoi(commande);
    	LCinitClient(ind, LCClient);
    }

	sprintf(compt, "ls data/Comptes | wc -l");
    f = popen (compt, "r") ;
    fgets(compt, 100, f);
    i_compt = atoi(compt);
    for(i = 0; i < i_compt-1; i++){
    	sprintf(commande, "ls data/Comptes | tail -n%d | head -n1 | cut -f1 -d '.'", i_compt-i);
    	f = popen (commande, "r") ;
    	fgets(commande, 100, f);
    	ind = atoi(commande);
    	LCinitCompte(ind, LCCompte);
    }

	sprintf(compt, "ls data/Virements | wc -l");
    f = popen (compt, "r") ;
    fgets(compt, 100, f);
    i_compt = atoi(compt);
    for(i = 0; i < i_compt-1; i++){
    	sprintf(commande, "ls data/Virements | tail -n%d | head -n1 | cut -f1 -d '.'", i_compt-i);
    	f = popen (commande, "r") ;
    	fgets(commande, 100, f);
    	ind = atoi(commande);
    	LCinitVirement(ind, LCVirement);
    }
}

void lecture_fichier_json_client(int id, Client client) //CHECK VOID
{
    FILE *f;
    char commande[100];
    int  i;
    for(i = 6; i >= 2; i--) {
        sprintf(commande, "cat data/Clients/%d.json | cut -f4 -d '\"' | tail -n%d", id, i);
        f = popen (commande, "r") ;
        fgets(commande, 32, f);
        switch(i) {
            case 6 :
            setId(client, atoi(commande));
            break;
            case 5 :
            setNom(client, commande);
            break;
            case 4 :
            setPrenom(client, commande);
            break;
            case 3 :
            setNum(client, atoi(commande));
            break;
            case 2 :
            setMdp(client, commande);
            break;
            default :
            printf("Client : Error reading %d.json\n", id);
        }
    }
}

void lecture_fichier_json_compte(int id, Compte compte) //CHECK
{
    FILE *f;
    char commande[100];
    char compt[100];
    int  i;
    for(i = 7; i >= 2; i--) {
        sprintf(commande, "cat data/Comptes/%d.json | cut -f4 -d '\"' | tail -n%d", id, i);
        f = popen (commande, "r") ;
        fgets(commande, 100, f);
        switch(i) {
            case 6 :
            setType(compte, commande[0]);
            break;
            case 5 :
            setClient1(atoi(commande), compte);
            break;
            case 4 :
            setClient2(atoi(commande), compte);
            break;
            case 3 :
            setMontant(compte, atof(commande));
            break;
            case 2 :
            setLock(compte, commande[0]);
            break;
            default :
            printf("Error reading %d.json\n", id);
        }
    }
}

void lecture_fichier_json_virement(int id, Virement virement) //CHECK
{
    FILE *f;
    char commande[100];
    char compt[100];
    int  i;
    for(i = 5; i >= 2; i--) {
        sprintf(commande, "cat data/Virements/%d.json | cut -f4 -d '\"' | tail -n%d", id, i);
        f = popen (commande, "r") ;
        fgets(commande, 100, f);
        printf("%s", commande);
    }
}

void creer_fichier_json_client(Client client)
{
    FILE *fichier;
    char nom_fichier[100] = "";
    sprintf(nom_fichier, "data/Clients/%d.json", getIdClient(client));
    fichier = fopen(nom_fichier, "w");
    if (fichier != NULL)
    {
        fprintf(fichier, "{\n\t\"id_client\" : \"%d\",\n\t\"nom\" : \"%s\",\n\t\"prenom\" : \"%s\",\n\t\"numero_tel\" : \"%d\",\n\t\"mdp\" : \"%s\"\n}", getIdClient(client), getNom(client), getPrenom(client), getNum(client), getMdp(client));
        fclose(fichier);
    }
}

void creer_fichier_json_compte(Compte compte)
{
    FILE *fichier;
    char nom_fichier[100] = "";
    sprintf(nom_fichier, "data/Comptes/%d.json", getIdCompte(compte));
    fichier = fopen(nom_fichier, "w");
    if (fichier != NULL)
    {
        fprintf(fichier, "{\n\t\"id_compte\" : \"%d\",\n\t\"type\" : \"%c\",\n\t\"id_client1\" : \"%d\",\n\t\"id_client2\" : \"%d\",\n\t\"montant\" : \"%lf\",\n\t\"locker\" : \"%c\"\n}", getIdCompte(compte), getType(compte), getIdClient1(compte), getIdClient2(compte), getMontant(compte), getLock(compte));
        fclose(fichier);
    }
}

void creer_fichier_json_virement(int id, int id_compteFrom, int id_compteTo, char *date, double montant)
{
    FILE *fichier;
    char nom_fichier[100] = "";
    sprintf(nom_fichier, "data/Virements/%d.json", id);
    fichier = fopen(nom_fichier, "w");
    if (fichier != NULL)
    {
        fprintf(fichier, "{\n\t\"id_compteFrom\" : \"%d\",\n\t\"id_compteTo\" : \"%d\",\n\t\"date\" : \"%s\",\n\t\"montant\" : \"%lf\"\n}", id_compteFrom, id_compteTo, date, montant);
        fclose(fichier);
    }
}

Client login(Client LCClient)
{
    int answer;
    printf("1/ Login\n2/ Nouveau Client ?\n3/ Quitter\n");
    scanf("%d", &answer);
    if(answer == 3) exit(EXIT_SUCCESS);
    int login;
    char nom[15];
    char prenom[15];
    int numero_tel;
    char *mdp;
    mdp = malloc(40*sizeof(char));
    if(answer == 1){
        printf("----LOGIN----\n");
        printf("login : ");
        scanf("%d", &login);
        printf("mot de passe : ");
        scanf("%s", mdp);
        mdp = hachage_mdp(mdp);
        if(getIdClient(findClient(login, LCClient)) != login || strcmp(mdp, getMdp(findClient(login, LCClient)))) return NULL;
    } else {
        printf("----NOUVEAU CLIENT----\n");
        printf("nom : ");
        scanf("%s", nom);
        printf("prenom : ");
        scanf("%s", prenom);
        printf("numero_tel : ");
        scanf("%d", &numero_tel);
        printf("mot de passe : ");
        scanf("%s", mdp);
        hachage_mdp(mdp);
        cr_client(LCClient, nom, prenom, numero_tel, mdp);
    }
    return LCClient;
}

//Prends en paramètre le mdp en clair et le crypte

char *hachage_mdp(char *mdp)
{
    FILE *f;    
    char commande[32];
    sprintf(commande, "echo %s | md5sum", mdp);
    f   = popen (commande, "r") ;
	char hache[32];
	fgets(hache, 32, f);
    pclose(f);
    mdp = hache;
    return mdp;
}

void menu_admin(Client LC_Client, Compte LC_Compte, Virement LC_Virement)
{
    int choix;
    printf("----MENU ADMINISTRATEUR----\n\n");
    printf("1/ Gestion des comptes\n");
    printf("2/ Gestion des clients\n");
    printf("3/ Administration\n");
    printf("4/ Quitter\n");
    scanf("%d", &choix);
    switch(choix) {
        case 1 :
            menu_admin_gestionComptes(LC_Client, LC_Compte, LC_Virement);
            break;
        case 2 :
            menu_admin_gestionClients(LC_Client, LC_Compte, LC_Virement);
            break;
        case 3 :
            menu_admin_administration(LC_Client, LC_Compte, LC_Virement);
            break;
        case 4 :
            exit(EXIT_SUCCESS);
            break;
        default :
            printf("error\n");
            break;
    }
}

void menu_client(Client client, Client LC_Client, Compte LC_Compte, Virement LC_Virement)
{
    int choix;
    printf("----MENU CLIENT----\n");
    printf("Que souhaitez vous faire %s %s ?", getNom(client), getPrenom(client));
    printf("1/ Gestion des comptes\n");
    printf("2/ Administration\n");
    printf("3/ Quitter\n");
    scanf("%d", &choix);
    switch(choix) {
        case 1 :
            menu_client_gestionComptes(client, LC_Client, LC_Compte, LC_Virement);
            break;
        case 2 :
            menu_client_administration(client, LC_Client, LC_Compte, LC_Virement);
            break;
        case 3 :
            exit(EXIT_SUCCESS);
            break;
        default :
            printf("error\n");
            break;
    }
}

void menu_client_gestionComptes(Client client, Client LC_Client, Compte LC_Compte, Virement LC_Virement)
{
    int choix;
    printf("client_actif : %s %s", getNom(client), getPrenom(client));
    printf("----Gestion des Comptes----\n");
    Compte etude = LC_Compte;
    while(etude != NULL){
        if (getIdClient1(etude) == getIdClient(client) || getIdClient2(etude) == getIdClient(client)) {
            if (getLock(etude) != 1) {
                toprintcompte(etude);
            }            
        }
        etude = getNextCompte(etude);
    }
    free(etude);
    printf("1/ liste des opérations\n");
    printf("2/ consulter virements\n");
    printf("3/ Faire un virement\n");
    printf("4/ Retour\n");
    scanf("%d", &choix);
    int compteActif;
    printf("Id du compte pour l'action : ");
    while(getIdClient1(findCompte(compteActif, LC_Compte)) != getIdClient(client) && getIdClient2(findCompte(compteActif, LC_Compte)) != getIdClient(client)){
        scanf("%d", &compteActif);
    }    
    switch(choix) {
        case 1 :
            //TODO choix des dates
            //exporterCompte(LC_Virement, findCompte(compteActif,LC_Compte),) /*TODO date*/);
            break;
        case 2 :
            afficherVirements(findCompte(compteActif, LC_Compte), LC_Virement);
            break;
        case 3 :
        {
            double montant = -1;
            int to;
            printf("Montant du virement : ");
            while(montant <=0 || montant > getMontant(findCompte(compteActif, LC_Compte))){
                scanf("%lf", & montant);
            }
            printf("id du compte cible :");
            scanf("%d", &to);
            setMontant(findCompte(compteActif,LC_Compte), getMontant(findCompte(compteActif, LC_Compte))-montant);
            setMontant(findCompte(to,LC_Compte), getMontant(findCompte(to, LC_Compte))+montant);
            creer_fichier_json_compte(findCompte(compteActif, LC_Compte));
            creer_fichier_json_compte(findCompte(to, LC_Compte));
            cr_virement(compteActif, to, montant);
            break;
        }
        case 4 :
            menu_client(client, LC_Client, LC_Compte, LC_Virement);
        default :
            printf("Error");
            break;
    }
}

void menu_client_administration(Client client, Client LC_Client, Compte LC_Compte, Virement LC_Virement)
{
    int choix;
    printf("client_actif : %s %s", getNom(client), getPrenom(client));
    printf("----Administration----\n");
    Compte etude = LC_Compte;
    while(etude != NULL){
        if (getIdClient1(etude) == getIdClient(client) || getIdClient2(etude) == getIdClient(client)) {
            if (getLock(etude) != 1) {
                toprintcompte(etude);
            }            
        }
        etude = getNextCompte(etude);
    }
    free(etude);
    printf("1/ creation compte\n");
    printf("2/ suppression compte\n");
    printf("3/ changer mot de passe\n");
    printf("4/ Retour\n");
    scanf("%d", &choix);
    switch(choix) {
        case 1 :
        {
            char choixtype;
            printf("'a' pour livret A, 'p' pour PEL, 'c' pour compte courant, type : ");
            while(choixtype != 'a' && choixtype != 'p' && choixtype != 'c'){
                scanf("%c", &choixtype);              
            }            
            if (choixtype != 'c') {
                cr_compte(LC_Compte, getIdClient(client), -1, choixtype);
            } else {
                int clientdeux;
                printf("Id du second propriétaire du compte (-1 pour aucun) : ");
                while(clientdeux == 0 || findClient(clientdeux, LC_Client) == NULL){
                    scanf("%d", &clientdeux);
                    if (clientdeux == -1) {
                        break;
                    }
                }
                cr_compte(LC_Compte, getIdClient(client), clientdeux, 'c');
            }            
            break;
        }
        case 2 :
        {
            int idcompteasuppr;
            printf("id du compte à supprimer : ");
            while(getIdClient1(findCompte(idcompteasuppr, LC_Compte)) != getIdClient(client) && getIdClient2(findCompte(idcompteasuppr, LC_Compte)) != getIdClient(client)){
                scanf("%d", &idcompteasuppr);
            }
            setLock(findCompte(idcompteasuppr, LC_Compte), 2);
            creer_fichier_json_compte(findCompte(idcompteasuppr, LC_Compte));
            break;
        }
        case 3 :
        {
            char *newmdp;
            newmdp = malloc(100*sizeof(char));
            printf("nouveau mot de passe : ");
            scanf("%s", newmdp);
            newmdp = hachage_mdp(newmdp);
            setMdp(client, newmdp);
            creer_fichier_json_client(client);
            break;
        }
        case 4 :
            menu_client(client, LC_Client, LC_Compte, LC_Virement);
        default :
            printf("Error");
            break;
    }
}

void menu_admin_gestionComptes(Client LC_Client, Compte LC_Compte, Virement LC_Virement)
{
    int choix;
    printf("admin\n");
    printf("----Gestion des comptes----\n");
    printf("1/ créer, modifier, supprimer compte\n");
    printf("2/ afficher liste des comptes\n");
    printf("3/ Retour\n");
    scanf("%d", &choix);
    switch(choix) {
        case 1 :
            menu_c(LC_Client, LC_Compte, LC_Virement);
            break;
        case 2 :
            afficherComptes(LC_Compte);
            break;
        case 3 :
            menu_admin(LC_Client, LC_Compte, LC_Virement);
        default :
            printf("Error");
            break;
    }
}

void menu_admin_gestionClients(Client LC_Client, Compte LC_Compte, Virement LC_Virement)
{
    int choix;
    printf("admin");
    printf("----Gestion des clients----\n");
    printf("1/ ajouter client\n");
    printf("2/ modifier coordonnées client\n");
    printf("3/ afficher liste titulaires du compte\n");
    printf("4/ Retour\n");
    scanf("%d", &choix);
    switch(choix) {
        case 1 :
        {
            char nom[15];
            printf("Nom : ");
            scanf("%s", nom);
            char prenom[15];
            printf("Prenom : ");
            scanf("%s", prenom);
            int num;
            printf("Num : ");
            scanf("%d", &num);
            char *mdp;
            mdp = malloc(100*sizeof(char));
            printf("nouveau mot de passe : ");
            scanf("%s", mdp);
            mdp = hachage_mdp(mdp);
            cr_client(LC_Client, nom, prenom, num, mdp);
            break;
        }
        case 2 :
        {
            int idclient;
            printf("id du client : ");
            scanf("%d", &idclient);
            int numero;
            printf("Numéro : ");
            scanf("%d", &numero);
            setNum(findClient(idclient, LC_Client), numero);
            creer_fichier_json_client(findClient(idclient, LC_Client));
            break;
        }
        case 3 :
        {
            int idcompte;
            printf("id du compte : ");
            scanf("%d", &idcompte);
            titulairesCompte(findCompte(idcompte, LC_Compte));
            break;
        }
        case 4 :
            menu_admin(LC_Client, LC_Compte, LC_Virement);
        default :
            printf("Error");
            break;
    }
}

void menu_admin_administration(Client LC_Client, Compte LC_Compte, Virement LC_Virement)
{
    int choix;
    printf("admin");
    printf("----Administration----\n");
    printf("1/ changer mot de passe\n");
    printf("2/ Retour\n");
    scanf("%d", &choix);
    switch(choix) {
        case 1 :
        {
            char *newmdp;
            newmdp = malloc(100*sizeof(char));
            printf("nouveau mot de passe : ");
            scanf("%s", newmdp);
            newmdp = hachage_mdp(newmdp);
            setMdp(findClient(0, LC_Client), newmdp);
            creer_fichier_json_client(findClient(0, LC_Client));
            break;
        }
        case 2 :
            menu_admin(LC_Client, LC_Compte, LC_Virement);
            break;
        default :
            printf("Error");
            break;
    }
}

void menu_c(Client LC_Client, Compte LC_Compte, Virement LC_Virement)
{
    int choix;
    printf("admin\n");
    printf("----Gestion des comptes----\n");
    printf("1/ créer\n");
    printf("2/ modifier\n");
    printf("3/ supprimer\n");
    printf("4/ Retour\n");
    scanf("%d", &choix);
    switch(choix) {
        case 1 :
            printf("Requetes de création de compte :\n");
            Compte etude = LC_Compte;
            while(etude != NULL){
                if (getLock(etude) == 1) {
                    toprintcompte(etude);
                    int ok;
                    printf("accepter la création (0 non 1 oui) : ");
                    scanf("%d", &ok);
                    if (ok == 1) {
                        setLock(etude, 0);
                        creer_fichier_json_compte(etude);
                    } else {
                        supprimerCompte(LC_Compte, etude);
                    }                  
                }
                etude = getNextCompte(etude);
            }
            int ok;
            printf("Créer un nouveau compte (0 non 1 oui) ");
            scanf("%d", &ok);
            if (ok == 1) {
                int id1, id2;
                char t;
                printf("id client 1 :");
                scanf("%d", &id1);
                printf("id client 2 (-1 si non existant) :");
                scanf("%d", &id2);
                printf("type (a, p, c) :");
                scanf("%c", &t);
                cr_compte(LC_Compte, id1, id2, t);
            }       
            break;
        case 2 :
        {
            int idc;
            double nm;
            printf("id du compte à midifier : ");
            scanf("%d", &idc);
            printf("nouveau montant : ");
            scanf("%lf", &nm);
            setMontant(findCompte(idc, LC_Compte), nm);
            creer_fichier_json_compte(findCompte(idc, LC_Compte));
            break;
        }
        case 3 :
            printf("Requetes de suppression de compte :\n");
            Compte etude2 = LC_Compte;
            while(etude2 != NULL){
                if (getLock(etude2) == 2) {
                    toprintcompte(etude2);
                    int ok;
                    printf("accepter la suppression (0 non 1 oui) : ");
                    scanf("%d", &ok);
                    if (ok == 1) {
                        supprimerCompte(LC_Compte, etude2);
                    } else {     
                        setLock(etude2, 0);
                        creer_fichier_json_compte(etude2);
                    }                  
                }
                etude2 = getNextCompte(etude2);
            }
            int ok2;
            printf("Supprimer un compte (0 non 1 oui) ");
            scanf("%d", &ok2);
            if (ok2 == 1) {
                int idc;
                printf("id du compte à supprimer : ");
                scanf("%d", &idc);
                supprimerCompte(LC_Compte, findCompte(idc, LC_Compte));
            }       
            break;
        case 4 :
            menu_admin_gestionComptes(LC_Client, LC_Compte, LC_Virement);
        default :
            printf("Error");
            break;
    }
}