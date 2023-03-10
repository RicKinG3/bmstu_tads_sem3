#!/bin/bash
pos_in=$1   # имя файла для подмены потока входа	
pos_out=$2  # имя файла с истиными значениями вывода
ARGS=$3     # имя файла с ключами
error_memory=0

eval "echo > temp_pos_out.txt"

eval "./app.exe $ARGS"

if ./func_tests/scripts/comparator.sh "temp_pos_out.txt" "$pos_out"; then
    if [[ $error_memory == 0 ]]; then
        exit 0
    else
        exit 1 #тесты прошли проверку, память нет
    fi
else
    if [[ $error_memory == 0 ]]; then
        exit 2 #тесты не прошли, но память прошла
    else
        exit 3 #тесты не прошли проверку, память тоже
    fi
fi
