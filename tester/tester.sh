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
CCTimeOut=60

ExecTimeOut=2
maxTestNameLength=20

valgrindOptions=("--track-origins=yes" "-s")
makeArgs=()
# config #
function	DisplayHelp()
{
	echo "help : working on it..."
	exit 0
}

function	InvalidArg()
{
	echo -e "$1" ": ${C_RED}not a valid argument !${C_RESET}" >&2
	DisplayHelp
	exit 1
}
# parse #
for arg in "$@"; do
	if [[ "$arg" == *"="* ]]; then
		case "${arg%=*}" in
			"DIR_CONTAINERS")
				makeArgs+=("$arg");;
			"CCTimeOut")
				CCTimeOut=${arg#=*};;
			"ExecTimeOut")
				ExecTimeOut=${arg#=*};;
			"maxTestNameLength")
				maxTestNameLength=${arg#=*};;
			*)
				InvalidArg "$arg";;
		esac
		continue ;
	fi
	case "$arg" in
		"-h" | "--help")
			DisplayHelp;;
		"softClean" | "fclean" | "clean")
			makeArgs+=("$arg");;
		"re" | "all")
			makeArgs+=("$arg");;
		"vector" | "map" | "stack")
			makeArgs+=("$arg");;
		*)
			InvalidArg "$arg";;
	esac
done
if [ "${#makeArgs}" = "0" ]; then
	makeArgs+=("all")
fi
# parse #
function	compil()
{
	make softClean namespace="$1" >/dev/null 2>&1
	echo -n $(echo "$1" | awk '{ print toupper($0) }')
	if [ "$1" = "ft" ]; then echo -n " "; fi
	if ! t=$( { time timeout "$CCTimeOut" make ${makeArgs[@]} namespace="$1"; } 2>&1); then
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
	stdCompil=$(test -f ./.exec/std_"$2"/"$1" && echo Y || echo N)
	if [ "$stdCompil" = "Y" ]; then
		stdTime=$({ time timeout "$ExecTimeOut" ./.exec/std_"$2"/"$1" >./outputs/std_"$2"/"$1".output 2>&1; } 2>&1)
		stdReturn=$?
		stdTime=$(echo "$stdTime" | awk 'NR==1 { print $2 }')
	fi

	ftCompil=$(test -f ./.exec/ft_"$2"/"$1" && echo Y || echo N)
	if [ "$ftCompil" = "Y" ]; then
		ftTime=$({ time timeout "$ExecTimeOut" ./.exec/ft_"$2"/"$1" >./outputs/ft_"$2"/"$1".output 2>&1; } 2>&1)
		ftReturn=$?
		ftTime=$(echo "$ftTime" | awk 'NR==1 { print $2 }')
	fi

	if ([ "$ftCompil" = "Y" ] && [ "$stdCompil" = "Y" ]); then
		sameOutput=$(diff -q ./outputs/std_"$2"/"$1".output ./outputs/ft_"$2"/"$1".output >/dev/null && echo 1 || echo 0)
	fi
	
	echo -n $(echo | awk "{ print substr(\"$1\", 1, $maxTestNameLength) substr(\"..................\", 1, $maxTestNameLength - ${#1}); }")"|"
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
	if [ "$(ls ./tests/"$1"/*.cpp 2>/dev/null)" == "" ]; then
		return ;
	elif ([[ "${makeArgs[@]}" != *"all"* ]] && [[ "${makeArgs[@]}" != *"re"* ]] && [[ "${makeArgs[@]}" != *"$1"* ]]); then
		return ;
	fi
	echo
	echo "TEST OF" $(echo | awk "{ print toupper(\"$1\") }") ":"
	echo
	testNameList=$(basename -a -s .cpp ./tests/"$1"/*.cpp)
	for name in $testNameList; do
		oneTest "$name" "$1"
	done
}

compil "std"
compil "ft"

oneContainer "vector"
oneContainer "stack"
oneContainer "map"
