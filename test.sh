#!/bin/bash

EXECUTABLE="$1"
DIRECTORY="$2"

echo "Test poprawnościowy"
for file in "${DIRECTORY}"/*.in
do
    OUT=$(mktemp)
    ERR=$(mktemp)
    
    ./"${EXECUTABLE}" < "${file}" > $OUT 2> $ERR
    
    if diff $OUT "${file%.in}.out" > /dev/null && diff $ERR "${file%.in}.err" > /dev/null
    then
        echo -e "\e[1;42m OK \e[0m - ${file%.in}"
    else
        echo -e "\e[1;41m ERR \e[0m - ${file%.in}"
    fi
    rm $OUT $ERR
done

echo "Test pamięciowy (valgrind)"
for file in "${DIRECTORY}"/*.in
do
    ERR=$(mktemp)
    LOG=$(mktemp)
    
    valgrind --error-exitcode=123 --leak-check=full --show-leak-kinds=all --log-file="${LOG}" --errors-for-leak-kinds=all -q\
    ./"${EXECUTABLE}" < "${file}" > /dev/null 2> /dev/null
    
    if [ $? -eq 123 ]
    then
        echo -e "\e[1;41m ERR \e[0m - ${file%.in}"
        cat $LOG
    else 
        echo -e "\e[1;42m OK \e[0m - ${file%.in}"
    fi
    rm $ERR $LOG
done