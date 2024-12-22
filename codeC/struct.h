#ifndef STRUCT_H
#define STRUCT_H

typedef struct DataCSV
{
    int id_station;
    long capacite; // Capacite (en kWh)
    long charge;   // Charge consommee (en kWh)
} DataCSV;

typedef struct NoeudAVL
{
    int id;              // Identifiant unique de la station
    int equilibre;       // Equilibre du noeud dans l'arbre AVL
    long long capacite;  // Capacite (quantite d'energie produite ou transferee en kWh)
    long long charge;    // Charge consommee (quantite d'energie utilisee en kWh)
    struct NoeudAVL *fg; // Pointeur vers le sous-arbre gauche
    struct NoeudAVL *fd; // Pointeur vers le sous-arbre droit
} NoeudAVL;

#endif
