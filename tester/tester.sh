#!/bin/bash

# utils #

#OK="\U2705"
#KO="\U274C"

C_RESET="\e[0m"
C_PURPLE="\e[34m"
C_RED="\e[31m"
C_GREEN="\e[32m"

# utils #

# config #

valgrindOptions=("--track-origins=yes" "-s")

# config #

# init #

function	compil()
{
	echo "\"make $1 $2\" :" > outputs/compiling.output
	# shellcheck disable=SC2086
	if ! make $1 $2 >> outputs/compiling.output 2>&1; then
		echo -e "${C_RED}Compilation Failed !${C_RESET}"
		echo -e "output saved in ./outputs/compiling.output"
		exit 1
	fi
}

mkdir -p outputs
compil "$1" "namespace=std"
compil "$1" "namespace=ft"
echo -e "${C_GREEN}Compilation Successful !${C_RESET}"
echo -e "all executions outputs saved at ./outputs/[namespace]_[container]/[testName].output" "\n"

# init #

function	anonymiserOutput()
{
	output=$(valgrind ${valgrindOptions[@]} ./.exec/"$1"_vector/"$2" 2>&1)
	output=$(echo "$output" | sed -e "s/$1/namespace/g" | sed -e "s/^==.....==.//")	
	echo "$output" > outputs/"$1"_vector/"$2".output
	return $(( $(echo "$output" | awk 'END { print $3 }') != 0 ))
}

workingTest=0

mkdir -p outputs/std_vector
mkdir -p outputs/ft_vector
for test_file in $(cd ./.exec/std_vector/ || exit; echo *); do
	echo -n "[$test_file] : "
	if anonymiserOutput "std" "$test_file"; then
		echo -e -n "${C_GREEN}no val errors${C_RESET}";
	else
		echo -e -n "${C_RED}val errors${C_RESET}";
	fi
	echo -n " | "
	if anonymiserOutput "ft" "$test_file"; then
		echo -e -n "${C_GREEN}no val errors${C_RESET}";
	else
		echo -e -n "${C_RED}val errors${C_RESET}";
	fi
	echo -n " -> "
	if ! diff "outputs/std_vector/$test_file.output" "outputs/ft_vector/$test_file.output" > /dev/null; then
		echo -e "${C_RED}DIFF${C_RESET}erences beetween STD and FT"
	else
		(( workingTest=workingTest+1 ))
		echo -e "${C_GREEN}NO DIFF${C_RESET}erences beetween STD and FT"
	fi
done

echo -e "\n" "${C_PURPLE}FINAL GRADE : $workingTest/$(cd ./.exec/std_vector/ || exit; echo * | wc -w)${C_RESET}"
