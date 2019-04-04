#include "../include/KaradocUtil.h"

//TODO : REMPLASSER TODO DANS LES SWITCHS PAR DES FONCTIONS (de TitulaireCompte.c ?)

void initialisation(Compte LCCompte, Client LCClient, Virement LCVirement)
{
    FILE *f;
	int i, i_compt, ind;
	char compt[100]; 
	char commande[100];
	sprintf(compt, "ls ../data/Clients | wc -l");
    f = popen (compt, "r") ;
    fgets(compt, 100, f);
    i_compt = atoi(compt);
    for(i = 0; i < i_compt-1; i++){
    	sprintf(commande, "ls ../data/Clients | tail -n%d | head -n1 | cut -f1 -d '.'", i_compt-i);
    	f = popen (commande, "r") ;
    	fgets(commande, 100, f);
    	ind = atoi(commande);
    	LCinitClient(ind, LCClient);
    }

    FILE *f;
	int i, i_compt, ind;
	char compt[100]; 
	char commande[100];
	sprintf(compt, "ls ../data/Comptes | wc -l");
    f = popen (compt, "r") ;
    fgets(compt, 100, f);
    i_compt = atoi(compt);
    for(i = 0; i < i_compt-1; i++){
    	sprintf(commande, "ls ../data/Comptes | tail -n%d | head -n1 | cut -f1 -d '.'", i_compt-i);
    	f = popen (commande, "r") ;
    	fgets(commande, 100, f);
    	ind = atoi(commande);
    	LCinitCompte(ind, LCCompte);
    }

    FILE *f;
	int i, i_compt, ind;
	char compt[100]; 
	char commande[100];
	sprintf(compt, "ls ../data/Virements | wc -l");
    f = popen (compt, "r") ;
    fgets(compt, 100, f);
    i_compt = atoi(compt);
    for(i = 0; i < i_compt-1; i++){
    	sprintf(commande, "ls ../data/Virements | tail -n%d | head -n1 | cut -f1 -d '.'", i_compt-i);
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
    char compt[100];
    int  i;
    for(i = 6; i >= 2; i--) {
        sprintf(commande, "cat ../data/Clients/%d.json | cut -f4 -d '\"' | tail -n%d", id, i);
        f = popen (commande, "r") ;
        fgets(commande, 100, f);
        switch(i) {
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
            printf("Error reading %d.json", id);
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
        sprintf(commande, "cat ../data/Comptes/%d.json | cut -f4 -d '\"' | tail -n%d", id, i);
        f = popen (commande, "r") ;
        fgets(commande, 100, f);
        switch(i) {
            case 6 :
            setType(compte, commande);
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
            setLock(compte, commande);
            break;
            default :
            printf("Error reading %d.json", id);
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
        sprintf(commande, "cat ../data/Virements/%d.json | cut -f4 -d '\"' | tail -n%d", id, i);
        f = popen (commande, "r") ;
        fgets(commande, 100, f);
        printf("%s", commande);
    }
}

void creer_fichier_json_client(int id_client, char *nom, char *prenom, int numero_tel, char *mdp)
{
    FILE *fichier;
    char nom_fichier[100] = "";
    sprintf(nom_fichier, "../data/Clients/%d.json", id_client);
    fichier = fopen(nom_fichier, "w");
    if (fichier != NULL)
    {
        fprintf(fichier, "{\n\t\"id_client\" : \"%d\",\n\t\"nom\" : \"%s\",\n\t\"prenom\" : \"%s\",\n\t\"numero_tel\" : \"%d\",\n\t\"mdp\" : \"%s\"\n}", id_client, nom, prenom, numero_tel, mdp);
        fclose(fichier);
    }
}

void creer_fichier_json_compte(int id_compte, char type, int id_client1, int id_client2, double montant, char locker)
{
    FILE *fichier;
    char nom_fichier[100] = "";
    sprintf(nom_fichier, "./data/Comptes/%d.json", id_compte);
    fichier = fopen(nom_fichier, "w");
    if (fichier != NULL)
    {
        fprintf(fichier, "{\n\t\"id_compte\" : \"%d\",\n\t\"type\" : \"%c\",\n\t\"id_client1\" : \"%d\",\n\t\"id_client2\" : \"%d\",\n\t\"montant\" : \"%lf\",\n\t\"locker\" : \"%c\"\n}", id_compte, type, id_client1, id_client2, montant, locker);
        fclose(fichier);
    }
}

void creer_fichier_json_virement(int id, int id_compteFrom, int id_compteTo, char *date, double montant)
{
    FILE *fichier;
    char nom_fichier[100] = "";
    sprintf(nom_fichier, "../data/Virements/%d.json", id);
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
    system("clear");
    int login;
    char nom[15];
    char prenom[15];
    int numero_tel;
    char mdp[35];
    if(answer == 1){
        printf("----LOGIN----");
        printf("login : ");
        scanf("%d", &login);
        printf("mot de passe : ");
        scanf("%s", mdp);
        hachage_mdp(&mdp);
        while(getClientSuivant(LCClient) != NULL && getIdClient(LCClient) != login) {
            LCClient = getClientSuivant(LCClient);
        }
        if(getIdClient(LCClient) != login || strcmp(mdp, getMdp(LCClient))) return NULL;
    } else {
        printf("----NOUVEAU CLIENT----");
        printf("login : ");
        scanf("%d", &login);
        printf("nom : ");
        scanf("%s", nom);
        printf("prenom : ");
        scanf("%s", prenom);
        printf("numero_tel : ");
        scanf("%d", &numero_tel);
        printf("mot de passe : ");
        scanf("%s", mdp);
        hachage_mdp(&mdp);
        cr_client(LCClient, nom, prenom, numero_tel, mdp);
    }
    return LCClient;
}

//Prends en paramètre le mdp en clair et le crypte

void hachage_mdp(char *mdp)
{
    FILE *f;    
    char commande[40];
    sprintf(commande, "echo %s | md5sum", mdp);
    f   = popen (commande, "r") ;
	char hache[32];
	fgets(hache, 32, f);
    pclose(f);
    *mdp = hache;
}

void menu_admin()
{
    int choix;
    system("clear");
    printf("----MENU ADMINISTRATEUR----\n\n");
    printf("1/ Gestion des comptes\n");
    printf("2/ Gestion des clients\n");
    printf("3/ Administration\n");
    printf("4/ Quitter\n");
    scanf("%d", &choix);
    switch(choix) {
        case 1 :
        menu_admin_gestionComptes();
        break;
        case 2 :
        menu_admin_gestionClients();
        break;
        case 3 :
        menu_admin_administration();
        break;
        case 4 :
        exit(EXIT_SUCCESS);
        break;
        default :
        printf("error\n");
        break;
    }
}

void menu_client(Client client)
{
    int choix;
    system("clear");
    printf("----MENU CLIENT----\n");
    printf("Que souhaitez vous faire %s %s ?", getNom(client), getPrenom(client));
    printf("1/ Gestion des comptes\n");
    printf("2/ Administration\n");
    printf("3/ Quitter\n");
    scanf("%d", &choix);
    switch(choix) {
        case 1 :
        menu_client_gestionComptes(client);
        break;
        case 2 :
        menu_client_administration(client);
        break;
        case 3 :
        exit(EXIT_SUCCESS);
        break;
        default :
        printf("error\n");
        break;
    }
}

void menu_client_gestionComptes(Client client)
{
    system("clear");
    int choix;
    printf("client_actif : %s %s", getNom(client), getPrenom(client));
    printf("----Gestion des Comptes----\n");
    printf("1/ solde\n");
    printf("2/ liste des opérations\n");
    printf("3/ consulter virements\n");
    printf("4/ Retour\n");
    scanf("%d", &choix);
    switch(choix) {
        case 1 :
        //TODO Consulter solde
        break;
        case 2 :
        //TODO liste des opérations
        break;
        case 3 :
        //TODO consulter virements
        break;
        case 4 :
        menu_client(client);
        default :
        printf("Error");
        break;
    }
    return choix;
}

void menu_client_administration(Client client)
{
    system("clear");
    int choix;
    printf("client_actif : %s %s", getNom(client), getPrenom(client));
    printf("----Administration----\n");
    printf("1/ creation compte\n");
    printf("2/ suppression compte\n");
    printf("3/ changer mot de passe\n");
    printf("4/ Retour\n");
    scanf("%d", &choix);
    switch(choix) {
        case 1 :
        //TODO CREER FONCTION
        break;
        case 2 :
        //TODO CREER FONCTION
        break;
        case 3 :
        //TODO CREER FONCTION
        break;
        case 4 :
        menu_client(client);
        default :
        printf("Error");
        break;
    }
}

void menu_admin_gestionComptes()
{
    int choix;
    system("clear");
    printf("admin\n");
    printf("----Gestion des comptes----\n");
    printf("1/ créer, modifier, supprimer compte\n");
    printf("2/ afficher liste des comptes\n");
    printf("3/ Retour\n");
    scanf("%d", &choix);
    switch(choix) {
        case 1 :
        //TODO
        break;
        case 2 :
        //TODO
        break;
        case 3 :
        menu_admin();
        default :
        printf("Error");
        break;
    }
}

void menu_admin_gestionClients()
{
    int choix;
    system("clear");
    printf("admin");
    printf("----Gestion des clients----\n");
    printf("1/ ajouter client\n");
    printf("2/ modifier coordonnées client\n");
    printf("3/ afficher liste titulaires du compte\n");
    printf("4/ Retour\n");
    scanf("%d", &choix);
    switch(choix) {
        case 1 :
        //TODO
        break;
        case 2 :
        //TODO
        break;
        case 3 :
        //TODO
        break;
        case 4 :
        menu_admin();
        default :
        printf("Error");
        break;
    }
}

void menu_admin_administration()
{
    int choix;
    system("clear");
    printf("admin");
    printf("----Administration----\n");
    printf("1/ changer mot de passe\n");
    printf("2/ Retour\n");
    scanf("%d", &choix);
    switch(choix) {
        case 1 :
        //TODO
        break;
        case 2 :
        menu_admin();
        default :
        printf("Error");
        break;
    }
}