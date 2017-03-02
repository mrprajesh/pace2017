#!/bin/bash
#
###################
FOLDER=./instances
# without slash at the end! PLEASE!!
################### 
g++ -std=c++11 Minfill_Ordering.cpp -o Minfill_Ordering
EXECUTABLE=./Minfill_Ordering
for grfile in $FOLDER/*.graph;
do
	echo $grfile | cut -d'/' -f3
	$EXECUTABLE < $grfile	
done
