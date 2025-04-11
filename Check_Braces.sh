#!/bin/bash

#recorre todos los archivos .c en el dir actual
for archivo in *.c; do
#cuenta las llaves de apertura  '{' y de cierre '}'
	apertura=$(grep -o "{" "$archivo" | wc -l)
	cierre=$(grep -o "}" "$archivo" | wc -l)

#si el num de llaves de apertura no coincide el num de cierre

if [ "$apertura" -ne "$cierre" ]; then
	echo "El archivo '$archivo' tiene desbalance de llaves: $apertura '{' y  $cierre '}'."
fi
done
