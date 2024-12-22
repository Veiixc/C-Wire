#ifndef NOEUD_H
#define NOEUD_H
#include "./struct.h"

NoeudAVL *rotationGauche(NoeudAVL *avl);
NoeudAVL *rotationDroite(NoeudAVL *avl);
NoeudAVL *rotationDoubleDroite(NoeudAVL *avl);
NoeudAVL *rotationDoubleGauche(NoeudAVL *avl);
NoeudAVL *equilibrerAVL(NoeudAVL *avl);
NoeudAVL *insertionAVL(NoeudAVL *a, NoeudAVL *b, int *h);
NoeudAVL *creerArbre(DataCSV *entrees, int nb_entrees);
NoeudAVL *creerNoeud(int id, long long capacite, long long charge);
int max3(int a, int b, int c);
int min3(int a, int b, int c);
int max(int a, int b);
int min(int a, int b);
void afficheInformationsNoeud(NoeudAVL *noeud);
void affichePrefixe(NoeudAVL *noeud);
#endif
