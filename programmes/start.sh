nomDuFichier=ville.txt

echo ${nomDuFichier}

start=$(date +%s)
# Donne le contenue de nomDuFichier a afficherOrdres, qui ecrit dans direction.txt les directions a suivre
bin/afficherOrdres ${nomDuFichier} > direction.txt

# Donne le contenue de direction.txt a robot, qui execute les directions
sudo bin/robot < direction.txt

end=$(date +%s)
duree=$((end -start))

echo "le temps d'excution est de $duree s "