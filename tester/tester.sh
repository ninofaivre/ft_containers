#!/bin/bash
# utils #
C_RESET="\e[0m"
C_PURPLE="\e[95m"
C_RED="\e[91m"
C_GREEN="\e[92m"
C_YELLOW="\e[93m"

S_RESET="\033[0m"
S_BOLD="\033[1m"

SEP="${S_BOLD}|${S_RESET}"
OK="${S_BOLD}${C_GREEN}\U2713${C_RESET}${S_RESET}"
MOK="${S_BOLD}${C_YELLOW}\U2713${C_RESET}${S_RESET}"
KO="${C_RED}\U2620${C_RESET}"
# utils #

if [ -f ".env" ]; then export "$(grep -v "^#" < .env | xargs)" &>/dev/null; fi

# config #
if [[ ! -v CCTimeOut ]]; then CCTimeOut=60; fi
if [[ ! -v maxTestNameLength ]]; then maxTestNameLength=20; fi
if [[ ! -v ExecTimeOut ]]; then ExecTimeOut=4; fi
if [[ ! -v make_j ]]; then make_j=$(nproc); fi

makeArgs=()

# config #
function	DisplayHelp()
{
	echo "help : working on it..."
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
			"CXX")
				makeArgs+=("$arg");;
			"CXXFLAGS")
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
			DisplayHelp;
			exit 0;;
		"-j"*)
			make_j="${arg#*j}";;
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
	make softClean namespace="$1" &>/dev/null
	echo -n "${1^^}"
	if [ "$1" = "ft" ]; then echo -n " "; fi
	if ! t="$( { time timeout "$CCTimeOut" make "${makeArgs[@]}" -j"$make_j" namespace="$1" &>/dev/null; } 2>&1)"; then
		if (echo "$t" | grep -c "Terminated" >/dev/null); then
			echo -e " Make ${C_RED}failed${C_RESET} !(Timed out)"
		else
			echo -e " Make ${C_RED}failed${C_RESET} !"
		fi
		exit 1
	fi
	t=$(echo "$t" | awk 'NR==2 { print $2 }')
	echo -e " Make ${C_GREEN}succeeded${C_RESET}" "	time :" "$t"
}

function pres() #subtestname #F[rawData] #S[rawData] #only_comp
{
	compRes=$(if [ "$2" = "$3" ] ; then echo "${OK}"; else echo "${KO}"; fi)
		echo -e -n "$1$compRes"
	if [ "$4" != "compact" ]; then
		echo -e -n " F[$2] S[$3]"
	fi
	echo -e -n "${SEP}"
}

function presTime()
{
	stdTime=$(awk -F'[.ms]' '{ printf("%d"), $3 }' <<< "$1")
	ftTime=$(awk -F'[.ms]' '{ printf("%d"), $3 }' <<< "$2")
	diff=$((ftTime-stdTime))
	if ((diff < 0)); then
		note=100
	elif ((diff < 5)); then
		note=100
	else
		note=$(awk -v ft="$ftTime" -v std="$stdTime" '{ printf("%3d"), 100-(ft/std*5) }' <<< "")
		if ((note < 0)) ; then note="  0"; fi
	fi
	echo -n "perf"
	if ((note == 0)); then
		echo -n -e "${KO}${C_RED}"
	elif ((note < 50)); then
		echo -n -e "${MOK}${C_YELLOW}"
	else
		echo -n -e "${OK}${C_GREEN}"
	fi
	echo -n -e " $note${C_RESET}/100${SEP}"
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
	#if !(test -f ./.exec/std_$2/$1); then
	if [[ ! -f "./.exec/std_$2/$1" ]]; then
		STD_PIDS+=("none")
		STD_COMPILS+=("N")
	else
		STD_COMPILS+=("Y")
		({ time timeout "$ExecTimeOut" ./.exec/std_"$2"/"$1" &>./outputs/std_"$2"/"$1".output; } 2>./outputs/std_"$2"/"$1".time) &
		STD_PIDS+=("$!")
	fi
	if [[ ! -f "./.exec/ft_$2/$1" ]]; then
		FT_PIDS+=("none")
		FT_COMPILS+=("N")
	else
		FT_COMPILS+=("Y")
		({ time timeout "$ExecTimeOut" ./.exec/ft_"$2"/"$1" &>./outputs/ft_"$2"/"$1".output; } 2>./outputs/ft_"$2"/"$1".time) &
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
	for name in "${TESTS[@]}"; do
		OneTest "$name" "$1"
	done
	for i in "${!TESTS[@]}"; do
		pid="${STD_PIDS[${i}]}"
		timepath="./outputs/std_${1}/${TESTS[${i}]}.time"
		if [ "$pid" = "none" ]; then
			STD_RETURNS+=("none")
			STD_TIMES+=("none")
		else
			wait "$pid"; STD_RETURNS+=("$?"); STD_TIMES+=("$(awk 'NR==2 { print $2 }' < "$timepath")"); rm "$timepath"
		fi
		pid="${FT_PIDS[${i}]}"
		timepath="./outputs/ft_${1}/${TESTS[${i}]}.time"
		if [ "$pid" = "none" ]; then
			FT_RETURNS+=("none")
			FT_TIMES+=("none")
		else
			wait "$pid"; FT_RETURNS+=("$?"); FT_TIMES+=("$(awk 'NR==2 { print $2 }' < "$timepath")"); rm "$timepath"
		fi
	done
}

function	displayTest() #testID #ContainerName
{
	if [ "${FT_COMPILS[${1}]}" = "Y" ] && [ "${STD_COMPILS[${1}]}" = "Y" ]; then
		cmp ./outputs/std_"$2"/"${TESTS[${1}]}".output ./outputs/ft_"$2"/"${TESTS[${1}]}".output &>/dev/null; diffOutput=$?
	fi
	awk -v name="${TESTS[${1}]}" -v maxNameLen="$maxTestNameLength"\
		'{ nameLen = length(name) ; te = nameLen <= maxNameLen;
		printf("%s%"te * (maxNameLen - nameLen)"s%s", substr(name, 1, maxNameLen - !te), "", substr(". ", 1 + te, 2)); }' <<< ""
	echo -n -e "$SEP"
	pres "CC" "${FT_COMPILS[${1}]}" "${STD_COMPILS[${1}]}" "full"
	if [ "${STD_RETURNS[${1}]}" = "124" ]; then
		echo -e "${C_RED}STD Timed Out${C_RESET}"
		return ;
	elif [ "${FT_RETURNS[${1}]}" = "124" ]; then
		echo -e "${C_RED}FT Timed Out ${C_RESET}"
		return ;
	fi
	if [ "${FT_COMPILS[${1}]}" = "N" ] && [ "${STD_COMPILS[${1}]}" = "Y" ]; then
		echo -e "${C_RED} FT shall CC ${C_RESET}"
		return ;
	elif [ "${FT_COMPILS[${1}]}" = "Y" ] && [ "${STD_COMPILS[${1}]}" = "N" ]; then
		echo -e "${C_RED}FT shallnt CC${C_RESET}"
		return ;
	elif [ "${FT_COMPILS[${1}]}" = "N" ] && [ "${STD_COMPILS[${1}]}" = "N" ]; then
		echo -e "${C_GREEN}CC fail test${C_RESET}"
		return ;
	fi
	pres "Out" "0" "$diffOutput" "compact"
	pres "Ret" "${FT_RETURNS[${1}]}" "${STD_RETURNS[${1}]}" "compact"
	presTime "${STD_TIMES[${1}]}" "${FT_TIMES[${1}]}"
	echo
}

function	oneContainer()
{
	if [ "$(ls ./tests/"$1"/*.cpp 2>/dev/null)" == "" ]; then
		return ;
	elif [[ "${makeArgs[*]}" != *"all"* ]] && [[ "${makeArgs[*]}" != *"re"* ]] && [[ "${makeArgs[*]}" != *"$1"* ]]; then
		return ;
	fi
	exe "$1"
	echo
	echo -e "TEST OF" "${C_PURPLE}${1^^}${C_RESET}" ":"
	echo
	for i in "${!TESTS[@]}"; do
		displayTest "$i" "$1"
	done
}

compil "std"
compil "ft"

oneContainer "vector"
oneContainer "stack"
oneContainer "map"
