#include <stdlib.h>
#include <stdio.h>
#include "./struct.h"

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

    // tableNoeuds[id] = noeud;

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
    return rotationgauche(avl);
}

NoeudAVL *rotationDoubleGauche(NoeudAVL *avl)
{
    if (avl == NULL)
    {
        return 0;
    }
    avl->fg = rotationGauche(avl->fg);
    return rotationdroite(avl);
}