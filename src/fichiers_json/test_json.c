#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void creer_fichier_json_client(int id_client, char *nom, char *prenom, int numero_tel, char *mdp)
{
    FILE *fichier;
    char nom_fichier[100] = "";
    char id[12];
    sprintf(id, "%d", id_client);
    strcat(nom_fichier, "clients/");
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
    strcat(nom_fichier, "comptes/");
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
    strcat(nom_fichier, "virements/");
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

int main(int argc, char *argv[])
{
    char date[8] = "10091999";
    creer_fichier_json_client(4, "Chevalier", "Lancelot", 698587435, "gpad1spi");
    creer_fichier_json_compte(4, 'p', 1, 2, 1000, 1);
    creer_fichier_json_virement(4, 2, date, 578); 
    return 0;
}