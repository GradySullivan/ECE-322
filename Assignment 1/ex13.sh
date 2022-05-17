#!/bin/bash

# Filename: ex13.sh
#
# Problem: Add writing to an array and reading from the array.

#echo Please type in 3 foods you like:
#for xx in `seq 1 3`; do
#	read array
#done

#PS3='Now Select the food you like the best: '
#select option in array
#do
#  echo "The option you have selected is: $option"
#  break
#done

echo Please type in 3 foods you like:
for xx in `seq 1 3`; do				
	read array[$xx]	
		
done


PS3='Now Select the food you like the best: '
select option in ${array[1]} ${array[2]} ${array[3]}
do
  echo "The option you have selected is: $option"
  break
done
