set datafile separator ":"
set terminal png size 10000,600
set output nom_image
set title "Capacité et Consommation par Station " . type_station
set xlabel "Stations " . type_station
set ylabel "Consommation et capacité (en Kwh)"
set grid
set xtics rotate by 45  # Rotation pour plus de lisibilité des tics
set xtics offset 0,-1.5  # Déplacer les tics vers le bas


# Définir les styles pour les barres
set style fill solid 1.0 border -1  # Remplissage des barres
set boxwidth 0.4  # Largeur des barres
set key center top # Placer la légende

# Afficher les barres côte à côte en les décalant
plot datafileEntry using (column(1)-0.2):2:xtic(1) title "Capacité" lc rgb "blue" with boxes, \
     datafileEntry using (column(1)+0.2):3 title "Consommation" lc rgb "purple" with boxes
