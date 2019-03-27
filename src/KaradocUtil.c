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
            setType(commande);
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
            setLock(compte);
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
        while(LCClient->client_suivant != NULL && LCClient->id_client) {
            LCClient = LCClient->client_suivant;
        }
        if(getIdClient(LCClient) != login || mdp != getMdp(LCClient)) return NULL;
    } else {
        printf("----NOUVEAU CLIENT----");
        printf("login : ");
        scanf("%d", &login);
        printf("nom : ");
        scanf("%s", nom);
        printf("prenom : ");
        scanf("%s", prenom);
        printf("numero_tel : ");
        scanf("%s", &numero_tel);
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
    return NULL;
}

char menu_client()
{
    return NULL;
}

//POURRA peut etre SERVIR A L'AVENIR (compare 2 mdp crypté entre eux)
/*
printf("vérification mdp : ");
scanf("%s", &mdp);

sprintf(commande, "echo %s | md5sum", mdp);
f = popen (commande, "r") ;
fgets(hache, 32, f);
pclose(f);

char chaine[32];
file = fopen("../mot_de_passe.txt", "r");
if(strcmp(hache, fgets(chaine, 32, file))){
    printf("erreurs mots de passe différents\n");
}else{
    printf("authentification réussie\n");
}
fclose(file);
*/