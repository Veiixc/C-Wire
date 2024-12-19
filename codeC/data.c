#include <stdlib.h>
#include <stdio.h>
#include "./struct.h"

void parserLigneCSV(char *ligne, int *id, int *id_parent, TYPE_STATION *type_station,
                    CONSOMMATEUR *consommateur, int *est_racine,
                    long long *capacite, long long *charge)
{
    char *token;

    token = strtok(ligne, ":");
    *id = atoi(token);

    token = strtok(NULL, ":");
    *id_parent = atoi(token);

    token = strtok(NULL, ":");
    *type_station = (TYPE_STATION)atoi(token);

    token = strtok(NULL, ":");
    *consommateur = (CONSOMMATEUR)atoi(token);

    token = strtok(NULL, ":");
    *est_racine = atoi(token);

    token = strtok(NULL, ":");
    *capacite = atoll(token);

    token = strtok(NULL, ":");
    *charge = atoll(token);
}

NoeudAVL buildtree()
{
}