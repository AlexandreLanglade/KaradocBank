#include "../include/KaradocUtil.h"

void initialisation(Compte LC_Compte, Client LC_Client, Virement LC_Virement)
{
    FILE *f;
    Client client;
    Compte compte;
    Virement virement;
    char commande[100];
    char compt[100];
    int  i, i_compt;
    sprintf(compt, "ls fichiers_json/clients | wc -l");
    f = popen (compt, "r") ;
    fgets(compt, 100, f);
    i_compt = atoi(compt);
    for(i = 1; i <= i_compt; i++){
        addLCClient(LC_Client, lecture_fichier_json_client(i, client));
    }
    sprintf(compt, "ls fichiers_json/comptes | wc -l");
    f = popen (compt, "r") ;
    fgets(compt, 100, f);
    i_compt = atoi(compt);
    for(i = 1; i <= i_compt; i++){
        addLCCompte(LC_Compte, lecture_fichier_json_compte(i, compte));
    }
    sprintf(compt, "ls fichiers_json/virements | wc -l");
    f = popen (compt, "r") ;
    fgets(compt, 100, f);
    i_compt = atoi(compt);
    for(i = 1; i <= i_compt; i++){
        addLCVirement(LC_Virement, lecture_fichier_json_client(i, virement));
    }
}

Client lecture_fichier_json_client(int id, Client client)
{
    FILE *f;
    char commande[100];
    char compt[100];
    int  i;
    for(i = 6; i >= 2; i--) {
        sprintf(commande, "cat fichiers_json/clients/%d.json | cut -f4 -d '\"' | tail -n%d", id, i);
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
        sprintf(commande, "cat fichiers_json/comptes/%d.json | cut -f4 -d '\"' | tail -n%d", id, i);
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
        sprintf(commande, "cat fichiers_json/virements/%d.json | cut -f4 -d '\"' | tail -n%d", id, i);
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
    strcat(nom_fichier, "fichiers_json/clients/");
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
    strcat(nom_fichier, "fichiers_json/comptes/");
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
    strcat(nom_fichier, "fichiers_json/virements/");
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
    printf("1/ Login\n2/ Nouveau Client ?\n");
    scanf("%d", &answer);
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
    FILE *file, *f;
    file = fopen("../mot_de_passe.txt", "w");
    
    char commande[40];
    sprintf(commande, "echo %s | md5sum", mdp);
    f   = popen (commande, "r") ;
	char hache[32];
	fgets(hache, 32, f);
	fprintf(file, "%s\n", hache);
    pclose(f);
    fclose(file);
    *mdp = hache;
}

char menu_admin()
{
    char choix;
    system("clear");
    printf("----MENU ADMINISTRATEUR----\n\n");
    printf("1/ Gestion des comptes\n");
    printf("2/ Gestion des clients\n");
    printf("3/ Administration\n");
    scanf("%c", &choix);
    return choix;
}

char menu_client(Client client)
{
    char choix;
    printf("----MENU CLIENT----\n");
    printf("Que souhaitez vous faire %s %s ?", getNom(client), getPrenom(client));
    printf("1/ Gestion des comptes\n");
    printf("2/ Administration\n");
    scanf("%c", &choix);
    return choix;
}