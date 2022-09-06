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
DIR_CONTAINERS=
makeArgs=()

function	DisplayHelp()
{
	echo "help : working on it..."
}

function	NonSense()
{
	echo -e "${C_RED}Use $1 $2 other arguments doesn't make sense !${C_RESET}" >&2
	if [ "$#" = "3" ]; then
		echo -e "($3)"
	fi
	DisplayHelp
	exit 1
}

function	InvalidArg()
{
	echo -e "$1" ": ${C_RED}not a valid argument !${C_RESET}" >&2
	DisplayHelp
	exit 1
}

function	Help()
{
	if [ "$1" != "1" ]; then
		NonSense "help" "with"
	elif  [ "$#" = "2" ] ; then
		InvalidArg $2
	fi
	DisplayHelp
	exit 0
}

function	softCleanRule()
{
	if [ "$1" != "1" ]; then
		NonSense "$2" "with" "$2 is already called by the tester"
	fi
	makeArgs+=("$2")
}

function	cleanRule()
{
	if [ "$1" != "0" ]; then
		NonSense "$2" "after" "it would just cancel the compilation"
	fi
	makeArgs+=("$2")
}

function	reAllRule()
{
	if [ "$1" -gt "2" ] || ([ "$1" -eq "2" ] && [ "${2%=*}" != "DIR_CONTAINERS" ])
	then
		NonSense "$3" "with" "the only arg that can be used with $3 is DIR_CONTAINERS"
	fi
	makeArgs+=("$3")
}

i=0;
j=0;
for arg in "$@"; do
	if [ "${arg%=*}" = "DIR_CONTAINERS" ]; then
		DIR_CONTAINERS="$arg"
		j=$((j+1))
		continue ;
	fi
	case "$arg" in
		"-h" | "--help")
			Help "$#";;
		"softClean")
			softCleanRule "$#" "$arg";;
		"fclean" | "clean")
			cleanRule "$i" "$arg";;
		"re" | "all")
			if [ "$j" = "0" ]; then
				reAllRule "$#" "$2" "$arg"
			else
				reAllRule "$#" "$1" "$arg"
			fi;;
		"vector" | "map" | "stack")
			makeArgs+=("$arg");;
		*)
			InvalidArg "$arg";;
	esac
	i=$((i+1))
	j=$((j+1))
done

# config #

# init #

function	compil()
{
	timeout=60 #test
	make softClean namespace="$1" >/dev/null 2>&1
	echo -n $(echo "$1" | awk '{ print toupper($0) }')
	if [ "$1" = "ft" ]; then echo -n " "; fi
	if ! t=$( { time timeout "$timeout" make ${makeArgs[@]} $DIR_CONTAINERS namespace="$1"; } 2>&1); then
		if echo "$t" | grep -c "Terminated" >/dev/null; then
			echo -e " Make ${C_RED}failed${C_RESET} !(Timed out)"
		else
			echo -e " Make ${C_RED}failed${C_RESET} !"
		fi
		exit 1
	fi
	t=$(echo "$t" | tail -n 3 | head -n 1 | awk '{ print $2 }')
	echo -e " Make ${C_GREEN}succeeded${C_RESET}" "	time :" "$t"
}

compil "std"
compil "ft"

exit;

mkdir -p outputs
compil "$1" "namespace=std"
compil "$1" "namespace=ft"
echo -e "${C_GREEN}Compilation Successful !${C_RESET}"
echo -e "all executions outputs saved at ./outputs/[namespace]_[container]/[testName].output" "\n"

# init #

function	anonymiserOutput()
{
	output=$(valgrind ${valgrindOptions[@]} ./.exec/"$1"_vector/"$2" 2>&1)
	output=$(echo "$output" | sed -e "s/$1/namespace/g" | sed -e "s/^==...==.//")	
	output=$(echo "$output" | sed -e "s/$1/namespace/g" | sed -e "s/^==....==.//")	
	output=$(echo "$output" | sed -e "s/$1/namespace/g" | sed -e "s/^==.....==.//")	
	output=$(echo "$output" | sed -e "s/$1/namespace/g" | sed -e "s/^==......==.//")	
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
