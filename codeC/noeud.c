#include <stdlib.h>
#include <stdio.h>
#include "./struct.h"
#include "./noeud.h"

NoeudAVL *rotationGauche(NoeudAVL *avl)
{
    if (avl == NULL)
    {
        return 0;
    }
    NoeudAVL *pivot = avl->fd;
    int eq_avl = avl->equilibre, eq_p = pivot->equilibre;

    avl->fd = pivot->fg;
    pivot->fg = avl;

    avl->equilibre = eq_avl - max(eq_p, 0) - 1;
    pivot->equilibre = min3(eq_avl - 2, eq_avl + eq_p - 2, eq_p - 1);

    return pivot;
}

NoeudAVL *rotationDroite(NoeudAVL *avl)
{
    if (avl == NULL)
    {
        return 0;
    }
    NoeudAVL *pivot = avl->fg;
    int eq_avl = avl->equilibre, eq_p = pivot->equilibre;

    avl->fg = pivot->fd;
    pivot->fd = avl;

    avl->equilibre = eq_avl - min(eq_p, 0) + 1;
    pivot->equilibre = max3(eq_avl + 2, eq_avl + eq_p + 2, eq_p + 1);

    return pivot;
}

int max(int a, int b)
{
    return a > b ? a : b;
}
int min(int a, int b)
{
    return a < b ? a : b;
}
int min3(int a, int b, int c)
{
    return (a < b ? (a < c ? a : c) : (b < c ? b : c));
}
int max3(int a, int b, int c)
{
    return (a > b ? (a > c ? a : c) : (b > c ? b : c));
}

NoeudAVL *rotationDoubleDroite(NoeudAVL *avl)
{
    if (avl == NULL)
    {
        return 0;
    }
    avl->fg = rotationGauche(avl->fg);
    return rotationDroite(avl);
}

NoeudAVL *rotationDoubleGauche(NoeudAVL *avl)
{
    if (avl == NULL)
    {
        return 0;
    }
    avl->fd = rotationDroite(avl->fd);
    return rotationGauche(avl);
}

NoeudAVL *equilibrerAVL(NoeudAVL *avl)
{
    if (avl->equilibre >= 2)
    { // Cas où l'arbre est déséquilibré à droite
        if (avl->fd->equilibre >= 0)
        {
            return rotationGauche(avl);
        }
        else
        {
            return rotationDoubleGauche(avl);
        }
    }
    else if (avl->equilibre <= -2)
    { // Cas où l'arbre est déséquilibré à gauche
        if (avl->fg->equilibre <= 0)
        {
            return rotationDroite(avl);
        }
        else
        {
            return rotationDoubleDroite(avl);
        }
    }
    return avl;
}

NoeudAVL *insertionAVL(NoeudAVL *parent, NoeudAVL *noeud, int *h)
{
    if (parent == NULL)
    {           // Si l'arbre est vide, crée un nouveau nœud
        *h = 1; // La equilibre a augmenté
        return noeud;
    }
    else if (noeud->id < parent->id)
    { // Si l'élément est plus petit, insérer à gauche
        parent->fg = insertionAVL(parent->fg, noeud, h);
        *h = -*h; // Inverse l'impact de la equilibre
    }
    else if (noeud->id > parent->id)
    { // Si l'élément est plus grand, insérer à droite
        parent->fd = insertionAVL(parent->fd, noeud, h);
    }
    else
    { // Élément déjà présent
        *h = 0;
        parent->charge += noeud->charge;
        return parent;
    }

    // Mise à jour du facteur d'équilibre et rééquilibrage si nécessaire
    if (*h != 0)
    {
        parent->equilibre += *h;
        parent = equilibrerAVL(parent);
        *h = (parent->equilibre == 0) ? 0 : 1; // Mise à jour de l'équilibre
    }
    return parent;
}

NoeudAVL *creerArbre(DataCSV *entrees, int nb_entrees)
{
    NoeudAVL *racine = NULL;
    int h = 0;
    for (int i = 0; i < nb_entrees; i++)
    {
        DataCSV entree = entrees[i];
        NoeudAVL *noeud = creerNoeud(entree.id_station, entree.capacite, entree.charge);

        racine = insertionAVL(racine, noeud, &h);
    }
    return racine;
}

NoeudAVL *creerNoeud(int id, long long capacite, long long charge)
{
    NoeudAVL *noeud = (NoeudAVL *)malloc(sizeof(NoeudAVL));
    if (noeud == NULL)
    {
        fprintf(stderr, "Erreur : allocation mémoire echouee.\n");
        exit(EXIT_FAILURE);
    }

    noeud->id = id;
    noeud->capacite = capacite;
    noeud->charge = charge;
    noeud->equilibre = 0;
    noeud->fg = NULL;
    noeud->fd = NULL;
    return noeud;
}

void afficheInformationsNoeud(NoeudAVL *noeud)
{
    if (noeud == NULL)
    {
        return;
    }

    printf("ID: %d\n", noeud->id);
    printf("  Capacity: %lld kWh\n", noeud->capacite);
    printf("  Load: %lld kWh\n", noeud->charge);
    printf("  Equilibre: %d\n", noeud->equilibre);
}

void affichePrefixe(NoeudAVL *noeud)
{
    if (noeud == NULL)
    {
        return;
    }

    afficheInformationsNoeud(noeud);
    affichePrefixe(noeud->fg);
    affichePrefixe(noeud->fd);
}