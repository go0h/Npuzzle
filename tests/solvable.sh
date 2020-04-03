#!/bin/bash

PROG="../debug/Npuzzle"
GENERATOR="res_npuzzle-gen.py"

if [ -z "$1" ] ; then
	echo "Usage: solvable.sh num_tests size [-u]"
	exit 1
fi

if [ -z "$2" ] ; then
	echo "Usage: solvable.sh num_tests size [-u]"
	exit 1
fi

if [ ! -f "$PROG" ]; then
	echo "File $PROG does not exist"
	exit 1
fi

if [ ! -f "$GENERATOR" ]; then
	echo "File $GENERATOR does not exist"
	exit 1
fi

if [ $# \> 2 ] && [ "$3" == "-u" ] ; then
	SOLVABLE="-u"
else
	SOLVABLE="-s"
fi

GREEN="\e[32m"
RED="\e[31m"
YELLOW="\e[1;33m"
EOC="\e[0m"


TOTAL=0
for (( i=0; i < $1; i++ ))
do
	python $GENERATOR $SOLVABLE $2 > test_file
	FILE=$(head --lines 1 test_file | awk '{print $5}')
	RES=$($PROG test_file  | awk '{print $2}')

	printf "Test #${i}. ${FILE} == ${RES} "
	if [ $FILE == $RES ] ; then
		TOTAL=$((TOTAL + 1))
		printf "${GREEN}GOOD${EOC}\n"
	else
		printf  "${RED}BAD${EOC}\n"
	fi
done

if [ $TOTAL == $1 ] ; then
	printf "${GREEN}Total: GOOD!!! ${TOTAL}/${1}${EOC}\n"
else
	printf  "${RED}Total: BAD!!! ${TOTAL}/${1}${EOC}\n"
fi

rm -rf test_file
