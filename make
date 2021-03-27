#!/bin/bash

# sets
compiler=g++
version=c++2a
appName=coursework

#exts
declare -A exts=()
exts['obj']=obj
exts['src']=cpp
exts['bin']=out

# dirs
declare -A dirs=()
dirs['obj']=obj
dirs['src']=src
dirs['bin']=bin

# sources
main=coursework
declare -a sources=()

sources+=($main)
sources+=('App')
sources+=('Database')
sources+=('Database.BinarySearch')
sources+=('Database.QuickSort')
sources+=('Shanon')
sources+=('DataStructs')

for i in "${dirs[@]}"; do
	if [ ! -d $i ]; then
		mkdir $i
	fi
done

# main object file
# ${compiler} -c -std=${version}  "${main}.cpp"
date="date --debug +%Y%m%d%H%M%S -r"

for i in "${sources[@]}"; do
	# object files
	source="${i}.${exts[src]}"
    object="${dirs[obj]}/${i}.${exts[obj]}"

	if [ ! -f "${source}" ]; then
		echo "The file \"${source}\" doesn't exist"
		continue
    elif [ $(${date} ${source}) -lt $(${date} ${object}) ]; then
        # already is up to date
        if [ "${1}" != "-a" ]; then continue; fi
	fi

	${compiler} -c -std=${version} "${source}" \
		 -o "${dirs[obj]}/${i}.${exts[obj]}" || exit 1
done

# executable
declare -a objects=()

for i in "${sources[@]}"; do
	objects+=("${dirs[obj]}/${i}.${exts[obj]}")
done

# compile
${compiler} -std=${version} ${objects[@]} -o "${dirs[bin]}/${appName}" || exit 1

# link to binary
if [ -f "${dirs['bin']}/${main}" ]; then
 	rm "${main}"
	ln "${dirs['bin']}/${main}" "${main}"
fi

unset exts[@]
unset dirs[@]
unset sources[@]
exit 0
