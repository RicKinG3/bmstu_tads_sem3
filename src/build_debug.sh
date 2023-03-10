#!/bin/bash

gcc -std=c99 -Wall -Werror -Wextra -Wpedantic -g -Wfloat-equal -Wfloat-conversion -Wvla -c *.c  
gcc -o app.exe *.o 