#include <stdlib.h>
#include <stdio.h>
#include "./struct.h"
#include "./noeud.h"
#include "./data.h"

void printNodeInfo(NoeudAVL *node)
{
    if (node == NULL)
    {
        return;
    }

    printf("ID: %d\n", node->id);
    printf("  Capacity: %lld kWh\n", node->capacite);
    printf("  Load: %lld kWh\n", node->charge);
    printf("  Equilibre: %d\n", node->equilibre);
}

void printTree(NoeudAVL *root)
{
    if (root == NULL)
    {
        return;
    }

    // Parcours récursif in-order
    printNodeInfo(root);
    printTree(root->fg);
    printTree(root->fd);
}

int main(int argc, char *argv[])
{
    if (argc != 4)
    {
        printf("Les arguments donnés en entrée sont incorrects.");
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

    ecrireFichier(arbre, argv[2], argv[3]);
    // printTree(arbre);

    free(arbre);
    free(entrees);
    return EXIT_SUCCESS;
}