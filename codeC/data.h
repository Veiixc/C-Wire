#ifndef DATA_H
#define DATA_H
#include "./struct.h"

DataCSV *parserLigneCSV(char *chemin, int *nb_entrees);
void ecrireFichier(NoeudAVL *arbre, char *station, char *consommateur);
void remplirFichier(FILE *file, NoeudAVL *arbre);
#endif
