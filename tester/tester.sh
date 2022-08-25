#!/bin/bash

make vector namespace=std
make vector namespace=ft

listTestStd=$(echo ./.exec/std_vector/*)
listTestFt=$(echo ./.exec/ft_vector/*)

for test_file in $listTestStd; do
	valgrind $test_file 2>&1 | tail +5 | cut -d ' ' -f2- > outputs/std_vector/$(echo $test_file | cut -d '/' -f 4).output
done

for test_file in $listTestFt; do
	valgrind $test_file 2>&1 | tail +5 | cut -d ' ' -f2- > outputs/ft_vector/$(echo $test_file | cut -d '/' -f 4).output
done

listOutputStd=$(echo outputs/std_vector/*)
listOutputFt=$(echo outputs/ft_vector/*)

for i in {1..2}; do
	diff $(echo "$listOutputStd" | cut -d ' ' -f "$i") $(echo "$listOutputFt" | cut -d ' ' -f "$i")
	echo $?
done
