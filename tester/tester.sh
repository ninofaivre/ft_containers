#!/bin/bash
# utils #
C_RESET="\e[0m"
C_PURPLE="\e[94m"
C_RED="\e[91m"
C_GREEN="\e[92m"

S_RESET="\033[0m"
S_BOLD="\033[1m"

OK="${S_BOLD}${C_GREEN}\U2713${C_RESET}${S_RESET}"
KO="${C_RED}\U2620${C_RESET}"
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
				CCTimeOut=${arg#*=};;
			"ExecTimeOut")
				ExecTimeOut=${arg#*=};;
			"maxTestNameLength")
				maxTestNameLength=${arg#*=};;
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
		echo -e -n "$1$compRes"
	if [ "$4" != "compact" ]; then
		echo -e -n " F[$2] S[$3]"
	fi
	echo -n "|"
}

function presTime()
{
	#echo -n "$1|$2"
	stdTime=$(echo $1 | awk -F'[.ms]' '{ print $3 }' | sed -e 's/00//')
	ftTime=$(echo $2 | awk -F'[.ms]' '{ print $3 }' | sed -e 's/00//')
	diff=$((stdTime-ftTime))
	if (( "$diff" <= "2" )) && (( "$diff" >= "-2" )); then
		stdTime="$ftTime"
	fi
	echo -n "Time" $(echo | awk -v ft=$ftTime -v std=$stdTime '{ print ft/std*100-100 "%" }')"	|"
	#echo -n $(( ((ftTime / stdTime) * 100) + (ftTime % stdTime) -100 ))"%"
}

TESTS=()

STD_RETURNS=()
STD_PIDS=()
STD_COMPILS=()
STD_TIMES=()

FT_RETURNS=()
FT_PIDS=()
FT_COMPILS=()
FT_TIMES=()

function	OneTest()
{
	if [ "$(test -f ./.exec/std_$2/$1 && echo Y || echo N)" = "N" ]; then
		STD_PIDS+=("none")
		STD_COMPILS+=("N")
	else
		STD_COMPILS+=("Y")
		({ time timeout "$ExecTimeOut" ./.exec/std_"$2"/"$1" >./outputs/std_"$2"/"$1".output 2>&1; } > ./outputs/std_"$2"/"$1".time 2>&1) &
		STD_PIDS+=("$!")
	fi
	if [ "$(test -f ./.exec/ft_$2/$1 && echo Y || echo N)" = "N" ]; then
		FT_PIDS+=("none")
		FT_COMPILS+=("N")
	else
		FT_COMPILS+=("Y")
		({ time timeout "$ExecTimeOut" ./.exec/ft_"$2"/"$1" >./outputs/ft_"$2"/"$1".output 2>&1; } > ./outputs/ft_"$2"/"$1".time 2>&1) &
		FT_PIDS+=("$!")
	fi
}

function	exe()
{
	#resetArray
	TESTS=()

	STD_RETURNS=()
	STD_PIDS=()
	STD_COMPILS=()
	STD_TIMES=()

	FT_RETURNS=()
	FT_PIDS=()
	FT_COMPILS=()
	FT_TIMES=()

	for name in $(basename -a -s .cpp ./tests/"$1"/*.cpp); do TESTS+=("$name"); done
	for name in ${TESTS[@]}; do
		OneTest "$name" "$1"
	done
	for i in ${!TESTS[@]}; do
		pid="${STD_PIDS[${i}]}"
		timepath="./outputs/std_"$1"/${TESTS[${i}]}.time"
		if [ "$pid" = "none" ]; then
			STD_RETURNS+=("none")
			STD_TIMES+=("none")
		else
			wait "$pid"; STD_RETURNS+=("$?"); STD_TIMES+=("$(cat $timepath | awk 'NR==2 { print $2 }')"); rm "$timepath"
		fi
		pid="${FT_PIDS[${i}]}"
		timepath="./outputs/ft_"$1"/${TESTS[${i}]}.time"
		if [ "$pid" = "none" ]; then
			FT_RETURNS+=("none")
			FT_TIMES+=("none")
		else
			wait "$pid"; FT_RETURNS+=("$?"); FT_TIMES+=("$(cat $timepath | awk 'NR==2 { print $2 }')"); rm "$timepath"
		fi
	done
}

function	displayTest() #testID #ContainerName
{
	if ([ "${FT_COMPILS[${1}]}" = "Y" ] && [ "${STD_COMPILS[${1}]}" = "Y" ]); then
		sameOutput=$(diff -q ./outputs/std_"$2"/"${TESTS[${1}]}".output ./outputs/ft_"$2"/"${TESTS[${1}]}".output >/dev/null && echo 1 || echo 0)
	fi
	
	echo -n "$(echo | awk -v testName=${TESTS[${1}]} -v maxTestNameLength=$maxTestNameLength -v testNameLength=${#TESTS[${1}]} '{ printf("%s%"maxTestNameLength-testNameLength"s\n", substr(testName, 1, maxTestNameLength), "") ; }')""|"
	pres "CC" "${FT_COMPILS[${1}]}" "${STD_COMPILS[${1}]}" "full"
	if [ "${STD_RETURNS[${1}]}" = "124" ]; then
		echo -e "${C_RED}STD Timed Out${C_RESET}|"
		return ;
	elif [ "${FT_RETURNS[${1}]}" = "124" ]; then
		echo -e "${C_RED}FT Timed Out ${C_RESET}|"
		return ;
	fi
	if ([ "${FT_COMPILS[${1}]}" = "N" ] && [ "${STD_COMPILS[${1}]}" = "Y" ]); then
		echo -e "${C_RED} FT shall CC ${C_RESET}|"
		return ;
	elif ([ "${FT_COMPILS[${1}]}" = "Y" ] && [ "${STD_COMPILS[${1}]}" = "N" ]); then
		echo -e "${C_RED}FT shallnt CC${C_RESET}|"
		return ;
	elif ([ "${FT_COMPILS[${1}]}" = "N" ] && [ "${STD_COMPILS[${1}]}" = "N" ]); then
		echo -e "${C_GREEN}CC fail test ${C_RESET}|"
		return ;
	fi
	pres "Out" "1" "$sameOutput" "compact"
	pres "Ret" "${FT_RETURNS[${1}]}" "${STD_RETURNS[${1}]}" "compact"
	presTime "${STD_TIMES[${1}]}" "${FT_TIMES[${1}]}"
	echo
}

function	oneContainer()
{
	if [ "$(ls ./tests/"$1"/*.cpp 2>/dev/null)" == "" ]; then
		return ;
	elif ([[ "${makeArgs[@]}" != *"all"* ]] && [[ "${makeArgs[@]}" != *"re"* ]] && [[ "${makeArgs[@]}" != *"$1"* ]]); then
		return ;
	fi
	exe "$1"
	echo
	echo "TEST OF" $(echo | awk "{ print toupper(\"$1\") }") ":"
	echo
	for i in ${!TESTS[@]}; do
		displayTest "$i" "$1"
	done
}

compil "std"
compil "ft"

oneContainer "vector"
oneContainer "stack"
oneContainer "map"
