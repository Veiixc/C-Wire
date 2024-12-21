#ifndef NOEUD_H
#define NOEUD_H
#include "./struct.h"

int hauteur(NoeudAVL *avl);
void mettreaJourHauteur(NoeudAVL *avl);
NoeudAVL *rotationGauche(NoeudAVL *a);
NoeudAVL *rotationDroite(NoeudAVL *a);
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
int equilibre(NoeudAVL *avl);
#endif
