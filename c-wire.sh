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


if [ ! -f "$chemin_csv" ]; then
echo "Erreur : le fichier CSV n'existe pas"
aide
exit 2
fi

# if (( $type_station != "hvb" )); then 
# if [ $type_station != "hvb" ] ; then 

if [[ ! "$type_station" =~ ^(hvb|hva|lv)$ ]]; then
    echo -e "Erreur : Le type de station doit être hvb, hva ou lv."
    exit 3
fi

if [[ ! "$type_consommateur" =~ ^(comp|indiv|all)$ ]]; then
    echo -e "Erreur : Le type de consommateur doit être 'comp', 'indiv' ou 'all'."
    exit 1
fi
 
 if [[ "$type_station" =~ ^(hvb|hva)$ && "$type_consommateur" =~ ^(indiv|all)$ ]]; then
    echo -e "Erreur: Les combinaisons suivantes sont interdites :"
    echo "  hvb all, hvb indiv, hva all, hva indiv"
    exit 0
fi


c_compilation = ./a.out...
if [[ ! -x "$c_compilation" ]]; then
    echo "Compilatio en cours"
    ./a.out...
if [[ $? -eq 0 ]]; then
    echo "Compilation réussie."
else
    echo -e "Erreur : Échec de la compilation du programme C."
    exit 1
fi
fi

mkdir -p tmp graphs
rm -rf tmp/* graphs/*



debut_temps=$(date +%s)

sleep 5
fin_temps=$(date +%s)


#output_file="tmp/resultat.csv"
#if [ -z "$id_centrale" ]; then
#    grep "$type_station" "$fichier_csv" | grep "$type_consommateur" > "$output_file"
#else
#    grep "$type_station" "$fichier_csv" | grep "$type_consommateur" | grep "$id_centrale" > "$output_file"
#fi

#if [ ! -s "$output_file" ]; then
#    echo "Aucune donnée trouvée correspondant aux critères."
#    exit 1
#fi
#echo "Les résultats sont enregistrés dans $output_file."

# Vérification si l'ID de la centrale est vide
if [[ -z "$central_id" ]]; then
    # Si pas d'ID de centrale, exécute le programme C sans l'ID
    $c_program "$csv_path" "$station_type" "$consumer_type"
else
    # Si l'ID de centrale est fourni, exécute le programme C avec l'ID
    $c_program "$csv_path" "$station_type" "$consumer_type" "$central_id"
fi

# Vérification du succès de l'exécution de la commande précédente
if [[ $? -ne 0 ]]; then
    # Si la commande a échoué, affiche un message d'erreur et termine le script
    echo -e "Erreur : Le traitement a échoué."
    exit 1
fi


duration=$((fin_temps - debut_temps))
echo "Durée totale : $duration secondes"


echo "Fin du Traitement de donnés."
exit 0