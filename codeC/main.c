#include <stdlib.h>
#include <stdio.h>
#include "./struct.h"
#include "./noeud.h"
#include "./data.h"

int main(int argc, char *argv[])
{
    if (argc < 4)
    {
        printf("Les arguments donnés en entrée sont incorrects.\n");
        return EXIT_FAILURE;
    }
    int nb_entrees = 0;

    DataCSV *entrees = parserLigneCSV(argv[1], &nb_entrees);
    // for (int i = 0; i < nb_entrees; i++)
    // {
    //     DataCSV entry = entrees[i];
    //     printf("Entry %d:\n id station %d, Capacité: %ld, charge: %ld\n",
    //            i + 1, entry.id_station, entry.capacite, entry.charge);
    //     printf("\n");
    // }

    NoeudAVL *arbre = creerArbre(entrees, nb_entrees);
    if (argc == 5)
        ecrireFichier(arbre, argv[2], argv[3], argv[4]);
    else
        ecrireFichier(arbre, argv[2], argv[3], "");

    free(arbre);
    free(entrees);
    return EXIT_SUCCESS;
}