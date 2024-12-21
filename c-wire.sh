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

if [ ! -f "$chemin_csv" ]; then
echo "Erreur : le fichier CSV n'existe pas"
aide
exit 2
fi

# if (( $type_station != "hvb" )); then 
# if [ $type_station != "hvb" ] ; then 

if [[ ! "$type_station" =~ ^(hvb|hva|lv)$ ]]; then
    echo -e "Erreur : Le type de station doit être hvb, hva ou lv."
aide
    exit 3
fi

if [[ ! "$type_consommateur" =~ ^(comp|indiv|all)$ ]]; then
    echo -e "Erreur : Le type de consommateur doit être 'comp', 'indiv' ou 'all'."
aide
    exit 1
fi
 
 if [[ "$type_station" =~ ^(hvb|hva)$ && "$type_consommateur" =~ ^(indiv|all)$ ]]; then
    echo -e "Erreur: Les combinaisons suivantes sont interdites :"
    echo "  hvb all, hvb indiv, hva all, hva indiv"
aide
    exit 1
fi

c_compilation=./codeC/C-wire
if [[ ! -x "$c_compilation" ]]; then
    echo "Compilation en cours"
    make -C ./codeC
    if [[ $? -eq 0 ]]; then
        echo "Compilation réussie."
    else
        echo -e "Erreur : Échec de la compilation du programme C."
aide
        exit 1
    fi
fi

mkdir -p tmp graphs tests
rm -rf tmp/* graphs/*

debut_temps=$(date +%s)

# sleep 5
fin_temps=$(date +%s)

fichier_filtre="./tmp/${2}_${3}_${4}cwire.csv"
awk -F';' -v station="$2" -v conso="$3" -v fichier_filtre="$fichier_filtre" '
BEGIN {
    OFS=";"
    print "type de station (" station ");capacité;consommation" > fichier_filtre
}

NR > 1 {
    if (station == "hvb") stat = $2
    else if (station == "hva") stat = $3
    else if (station == "lv") stat = $4
    else {
        print "Erreur : Type de station invalide." > "/dev/stderr"
        exit 8
    }

    if (conso == "comp") cons = $5
    else if (conso == "indiv") cons = $6
    else if (conso == "all") cons = ($5 + $6)
    else {
        print "Erreur : Type de consommateur invalide." > "/dev/stderr"
        exit 9
    }

    if (station == "hvb" && stat != "-" && $3 == "-") {
        print stat, $7, $8 >> fichier_filtre
    } else if (station == "hva" && stat != "-" && $4 == "-") {
        print stat, $7, $8 >> fichier_filtre
    } else if (station == "lv") {
        if ((conso == "indiv" && $6 == "-") || (conso == "comp" && $5 == "-") || conso == "all") {
            print stat, $7, $8 >> fichier_filtre
        }
    }
}

END {
  print "Succès du traitement. Les résultats se trouvent dans le dossier tests.";
  print ""
} ' $chemin_csv
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
# if [[ -z "$central_id" ]]; then
#     # Si pas d'ID de centrale, exécute le programme C sans l'ID
#     $c_program "$csv_path" "$station_type" "$consumer_type"
# else
#     # Si l'ID de centrale est fourni, exécute le programme C avec l'ID
#     $c_program "$csv_path" "$station_type" "$consumer_type" "$central_id"
# fi
echo "Lancement du programme"
$c_compilation $fichier_filtre $type_station $type_consommateur

# Vérification du succès de l'exécution de la commande précédente
if [[ $? -ne 0 ]]; then
    # Si la commande a échoué, affiche un message d'erreur et termine le script
    echo "Erreur : Le traitement a échoué."
    exit 1
fi


# duration=$((fin_temps - debut_temps))
# echo "Durée totale : $duration secondes"


echo "Fin du Traitement de donnés."
exit 0