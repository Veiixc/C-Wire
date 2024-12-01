#include <stdio.h>
#include <stdlib.h>
typedef struct AVL{
    int stationID; //Id de la station
    int Capacity ; //Capacité de la station
    int SumCons ;//Somme de la consomation
    int taille ; //taille du noeud
    struct AVL* fright ;
    struct AVL* fleft ;
}AVL;

typedef AVL* pAVL;

pAVL createAVL(int station, int Cap, int Sum){
    pAVL new = malloc(sizeof(AVL));
    if(new == NULL){
        exit(EXIT_FAILURE);
    }
    new->stationID = station;
    new->Capacity = Cap;
    new->SumCons = Sum;
    new->fright = NULL;
    new->fleft = NULL;
    return new;
}

int taille(pAVL avl){
    if(avl == NULL){
        return 0;
    }else{
    return avl->taille; 
    }
}

int calculequilibre(pAVL avl){
    if(avl == NULL){
        exit(EXIT_FAILURE);
    }
    return taille(avl->fright )-taille(avl->fleft);
}

pAVL rotationdroite(pAVL avl){
    if(avl == NULL){
        exit(EXIT_FAILURE);
    }
    
}