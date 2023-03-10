#!/bin/bash
FIRST_FILE=$1
SECOND_FILE=$2

DATA_FIRST=`cat $FIRST_FILE`
DATA_SECOND=`cat $SECOND_FILE`

if [[ "$DATA_FIRST" == "$DATA_SECOND" ]]; then
    exit 0

else
    exit 1
fi

