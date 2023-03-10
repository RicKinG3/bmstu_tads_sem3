#!/bin/bash
FIRST_FILE=$(cat "$1")
SECOND_FILE=$(cat "$2")

DATA_FIRST=${FIRST_FILE#*"Result: "}

DATA_SECOND=${SECOND_FILE#*"Result: "}

#echo "$DATA_FIRST"
#echo "))))))))"
#echo "$DATA_SECOND"

if [[ "$DATA_FIRST" == "$DATA_SECOND" ]]; then
    exit 0
else
    exit 1
fi
