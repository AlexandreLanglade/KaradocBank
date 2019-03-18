#include <stdio.h>
#include <stdlib.h>
#include "../include/KaradocBank.h"

//lecture du jason

int main(int argv, char *argc)
{
    int id;
    char mdp[32];
    printf("id : ");
    scanf("%d", &id);
    printf("%d\n", id);
    printf("mdp : ");
    scanf("%s", &mdp);
    printf("%s\n", mdp);

    FILE * f = popen("date | md5sum", "r");

	char pwd[512] = {0};
	fgets(pwd, 512, f);
	printf("Current folder is %s\n", pwd);

	pclose(f);
	return EXIT_SUCCESS;

    //if id = id_client
}