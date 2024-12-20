#include <stdlib.h>
#include <stdio.h>
#include "./struct.h"
#include "./noeud.h"
#define MAX_NODES 100000000
// Table de correspondance pour retrouver les nœuds par leur ID
NoeudAVL *nodeTable[MAX_NODES] = {NULL};

NoeudAVL *creerNoeud(int id, int id_parent, TYPE_STATION type_station, CONSOMMATEUR consommateur, int est_racine, long long capacite, long long charge)
{
    NoeudAVL *noeud = (NoeudAVL *)malloc(sizeof(NoeudAVL));
    if (noeud == NULL)
    {
        fprintf(stderr, "Erreur : allocation memoire echouee.\n");
        exit(EXIT_FAILURE);
    }

    noeud->id = id;
    noeud->id_parent = id_parent;
    noeud->type_station = type_station;
    noeud->consommateur = consommateur;
    noeud->est_racine = est_racine;
    noeud->capacite = capacite;
    noeud->charge = charge;
    noeud->hauteur = 1;
    noeud->fg = NULL;
    noeud->fd = NULL;

    nodeTable[id] = noeud;

    return noeud;
}

int hauteur(NoeudAVL *avl)
{
    if (avl == NULL)
    {
        return 0;
    }
    return avl->hauteur;
}

void mettreaJourHauteur(NoeudAVL *avl)
{
    int hauteurGauche = hauteur(avl->fg);
    int hauteurDroite = hauteur(avl->fd);
    if (hauteurGauche > hauteurDroite)
    {
        avl->hauteur = 1 + hauteurGauche;
    }
    else
    {
        avl->hauteur = 1 + hauteurDroite;
    }
}

NoeudAVL *rotationGauche(NoeudAVL *a)
{
    if (a == NULL)
    {
        return 0;
    }
    NoeudAVL *pivot = a->fd;
    // int eq_a = a->eq, eq_p = pivot->eq;

    a->fd = pivot->fg;
    pivot->fg = a;
    mettreaJourHauteur(a);
    mettreaJourHauteur(pivot);

    // a->eq = eq_a - max(eq_p, 0) - 1;                            // voir CM
    // pivot->eq = min3(eq_a - 2, eq_a + eq_p - 2, eq_p - 1);      // voir CM

    return pivot;
}

NoeudAVL *rotationDroite(NoeudAVL *a)
{
    if (a == NULL)
    {
        return 0;
    }
    NoeudAVL *pivot = a->fg;
    // int eq_a = a->eq, eq_p = pivot->eq;

    a->fg = pivot->fd;
    pivot->fd = a;
    mettreaJourHauteur(a);
    mettreaJourHauteur(pivot);

    // a->eq = eq_a - max(eq_p, 0) - 1;                            // voir CM
    // pivot->eq = min3(eq_a - 2, eq_a + eq_p - 2, eq_p - 1);      // voir CM

    return pivot;
}

NoeudAVL *rotationDoubleDroite(NoeudAVL *avl)
{
    if (avl == NULL)
    {
        return 0;
    }
    avl->fd = rotationDroite(avl->fd);
    return rotationGauche(avl);
}

NoeudAVL *rotationDoubleGauche(NoeudAVL *avl)
{
    if (avl == NULL)
    {
        return 0;
    }
    avl->fg = rotationGauche(avl->fg);
    return rotationDroite(avl);
}

NoeudAVL *equilibrerAVL(NoeudAVL *avl)
{
    if (hauteur(avl->fd) - hauteur(avl->fg) > 1)
    {
        if (hauteur(avl->fd->fd) - hauteur(avl->fd->fg) <= 0)
        {
            return rotationDroite(avl);
        }
        else
        {
            return rotationDoubleDroite(avl);
        }
    }
    else if (hauteur(avl->fd) - hauteur(avl->fg) < -1)
    {
        if (hauteur(avl->fg->fd) - hauteur(avl->fg->fg) >= 0)
        {
            return rotationGauche(avl);
        }
        else
        {
            return rotationDoubleGauche(avl);
        }
    }
    return avl;
}

// NoeudAVL *insertionAVL(NoeudAVL *a, int e, int *h)
// {
//     if (a == NULL)
//     {           // Si l'arbre est vide, crée un nouveau nœud
//         *h = 1; // La hauteur a augmenté
//         return creerAVL(e);
//     }
//     else if (e < a->hauteur)
//     { // Si l'élément est plus petit, insérer à gauche
//         a->fg = insertionAVL(a->fg, e, h);
//         *h = -*h; // Inverse l'impact de la hauteur
//     }
//     else if (e > a->hauteur)
//     { // Si l'élément est plus grand, insérer à droite
//         a->fd = insertionAVL(a->fd, e, h);
//     }
//     else
//     { // Élément déjà présent
//         *h = 0;
//         return a;
//     }

//     // Mise à jour du facteur d'équilibre et rééquilibrage si nécessaire
//     if (*h != 0)
//     {
//         a->hauteur += *h;
//         a = equilibrerAVL(a);
//         *h = (a->hauteur == 0) ? 0 : 1; // Mise à jour de la hauteur
//     }
//     return a;
// }

NoeudAVL *insertionAVL(NoeudAVL *parent, NoeudAVL *noeud)
{
    if (parent == NULL)
    {
        return noeud;
    }
    else if (noeud->id < parent->id)
    {
        parent->fg = insertionAVL(parent->fg, noeud);
    }
    else if (noeud->id > parent->id)
    {
        parent->fd = insertionAVL(parent->fd, noeud);
    }
    else
    {
        return parent;
    }
    mettreaJourHauteur(parent);
    // return equilibrerAVL(parent);
    return parent;
}

int estEnSurconsommation(NoeudAVL *noeud)
{
    if (noeud == NULL)
        return 0;
    return (noeud->charge > noeud->capacite);
}

int estEnSousConsommation(NoeudAVL *noeud)
{
    if (noeud == NULL)
        return 0;
    return (noeud->charge < noeud->capacite);
}

void afficherStationsEnSurconsommation(NoeudAVL *racine)
{
    if (racine == NULL)
        return;
    afficherStationsEnSurconsommation(racine->fg);
    if (estEnSurconsommation(racine))
    {
        printf("Station ID: %d est en surconsommation (Charge: %lld, Capacité: %lld)\n",
               racine->id, racine->charge, racine->capacite);
    }
    afficherStationsEnSurconsommation(racine->fd);
}

void afficherStationsEnSousConsommation(NoeudAVL *racine)
{
    if (racine == NULL)
        return;
    afficherStationsEnSousConsommation(racine->fg);
    if (estEnSousConsommation(racine))
    {
        printf("Station ID: %d est en sous-consommation (Charge: %lld, Capacité: %lld)\n",
               racine->id, racine->charge, racine->capacite);
    }
    afficherStationsEnSousConsommation(racine->fd);
}

int rechercherNoeud(NoeudAVL *racine, int id, NoeudAVL **noeudTrouve)
{
    if (racine == NULL)
    {
        return 0;
    }
    if (racine->id == id)
    {
        *noeudTrouve = racine;
        return 1;
    }
    if (id < racine->id)
    {
        return rechercherNoeud(racine->fg, id, noeudTrouve);
    }
    else
    {
        return rechercherNoeud(racine->fd, id, noeudTrouve);
    }
}

NoeudAVL *creerArbre(DataCSV *entrees, int nb_entrees)
{
    NoeudAVL *racine = NULL;

    for (int i = 0; i < nb_entrees; i++)
    {
        DataCSV entree = entrees[i];

        // Déterminer le type de station et de consommateur
        TYPE_STATION stationType;
        CONSOMMATEUR consumer = NONE;

        if (entree.id_centrale != -1 && entree.id_hvb == -1 && entree.id_hva == -1 && entree.id_lv == -1)
        {
            stationType = POWER_PLANT; // Centrale
        }
        else if (entree.id_hvb != -1)
        {
            stationType = HVB; // Station HV-B
        }
        else if (entree.id_hva != -1)
        {
            stationType = HVA; // Station HV-A
        }
        else if (entree.id_lv != -1)
        {
            stationType = LV; // Poste LV
        }

        if (entree.id_entreprise != -1)
            consumer = ENTREPRISE;
        else if (entree.id_particulier != -1)
            consumer = PARTICULIER;

        int nodeId, parentId;

        // Déterminer le type de nœud et ses IDs
        if (entree.id_centrale != -1 && entree.id_hvb == -1 && entree.id_hva == -1 && entree.id_lv == -1)
        {
            // Cas d'une centrale (racine)
            nodeId = entree.id_centrale;
            parentId = -1; // Pas de parent pour une racine
        }
        else if (entree.id_hvb != -1 && entree.id_hva == -1 && entree.id_lv == -1)
        {
            // Cas d'une station HV-B
            nodeId = entree.id_hvb;
            parentId = entree.id_centrale; // Parent = centrale
        }
        else if (entree.id_hva != -1 && entree.id_lv == -1)
        {
            // Cas d'une station HV-A
            nodeId = entree.id_hva;
            parentId = entree.id_hvb; // Parent = station HV-B
        }
        else if (entree.id_lv != -1)
        {
            // Cas d'un poste LV
            nodeId = entree.id_lv;
            parentId = entree.id_hva; // Parent = station HV-A
        }
        else if (entree.id_entreprise != -1)
        {
            // Cas d'un consommateur (entreprise)
            nodeId = entree.id_entreprise;
            if (entree.id_hvb != -1)
            {
                parentId = entree.id_hvb; // Parent = station HV-B
            }
            else if (entree.id_hva != -1)
            {
                parentId = entree.id_hva; // Parent = station HV-A
            }
            else
            {
                parentId = entree.id_lv; // Parent = poste LV
            }
        }
        else if (entree.id_particulier != -1)
        {
            // Cas d'un consommateur (particulier)
            nodeId = entree.id_particulier;
            parentId = entree.id_lv; // Parent = poste LV
        }
        else
        {
            printf("Erreur : entrée invalide ou incomplète\n");
            continue; // Ignorer cette entrée
        }
        // Créer le nœud
        NoeudAVL *node = creerNoeud(nodeId, parentId, stationType, consumer, stationType == POWER_PLANT, entree.capacite, entree.charge);

        // Ajouter au bon parent
        if (node->est_racine)
        {
            printf("isParent\n");
            racine = insertionAVL(racine, node);
        }
        else
        {
            printf("NotParent : parentId : %d\n", parentId);
            NoeudAVL *parent = nodeTable[parentId];
            printf("    Parent is %d\n", parent->id);
            if (parent)
            {
                printf("    Add children to Parent\n");
                insertionAVL(parent, node);
            }
        }
    }

    return racine;
}