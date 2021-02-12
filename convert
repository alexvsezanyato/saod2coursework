declare -a names=( $(echo $(file -i * | grep -oP "(.*)(?=:)")) )
declare -a formats=( $(echo $(file -i * | grep -oP "(?<=charset=)(.*)")) )
# for i in "${names[@]}"; do echo "{$i}"; done;
# for i in "${formats[@]}"; do echo "{$i}"; done;
n=${#names[@]}
m=${#formats[@]}

if [ $n -ne $m ]; then 
	echo "Some error while reading file names and formats"
	exit 1 
fi

# prepare to convert
destination="utf-8"
if [ ! -d "${destination}" ]; then mkdir utf-8; fi

for (( i=0; i<n; i++ )); do
	if [ "${formats[i]}" == "binary" ]; then continue; fi
	iconv -f "${formats[i]}" -t "utf-8" ${names[i]} > utf-8/${names[i]}
	echo "${names[i]}: ${formats[i]} => utf-8"
done
