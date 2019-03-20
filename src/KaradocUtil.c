#include "../include/KaradocUtil.h"

//TEST

/*

void login()
{
    printf("1/ Login\n2/ Nouveau Client ?\n");
    system("clear");
    int answer, login;
    char nom[15];
    char prenom[15];
    int numero_tel;
    char mdp[35];
    Client *client;
    scanf("%d", &answer);
    if(answer == 1){
        printf("----LOGIN----");
        printf("login : ");
        scanf("%d", &login);
        setIdClient(client, login);
        printf("mot de passe : ");
        scanf("%s", mdp);
        hachage_mdp(&mdp);
        setMdp(client, mdp);
        connexion(client);
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
        cr_client(nom, prenom, numero_tel, mdp);
    }
    
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
*/

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