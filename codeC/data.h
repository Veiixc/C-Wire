#ifndef DATA_H
#define DATA_H
#include "./struct.h"

DataCSV *parserLigneCSV(const char *chemin, int *nb_entrees);
void ecrireFichier(NoeudAVL *arbre, char *station, char *consommateur, char *id_centrale);
void remplirFichier(FILE *fichier, NoeudAVL *arbre);
void remplirFichierLV(FILE *fichier, NoeudAVL *arbre);
#endif
