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

NoeudAVL *équilibrerAVL(NoeudAVL *avl)
{
    if (hauteur(avl->fd) - hauteur(avl->fg) > 1)
    {
        if (hauteur(avl->fd->fd) - hauteur(avl->fd->fg) <= 0)
        {
            return rotationdroite(avl);
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
            return rotationgauche(avl);
        }
        else
        {
            return rotationDoubleGauche(avl);
        }
    }
    return avl;
}

NoeudAVL *insertionAVL(NoeudAVL *a, int e, int *h)
{
    if (a == NULL)
    {           // Si l'arbre est vide, crée un nouveau nœud
        *h = 1; // La hauteur a augmenté
        return creerAVL(e);
    }
    else if (e < a->hauteur)
    { // Si l'élément est plus petit, insérer à gauche
        a->fg = insertionAVL(a->fg, e, h);
        *h = -*h; // Inverse l'impact de la hauteur
    }
    else if (e > a->hauteur)
    { // Si l'élément est plus grand, insérer à droite
        a->fd = insertionAVL(a->fd, e, h);
    }
    else
    { // Élément déjà présent
        *h = 0;
        return a;
    }

    // Mise à jour du facteur d'équilibre et rééquilibrage si nécessaire
    if (*h != 0)
    {
        a->hauteur += *h;
        a = equilibrerAVL(a);
        *h = (a->hauteur == 0) ? 0 : 1; // Mise à jour de la hauteur
    }
    return a;
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
