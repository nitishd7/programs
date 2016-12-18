#!/bin/bash
replace_regex="s/"

#$1 : boolean for source, $2: source delimiter
make_regex(){
	if [ "$1" == "true" ];
	then
		replace_regex+="$2";
		echo $replace_string
	else
		replace_regex+="/$2/g";
		echo $replace_string
	fi	
}

if [[ "$1" == "comma" ]];
then
	make_regex true ",";
elif [[ "$1" == "space" ]];
then
	make_regex true " ";
else
	echo "source unknown"
fi



if [[ "$2" == "comma" ]];
then
	make_regex false ",";
elif [[ "$2" == "space" ]];
then
	make_regex false " ";
else
	echo "destination unknonw"
fi

echo "sed $replace_regex $3 > $4"
sed "$replace_regex" $3 >| $4
