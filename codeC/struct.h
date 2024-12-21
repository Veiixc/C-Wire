#ifndef STRUCT_H
#define STRUCT_H

typedef struct DataCSV
{
    int id_station;
    long capacite; // Capacite (en kWh)
    long charge;   // Charge consommee (en kWh)
} DataCSV;

// typedef enum
// {
//     POWER_PLANT,
//     HVB,
//     HVA,
//     LV
// } TYPE_STATION;

// typedef enum
// {
//     ENTREPRISE,
//     PARTICULIER,
//     NONE
// } CONSOMMATEUR;

typedef struct NoeudAVL
{
    int id; // Identifiant unique de la station ou du consommateur
    // int id_parent; // Identifiant du parent dans la hierarchie
    int equilibre; // Hauteur du noeud dans l'arbre AVL
    // TYPE_STATION type_station; // Type de station (centrale, HV-B, HV-A, LV)
    // CONSOMMATEUR consommateur; // Type de consommateur (entreprise, particulier)
    // int est_racine;            // Indicateur si le noeud est la racine (1 si oui, 0 sinon)
    long long capacite;  // Capacite (quantite d'energie produite ou transferee en kWh)
    long long charge;    // Charge consommee (quantite d'energie utilisee en kWh)
    struct NoeudAVL *fg; // Pointeur vers le sous-arbre gauche
    struct NoeudAVL *fd; // Pointeur vers le sous-arbre droit
} NoeudAVL;

#endif
