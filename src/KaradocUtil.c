#include "../include/KaradocUtil.h"

void authentification()
{
    FILE *file, *f;
    char mdp[100];
    printf("mdp : ");
    scanf("%s", &mdp);
    file = fopen("../mot_de_passe.txt", "w");
    
    char commande[40];
    sprintf(commande, "echo %s | md5sum", mdp);
    f   = popen (commande, "r") ;
	char hache[32];
	fgets(hache, 32, f);
	fprintf(file, "%s\n", hache);
    pclose(f);
    fclose(file);

    printf("vérification mdp : ");
    scanf("%s", &mdp);

    sprintf(commande, "echo %s | md5sum", mdp);
    f = popen (commande, "r") ;
	fgets(hache, 32, f);
	pclose(f);
    
    char chaine[32];
    file = fopen("../mot_de_passe.txt", "r");
    if(strcmp(hache, fgets(chaine, 32, file))){
        printf("erreurs identifiants incorrects\n");
    }else{
        printf("authentification réussie\n");
    }
    fclose(file);
}