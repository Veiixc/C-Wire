set datafile separator ":"
set terminal png size 800,600
set output nom_image
set title "Capacité et Consommation par Station " . type_station
set xlabel "Station " . type_station
set ylabel "Valeurs"
set grid

# Définir les styles pour les barres
set style fill solid 1.0 border -1  # Remplissage des barres
set boxwidth 0.4  # Largeur des barres
set key at screen 0.97, 0.98 # Placer la légende au premier plan (coin supérieur droit)

# Afficher les barres côte à côte en les décalant
plot datafileEntry using (column(1)-0.2):2:xtic(1) title "Capacité" lc rgb "blue" with boxes, \
     datafileEntry using (column(1)+0.2):3 title "Consommation" lc rgb "red" with boxes
