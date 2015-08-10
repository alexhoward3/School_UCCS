#!/bin/csh

# Alex Howard
# 10-15-2014
# Gas Pump
# pump.csh

alias MATH 'set \!:1 = `echo "\!:3-$" | bc -l`'

if($#argv != 5) then
	echo "Usage: pump.csh [ccn] [name] [pump] [product] [gallons]"
	exit 1;
else

set ccn=$argv[1]
set name=$argv[2]
set pump=$argv[3]
set sel=$argv[4]
set gal=$argv[5]
	if( $sel == "U" ) then
		set typ="Unleaded"
		set ppg=`cat ControlFile | grep "U" | cut -f2`
	else if( $sel == "P" ) then
		set typ="Plus"
		set ppg=`cat ControlFile | grep "P" | cut -f2`
	else if( $sel == "R" ) then
		set typ="Premium"
		set ppg=`cat ControlFile | grep "R" | cut -f2`
else
	echo "Really Bad Error"
	exit 1;
endif

set dlr='$'

###FORMATTING
echo "\t\tWelcome"
echo "Exxon"
echo "333 Main St"
echo "Colorado Springs\tCO 80918"
echo ""
echo "DATE \t`date +%H:%M:%S`"
echo "TIME \t`date +%D`"
echo ""
echo "CCN: XXXX XXXX XXXX $ccn"
echo "Name: $name"
printf "Pump\tProduct\t\tPPG\n"
if ($typ == "U") then
	printf "$pump\t$typ$dlr$ppg\n"
else
	printf "$pump\t$typ\t\t$dlr$ppg\n"
endif
printf "Gallons\t\tTotal\n"
MATH total = $ppg * $gal
printf "$gal\t\t%s%.2f\n" $dlr $total

exit 0
