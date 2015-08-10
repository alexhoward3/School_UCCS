#!/bin/ksh

file="grades.dat"				# Filename
total=0						# Total variable
if [ -e "$file" ]				# Check if grades file exists
then
	echo "File exists"			# Sucess message
	while read grade type			# Read each line
	do
		let total=$(($total + $grade))	# Add grade to total
	done < "$file" 				# Open the file for stdin
	<&-					# Close stdin
	echo "Total : $total of 300"		# Print the total
else
	echo "File does not exist"		# Error message
fi
