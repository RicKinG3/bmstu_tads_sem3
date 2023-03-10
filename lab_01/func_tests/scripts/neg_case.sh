#!/bin/bash

neg_in=$1 # имя файла для подмены потока входа
FILE_ARGS=$2

error_memory=0
# если есть глобвльная переменная USE_VALGRIND, то программа запускается под его управлением
if [[ -n "$USE_VALGRIND" ]]; then
    eval "valgrind --log-file=valgrind_pos.temp --tool=memcheck --leak-check=yes -q --track-origins=yes ../../app.exe $ARGS  < $neg_in > all_out.txt"
    if [[ -s "valgrind_neg.temp" ]]; then
        error_memory=1
    fi

  else 
    eval "../../app.exe $ARGS $neg_in < $neg_in > all_out.txt"
fi

value_return=$?

if [[ $value_return == 0 ]]; then
    if [[ $error_memory == 0 ]]; then
        exit 2 #тесты не прошли, но память прошла
    else
        exit 3 #тесты не прошли проверку, память тоже
    fi
else
    if [[ $error_memory == 0 ]]; then
        exit 0 #Все ок
    else
        exit 1 #тесты прошли проверку, память нет тоже
    fi
fi
