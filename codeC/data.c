#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "./struct.h"

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

        DataCSV entree = {-1, -1, -1, -1, -1, -1, -1, -1};
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
                    entree.id_centrale = atoi(jeton);
                    break;
                case 1:
                    entree.id_hvb = atoi(jeton);
                    break;
                case 2:
                    entree.id_hva = atoi(jeton);
                    break;
                case 3:
                    entree.id_lv = atoi(jeton);
                    break;
                case 4:
                    entree.id_entreprise = atoi(jeton);
                    break;
                case 5:
                    entree.id_particulier = atoi(jeton);
                    break;
                case 6:
                    entree.capacite = atoll(jeton);
                    break;
                case 7:
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

// NoeudAVL buildtree()
// {
//     return 1;
// }

// capacité - consommattion