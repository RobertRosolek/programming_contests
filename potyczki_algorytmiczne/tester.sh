#!/bin/bash

# Text color variables
txtund=$(tput sgr 0 1)    # Underline
txtbld=$(tput bold)       # Bold
txtred=$(tput setaf 1)    # Red
txtgrn=$(tput setaf 2)    # Green
txtylw=$(tput setaf 3)    # Yellow
txtblu=$(tput setaf 4)    # Blue
txtpur=$(tput setaf 5)    # Purple
txtcyn=$(tput setaf 6)    # Cyan
txtwht=$(tput setaf 7)    # White
txtrst=$(tput sgr0)       # Text reset

if [ $# -ne 2 ]
then
	echo "Usage: tester.sh binary folder_with_tests"
	exit 1
fi

BINARY=$1
TESTS=$2

ALL=0;
GOOD=0;

echo "$TESTS"
FILES=$TESTS/*.in
for f in $FILES
do
  echo "Test ${f%%.in}"
  ALL=`expr $ALL + 1`
  #./$BINARY <$f
  time ./$BINARY <$f >wynik.out
  if diff -w -B wynik.out ${f%%.in}.out >/dev/null; then
  	  echo "${txtgrn}OK!${txtrst}"
  	  GOOD=`expr $GOOD + 1`
  else
  	  echo "${txtred}WRONG ANSWER!${txtrst}"
  fi
done

echo "$GOOD / $ALL"
if [ $GOOD -ne $ALL ]
then
	echo "${txtred}WRONG!${txtrst}"
else
	echo "${txtgrn}OK!${txtrst}"
fi
