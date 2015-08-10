#!/bin/ksh

file="grades.dat"					# Filename
total=0							# Total variable
set -A arr 0 0 0					# Array of [Assignments] [Labs] [Exams]
if [ -e "$file" ]					# Check if grades file exists
then
	# echo "File exists"				# Sucess message # DEBUG
	while read grade type				# Read each line
	do
		let total=$(($total + $grade))		# Add grade to total
		if [ $type = "assignment" ]; then
			arr[0]=$((${arr[0]} + $grade))	# Add grade to array of Assignments
		elif [ $type = "lab" ]; then
			arr[1]=$((${arr[1]} + $grade))	# Add grade to array of Labs
		elif [ $type = "exam" ]; then
			arr[2]=$((${arr[2]} + $grade))	# Add grade to array of Exams
		else
			echo "Not found"
		fi
	done < "$file" 				# Open the file for stdin
	<&-					# Close stdin
	echo "Labs : ${arr[1]}"			# Print the labs
	echo "Assignments : ${arr[0]}"		# Print the assignments
	echo "Exams : ${arr[2]}"		# Print the exams
	echo "Total : $total of 300"		# Print the total
else
	echo "File does not exist"		# Error message
fi
