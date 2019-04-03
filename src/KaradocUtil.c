#include "../include/KaradocUtil.h"

//TODO : REMPLASSER TODO DANS LES SWITCHS PAR DES FONCTIONS (de TitulaireCompte.c ?)

void initialisation(Compte LCCompte, Client LCClient, Virement LCVirement)
{
    LCClient = LCinitClient();
    LCCompte = LCinitCompte();
    LCVirement = LCinitVirement();
}

Client lecture_fichier_json_client(int id, Client client)
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
    return client;
}

Compte lecture_fichier_json_compte(int id, Compte compte)
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
    return compte;
}

Virement lecture_fichier_json_virement(int id, Virement virement)
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
    return virement;
}

void creer_fichier_json_client(int id_client, char *nom, char *prenom, int numero_tel, char *mdp)
{
    FILE *fichier;
    char nom_fichier[100] = "";
    char id[12];
    sprintf(id, "%d", id_client);
    strcat(nom_fichier, "../data/Clients/");
    strcat(nom_fichier, id);
    strcat(nom_fichier, ".json");
    fichier = fopen(nom_fichier, "w");
    char num[12];
    sprintf(num, "%d", numero_tel);
    if (fichier != NULL)
    {
        fprintf(fichier, "{\n\t\"id_client\" : \"%s\",\n\t\"nom\" : \"%s\",\n\t\"prenom\" : \"%s\",\n\t\"numero_tel\" : \"%s\",\n\t\"mdp\" : \"%s\"\n}", id, nom, prenom, num, mdp);
        fclose(fichier);
    }
}

void creer_fichier_json_compte(int id_compte, char type, int id_client1, int id_client2, double montant, int locker)
{
    FILE *fichier;
    char nom_fichier[100] = "";
    char id[12];
    sprintf(id, "%d", id_compte);
    strcat(nom_fichier, "../data/Comptes/");
    strcat(nom_fichier, id);
    strcat(nom_fichier, ".json");
    fichier = fopen(nom_fichier, "w");
    char idc1[12];
    sprintf(idc1, "%d", id_client1);
    char idc2[12];
    sprintf(idc2, "%d", id_client2);
    char l[12];
    sprintf(l, "%d", locker);
    char m[12];
    sprintf(m, "%lf", montant);
    char t[2];
    t[0] = type;
    t[1] = '\0';
    if (fichier != NULL)
    {
        fprintf(fichier, "{\n\t\"id_compte\" : \"%s\",\n\t\"type\" : \"%s\",\n\t\"id_client1\" : \"%s\",\n\t\"id_client2\" : \"%s\",\n\t\"montant\" : \"%s\",\n\t\"locker\" : \"%s\"\n}", id, t, idc1, idc2, m, l);
        fclose(fichier);
    }
}

void creer_fichier_json_virement(int id_compteFrom, int id_compteTo, char *date, double montant)
{
    FILE *fichier;
    char nom_fichier[100] = "";
    char id[12];
    sprintf(id, "%d", id_compteFrom);
    strcat(nom_fichier, "../data/Virements/");
    strcat(nom_fichier, id);
    strcat(nom_fichier, ".json");
    fichier = fopen(nom_fichier, "w");
    char idc1[12];
    sprintf(idc1, "%d", id_compteTo);
    char m[12];
    sprintf(m, "%lf", montant);
    if (fichier != NULL)
    {
        fprintf(fichier, "{\n\t\"id_compteFrom\" : \"%s\",\n\t\"id_compteTo\" : \"%s\",\n\t\"date\" : \"%s\",\n\t\"montant\" : \"%s\"\n}", id, idc1, date, m);
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
        LCClient = cr_client(nom, prenom, numero_tel, mdp);
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

int menu_client_gestionComptes(Client client)
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