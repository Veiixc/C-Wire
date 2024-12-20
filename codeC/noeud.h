#ifndef NOEUD_H
#define NOEUD_H
#include "./struct.h"

NoeudAVL *creerNoeud(int id, int id_parent, TYPE_STATION type_station, CONSOMMATEUR consommateur, int est_racine, long long capacite, long long charge);
int hauteur(NoeudAVL *avl);
void mettreaJourHauteur(NoeudAVL *avl);
NoeudAVL *rotationGauche(NoeudAVL *a);
NoeudAVL *rotationDroite(NoeudAVL *a);
NoeudAVL *rotationDoubleDroite(NoeudAVL *avl);
NoeudAVL *rotationDoubleGauche(NoeudAVL *avl);
NoeudAVL *equilibrerAVL(NoeudAVL *avl);
NoeudAVL *insertionAVL(NoeudAVL *a, NoeudAVL *b);
int estEnSurconsommation(NoeudAVL *noeud);
int estEnSousConsommation(NoeudAVL *noeud);
void afficherStationsEnSurconsommation(NoeudAVL *racine);
void afficherStationsEnSousConsommation(NoeudAVL *racine);
int rechercherNoeud(NoeudAVL *racine, int id, NoeudAVL **noeudTrouve);
NoeudAVL *creerArbre(DataCSV *entrees, int nb_entrees);

#endif
