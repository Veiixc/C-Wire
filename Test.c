#include <stdio.h>
#include <stdlib.h>
typedef struct AVL{
    int stationID; //Id de la station
    int Capacity ; //Capacité de la station
    int SumCons ;//Somme de la consomation
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
    return new;
}

