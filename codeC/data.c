#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "./struct.h"
#include "./data.h"

DataCSV *parserLigneCSV(const char *chemin, int *nb_entrees)
{
    FILE *fichier = fopen(chemin, "r");
    if (fichier == NULL)
    {
        printf("erreur d'ouverture du fichier");
        exit(EXIT_FAILURE);
    }
    char ligne[100];
    int compteur = 0;

    if (fgets(ligne, sizeof(ligne), fichier) == NULL)
    {
        printf("erreur de lecture de la première ligne du fichier");
        exit(EXIT_FAILURE);
    }

    DataCSV *entrees = NULL;

    while (fgets(ligne, sizeof(ligne), fichier) != NULL)
    {
        DataCSV *nouvelles_entrées = realloc(entrees, (compteur + 1) * sizeof(DataCSV));
        if (nouvelles_entrées == NULL)
        {
            printf("erreur de réallocation du DataCSV");
            exit(EXIT_FAILURE);
        }
        entrees = nouvelles_entrées;

        DataCSV entree = {-1, 0, 0};
        ligne[strcspn(ligne, "\n")] = "\0";
        char *jeton = strtok(ligne, ";");
        int colonne = 0;
        while (jeton != NULL)
        {
            if (strcmp(jeton, "-") != 0)
            {
                switch (colonne)
                {
                case 0:
                    entree.id_station = atoi(jeton);
                    break;
                case 1:
                    entree.capacite = atoll(jeton);
                    break;
                case 2:
                    entree.charge = atoll(jeton);
                    break;
                default:
                    break;
                }
            }
            colonne++;
            jeton = strtok(NULL, ";");
        }
        entrees[compteur++] = entree;
    }
    *nb_entrees = compteur;
    return entrees;
}

void ecrireFichier(NoeudAVL *arbre, char *station, char *consommateur, char *id_centrale)
{
    char nom_fichier[50];
    if (strcmp(id_centrale, "") == 0)
        sprintf(nom_fichier, "./tests/%s_%s.csv", station, consommateur);
    else
        sprintf(nom_fichier, "./tests/%s_%s_%s.csv", station, consommateur, id_centrale);

    FILE *file = fopen(nom_fichier, "w");

    fprintf(file, "Station %s:Capacité:Consommation %s\n", station, consommateur);
    remplirFichier(file, arbre);

    fclose(file);
}

void remplirFichier(FILE *file, NoeudAVL *arbre)
{
    if (arbre != NULL)
    {
        fprintf(file, "%d:%lld:%lld\n", arbre->id, arbre->capacite, arbre->charge);
        remplirFichier(file, arbre->fg);
        remplirFichier(file, arbre->fd);
    }
}