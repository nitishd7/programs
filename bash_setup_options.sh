set -o noclobber

if [[ $(echo $PATH| grep $1) != $PATH ]];
then
	PATH+=$1
fi
echo $PATH
