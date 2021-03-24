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
# sources+=('Print')
sources+=('App')
sources+=('Database')
sources+=('Database.BinarySearch')
sources+=('Database.QuickSort')
# sources+=('Fano')
# sources+=('Stree')
# sources+=('Btree-fixed')
sources+=('Shanon')
sources+=('DataStructs')
# sources+=('Tree')

for i in "${dirs[@]}"; do
	if [ ! -d $i ]; then
		mkdir $i
	fi
done

# main object file
# ${compiler} -c -std=${version}  "${main}.cpp"

for i in "${sources[@]}"; do
	# object files
	source="${i}.${exts[src]}"

	if [ ! -f "${source}" ]; then
		echo "The file \"${source}\" doesn't exist"
		continue
	fi

	${compiler} -c -std=${version} "${source}" \
		 -o "${dirs[obj]}/${i}.${exts[obj]}" || exit 1
done

# executable
declare -a objects=()

for i in "${sources[@]}"; do
	objects+=("${dirs[obj]}/${i}.${exts[obj]}")
done

${compiler} -std=${version} ${objects[@]} -o "${dirs[bin]}/${appName}" || exit 1
unset exts[@]
unset dirs[@]
unset sources[@]
exit 0
