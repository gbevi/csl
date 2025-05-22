#!/bin/bash

echo "======================="
echo " Testando Parser"
echo "======================="

for teste in test/parser/*.txt; do
    echo "-----------------------"
    echo "Testando: $teste"
    ./meu_parser < "$teste"
    resultado=$?

    if [[ "$teste" == *_valido* ]]; then
        if [ $resultado -eq 0 ]; then
            echo "Teste válido passou como esperado."
        else
            echo "ERRO: Teste válido foi rejeitado!"
        fi
    else
        if [ $resultado -ne 0 ]; then
            echo "Teste inválido foi rejeitado como esperado."
        else
            echo "ERRO: Teste inválido foi aceito!"
        fi
    fi
done