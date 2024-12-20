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
    printf("  ID parent: %d\n", node->id_parent);
    printf("  Station Type: %s\n",
           node->type_station == HVB ? "HV-B" : node->type_station == HVA       ? "HV-A"
                                            : node->type_station == POWER_PLANT ? "POWER_PLANT"
                                                                                : "LV");
    printf("  consommateur: %s\n",
           node->consommateur == ENTREPRISE ? "ENTREPRISE" : node->consommateur == PARTICULIER ? "PARTICULIER"
                                                                                               : "None");
    printf("  Is Root: %s\n", node->est_racine ? "Yes" : "No");
    printf("  Capacity: %lld kWh\n", node->capacite);
    printf("  Load: %lld kWh\n", node->charge);
    printf("  Height: %d\n\n", node->hauteur);
}

void printTree(NoeudAVL *root)
{
    if (root == NULL)
    {
        return;
    }

    // Parcours récursif in-order
    printf("Enfant Gauche");
    printTree(root->fg);
    printNodeInfo(root);
    printf("Enfant Droite");
    printTree(root->fd);
}

int main(int argc, char *argv[])
{
    int nb_entrees = 0;

    DataCSV *entrees = parserLigneCSV(argv[1], &nb_entrees);
    for (int i = 0; i < nb_entrees; i++)
    {
        DataCSV entry = entrees[i];
        printf("Entry %d:\n Centrale: %d, HV-B: %d, HV-A: %d, LV: %d, Entreprise: %d, Particulier: %d, Capacité: %ld, charge: %ld\n",
               i + 1, entry.id_centrale, entry.id_hvb, entry.id_hva,
               entry.id_lv, entry.id_entreprise, entry.id_particulier, entry.capacite, entry.charge);
        printf("\n");
    }
    NoeudAVL *arbre = creerArbre(entrees, nb_entrees);
    printTree(arbre);

    free(entrees);
    free(arbre);
    return 0;
}