#!/bin/bash
echo "Début du traitement de donnés."

aide(){
    echo "paramètres:"
    echo "chemin du fichiercsv(obligatoire)"
    echo "type de station(hvb, hva, lv) (obligatoire)"
    echo "Type de consommateur (comp, indiv, all) (obligatoire)"
    echo "Identification d'une centrale(optionnel)"
}

debut_temps=$(date +%s%3N)
# indice 1 = temps de filtrage
# indice 2 = tmps d'exécution du programme
# indice 3 = temps de tri
# indice 4 = temps de création des graphiques
temps_debut=($debut_temps $debut_temps $debut_temps $debut_temps)
temps_fin=($debut_temps $debut_temps $debut_temps $debut_temps)
temps_nom=("Filtrage des données" "Exécution du programme" "Tri des données" "Création des graphiques")
afficherTemps(){
    for i in "${!temps_debut[@]}"; do
        debut=${temps_debut[$i]}
        fin=${temps_fin[$i]}
        duree=$(echo "scale=3; ($fin - $debut) / 1000" | bc)
        echo -e "L'exécution de ${temps_nom[$i]} a pris ${duree} secondes."
    done
}

if [[ $@ == *"-h"* ]]; then
    echo "aide à afficher"
    aide
    afficherTemps
    exit 0
fi 

if [ $# -lt 3 ]; then 
    echo "arguments insuffisants"
    aide
    afficherTemps
    exit 1          
fi

chemin_csv=$1
type_station=$2
type_consommateur=$3
id_centrale=$4

if [ ! -f "$chemin_csv" ]; then
    echo "Erreur : le fichier CSV n'existe pas"
    aide
    afficherTemps
    exit 2
fi

# if (( $type_station != "hvb" )); then 
# if [ $type_station != "hvb" ] ; then 

if [[ ! "$type_station" =~ ^(hvb|hva|lv)$ ]]; then
    echo "Erreur : Le type de station doit être hvb, hva ou lv."
    aide
    afficherTemps
    exit 3
fi

if [[ ! "$type_consommateur" =~ ^(comp|indiv|all)$ ]]; then
    echo "Erreur : Le type de consommateur doit être 'comp', 'indiv' ou 'all'."
    aide
    afficherTemps
    exit 1
fi
 
 if [[ "$type_station" =~ ^(hvb|hva)$ && "$type_consommateur" =~ ^(indiv|all)$ ]]; then
    echo -e "Erreur: Les combinaisons suivantes sont interdites :"
    echo "  hvb all, hvb indiv, hva all, hva indiv"
    aide
    afficherTemps
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
        afficherTemps
        exit 1
    fi
fi

mkdir -p tmp graphs tests
rm -rf tmp/* 

# Filtrage des données
echo -e "Filtre des données pour la station ${type_station} et le consommateur ${type_consommateur}"
temps_debut[0]=$(date +%s%3N)
fichier_filtre="./tmp/${2}_${3}_${4}_filtre.csv" # renommer si pas de centrale id
awk -F';' -v station="$type_station" -v conso=$type_consommateur -v id_centrale=$id_centrale -v fichier_filtre="$fichier_filtre" '
BEGIN {
    OFS=";"
    print "type de station (" station ");capacité;consommation" > fichier_filtre
}

NR > 1 {
    if (length(id_centrale) != 0 && id_centrale != $1) next

    if (station == "hvb") stat = $2
    else if (station == "hva") stat = $3
    else if (station == "lv") stat = $4
    else {
        print "Erreur : Type de station invalide." > "/dev/stderr"
        exit 1
    }

    if (station == "hvb" && stat != "-" && $3 == "-") {
        print stat, $7, $8 >> fichier_filtre
    } else if (station == "hva" && stat != "-" && $4 == "-") {
        print stat, $7, $8 >> fichier_filtre
    } else if (station == "lv" && stat != "-") {
        if ((conso == "all") || (conso == "indiv" && $5 == "-") || (conso == "comp" && $6 == "-")) {
            print stat, $7, $8 >> fichier_filtre
        }
    }
}

END {
} ' $chemin_csv
temps_fin[0]=$(date +%s%3N)


# Exécution du programme C
echo "Lancement du programme"
temps_debut[1]=$(date +%s%3N)
$c_compilation $fichier_filtre $type_station $type_consommateur $id_centrale
temps_fin[1]=$(date +%s%3N)

# Vérification du succès de l'exécution de la commande précédente
if [[ $? -ne 0 ]]; then
    # Si la commande a échoué, affiche un message d'erreur et termine le script
    echo -e "Erreur : Le traitement a échoué.\n"
    afficherTemps
    exit 1
fi

#Tri du fichier
echo "Tri des fichiers"
temps_debut[2]=$(date +%s%3N)
directory="./tmp"
for file in "$directory"/*.csv; do
    if [[ "$file" =~ non_trie\.csv$ ]]; then
        base_name=$(basename "$file" .csv)
        base_name=${base_name/_non_trie/}  # remplacement du nom temporaire
        sort -t':' -k2 -n $file > "./tests/${base_name}.csv"

        # genere le fichier lv_min_max
        if [ $file == "./tmp/lv_all_non_trie.csv" ]; then
            sort -t':' -k4 -n "./tmp/lv_all_minmax.csv" > "./tmp/lv_all_minmax_trie.csv"
            head -n 11 "./tmp/lv_all_minmax_trie.csv" > ./tmp/lv_min_trie.csv
            tail -n 10 "./tmp/lv_all_minmax_trie.csv" > ./tmp/lv_max_trie.csv
            cat ./tmp/lv_max_trie.csv >> ./tmp/lv_min_trie.csv
            cp ./tmp/lv_min_trie.csv ./tests/lv_all_minmax.csv
        fi
    fi
done;
temps_fin[2]=$(date +%s%3N)

# Génération des graphiques
echo "Création des graphiques"
directory="./tests"
temps_debut[3]=$(date +%s%3N)
for file in "$directory"/*.csv; do
    base_name=$(basename "$file" .csv)
    # Générer le chemin de sortie dans le dossier graphs basename recupere le nom sans le chemin
    output_file="./graphs/${base_name}.png"
    # Générer la commande gnuplot avec le fichier spécifique
    if [ $file == "./tests/lv_all_minmax.csv" ]; then
        gnuplot -e "datafileEntry='$file' ; nom_image='$output_file' ; type_station='$type_station'" ./graphs/plotLV.gp
    elif [[ ! $file =~ ^\./tests/lv_all\.csv$ ]]; then
        gnuplot -e "datafileEntry='$file' ; nom_image='$output_file' ; type_station='$type_station'" ./graphs/plot.gp
    fi  
done
temps_fin[3]=$(date +%s%3N)

afficherTemps
echo "Fin du traitement de données."
exit 0