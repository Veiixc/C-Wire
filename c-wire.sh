#!/bin/bash
aide(){
    echo "paramètres:"
    echo "chemin du fichiercsv(obligatoire)"
    echo "type de station(hvb, hva, lv) (obligatoire)"
    echo "Type de consommateur (comp, indiv, all) (obligatoire)"
    echo "Identification d'une centrale(optionnel)"
}
if [[ $@ == *"-h"* ]]; then
 echo "aide à afficher"
 aide
    exit 0
fi 

if [ $# -lt 3 ]; then 
    echo "arguments insuffisants"
    exit 1          
fi

chemin_csv=$1
type_station=$2
type_consommateur=$3
id_centrale=$4

echo $type_station


# if [ ! -f "$chemin_csv" ]; then
# echo "le fichier CSV n'existe pas"
# aide
# exit 2
# fi

# if (( $type_station != "hvb" )); then 
if [ $type_station != "hvb" ] ; then 
echo "le type doit être 'hvb' 'hva' ou 'lv'"
aide
exit 3
fi

# if [[ ! "$type_consommateur" = ]]; then 
# echo "le type doit être 'comp' 'indiv' ou 'all'"
# aide
# exit 3
# fi
 
 
mkdir -p tmp graphs
