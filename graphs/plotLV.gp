set datafile separator ":"
set terminal png size 10000,600
set output nom_image
set title "Capacité, Consommation et surconsommation par Station " . type_station
set xlabel "Stations " . type_station
set ylabel "Consommation et capacité (en Kwh)"
set grid

# Définir les styles pour les barres
set style fill solid 1.0 border -1  # Remplissage des barres
set boxwidth 0.3  # Largeur des barres
set key center top # Placer la légende

set format x ""  # Cela supprime le format des valeurs sur l'axe X

colorFunc(value) = value > 0  ? 0xFF0000 : 0x00FF00  

# Afficher les barres côte à côte en les décalant
plot datafileEntry using (column(0)-0.4):2 title "Capacité" lc rgb "blue" with boxes, \
     datafileEntry using (column(0)-0.1):3 title "Consommation" lc rgb "purple" with boxes, \
     datafileEntry using (column(0)+0.2):4:(colorFunc($5)) title "Consommation absolue" lc rgb var with boxes, \
     datafileEntry using (column(0)):3:1 with labels offset 0,1 notitle