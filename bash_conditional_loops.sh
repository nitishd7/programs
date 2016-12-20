
LIST=("Add" "Subtract" "Multiply" "Divide" "Power")

select OP in ${LIST}
do
	read -p "Enter two numbers" A B
	case $OP in
		"Add")  echo "Add"
			echo $(( $A + $B ))
			;;
		"Subtract") echo "Subtract"
			echo $(( $A - $B ))
			;;
		"Multiply") echo $(( $A * $B ))
			;;
		"Divide") echo $(( $A / $B ))
			;;
		"Power") echo $(( $A ** $B ))
			;;
		*) ;;
	esac
done
