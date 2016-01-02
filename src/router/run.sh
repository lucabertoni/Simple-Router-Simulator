clear
echo "/=================START===============/"
make clean
make
echo "Eseguo..."
./router 192.168.0.1
echo "Programma terminato. Codice valore di ritorno esecuzione: "$?
echo "/==================END================/"