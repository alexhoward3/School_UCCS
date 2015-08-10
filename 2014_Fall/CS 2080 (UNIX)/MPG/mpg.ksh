#!/bin/ksh

# Author: Alex Howard
# Date: 10-12-2014
# Miles per gallon calculator

args=${#}

file="./mileage"
cfile="./ControlFile"

### FILE EXISTENCE CHECK
if [ ! -f $file ]
then
	echo -e "Date\tMileage\tGallons\tMPG" > mileage
	echo "Please enter a first date and miles into the mileage file"
	exit 1
else
	echo "Found $file"
fi

if [ ! -f $cfile ]
then
	echo "Creating ControlFile"
	echo -e "Best:\t" > ControlFile
	echo -e "Dealer:\t" >> ControlFile
	echo "Please enter the Dealer MPG into the Control File"
	exit 1
else
	echo "Found $cfile"
fi

### CALCULATE MPG
if [ $args -eq 2 ]
then
	echo -e "$1\t$2" >> $file
elif [ $args -eq 3 ]
then
	dat=$(tail -n1 mileage | cut -f 2)
	mi=$(( $2 - $dat ))
	mpg=$(( $mi / $3 ))
	echo -e "$1\t$2\t\t$3\t\t$mpg" >> $file
else
	echo "Usage: mpg.ksh [date] [mileage] [gallons]"
	exit 1
fi

### FIND BEST MPG
typeset -F best=0.0
last=`expr "$*" : 'x* \(.*\)'`
touch tmp
tmp="./tmp"

cut -f 6 $file > $tmp

#cat $tmp #DEBUG

while read line
do

if [ "$line" -gt $best ]
then
	(( best = "$line" ))
fi
done < "$tmp"

del=$(tail -n1 ControlFile | cut -f 3)

echo -e "Best:\t\t$best" > $cfile
echo -e "Dealer:\t\t$del" >> $cfile

rm "./tmp"

cat mileage
cat ControlFile

exit 0
