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

: <<'END_OF_DOCS'
Convert Delimiters script is used to convert the source file with a specific input based record delimiter to a destination file with a specific input based record delimiter.

=head1 NAME
	bash_convert_delimiter

=head1 SYNOPSIS
	bash_convert_delimiter SOURCE_DELIMITER DEST_DELIMITER SOURCE_FILE DEST_FILE

=head1 OPTIONS
	First argument: Source file delimiter
	Second argument: Destination file delimiter
	Third argument: Source file path and name
	Fourth argument: Destination file path and name

=head1 DESCRIPTION
	So far we have covered the following delimiters implementation
	1) Comma
	2) Space

=head1 LICENSE AND COPYRIGHT

=cut
END_OF_DOCS
