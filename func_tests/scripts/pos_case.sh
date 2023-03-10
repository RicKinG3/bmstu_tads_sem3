#!/bin/bash
pos_in=$1   # имя файла для подмены потока входа	
pos_out=$2  # имя файла с истиными значениями вывода
ARGS=$3     # имя файла с ключами
error_memory=0

eval "echo > temp_pos_out.txt"
if [[ -n "$USE_VALGRIND" ]]; then
    eval "valgrind --log-file=valgrind_pos.temp --tool=memcheck --leak-check=yes -q --track-origins=yes ../../app.exe $ARGS  < $pos_in > all_out.txt"
    
    if [[ -s "valgrind_pos.temp" ]]; then
        error_memory=1
    fi
else
    eval "../../app.exe $ARGS $pos_in < $pos_in > temp_pos_out.txt"
fi

if  [[ -s "temp_pos_out.txt" ]]; then
    pos_in="temp_pos_out.txt"
fi

if ./comparator.sh "$pos_in" "$pos_out"; then
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