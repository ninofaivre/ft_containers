#!/bin/bash

# utils #

OK="\U2705"
KO="\U274C"

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
	t=$(echo "$t" | tail -n 3 | awk 'NR==1 { print $2 }')
	echo -e " Make ${C_GREEN}succeeded${C_RESET}" "	time :" "$t"
}

function pres() #subtestname #F[rawData] #S[rawData] #only_comp
{
	compRes=$(if [ "$2" = "$3" ] ; then echo ${OK}; else echo ${KO}; fi)
		echo -e -n "$1 $compRes"
	if [ "$4" != "compact" ]; then
		echo -e -n "F[$2] S[$3]"
	fi
	echo -n "|"
}

function	oneTest() #testName #ContainerName
{
	timeout=2
	maxTestNameLength=20

	stdCompil=$(test -f ./.exec/std_"$2"/"$1" && echo Y || echo N)
	if [ "$stdCompil" = "Y" ]; then
		stdTime=$({ time timeout "$timeout" ./.exec/std_"$2"/"$1" >./outputs/std_"$2"/"$1".output 2>&1; } 2>&1)
		stdReturn=$?
		stdTime=$(echo "$stdTime" | awk 'NR==1 { print $2 }')
	fi

	ftCompil=$(test -f ./.exec/ft_"$2"/"$1" && echo Y || echo N)
	if [ "$ftCompil" = "Y" ]; then
		ftTime=$({ time timeout "$timeout" ./.exec/ft_"$2"/"$1" >./outputs/ft_"$2"/"$1".output 2>&1; } 2>&1)
		ftReturn=$?
		ftTime=$(echo "$ftTime" | awk 'NR==1 { print $2 }')
	fi

	if ([ "$ftCompil" = "Y" ] && [ "$stdCompil" = "Y" ]); then
		sameOutput=$(diff -q ./outputs/std_"$2"/"$1".output ./outputs/ft_"$2"/"$1".output >/dev/null && echo 1 || echo 0)
	fi
	
	echo -n $(echo | awk "{ print substr(\"$1\", 1, $maxTestNameLength); print substr(\"..................\", 1, $maxTestNameLength - ${#1}); }")"|"
	pres "CC" "$ftCompil" "$stdCompil" "full"
	if [ "$stdReturn" = "124" ]; then
		echo -e "${C_RED}STD Timed Out${C_RESET}|"
		return ;
	elif [ "$ftReturn" = "124" ]; then
		echo -e "${C_RED}FT Timed Out ${C_RESET}|"
		return ;
	fi
	if ([ "$ftCompil" = "N" ] && [ "$stdCompil" = "Y" ]); then
		echo -e "${C_RED} FT shall CC ${C_RESET}|"
		return ;
	elif ([ "$stdCompil" = "N" ] && [ "$ftCompil" = "Y" ]); then
		echo -e "${C_RED}FT shallnt CC${C_RESET}|"
		return ;
	elif ([ "$stdCompil" = "N" ] && [ "$ftCompil" = "N" ]); then
		echo -e "${C_GREEN}CC fail test ${C_RESET}|"
		return ;
	fi
	pres "Out" "1" "$sameOutput" "compact"
	pres "Ret" "$ftReturn" "$stdReturn" "compact"
	echo

}

function	oneContainer()
{
	echo "TEST OF" $(echo | awk "{ print toupper(\"$1\") }") ":"
	echo
	testNameList=$(basename -a -s .cpp ./tests/"$1"/*.cpp)
	for name in $testNameList; do
		oneTest "$name" "$1"
	done
}

compil "std"
compil "ft"

echo
oneContainer "vector"
