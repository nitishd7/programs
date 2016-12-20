
SIZE=${1:?"Error. Insufficient arguments, input size"}

echo " --------------Find files recursively that are greater than given size in MB -------------------- "
find . -type f -size +${SIZE}M

echo
echo " -------------Sort files in the directory by size -------------- "
ls -lhS
