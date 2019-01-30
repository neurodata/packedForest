#!/bin/bash

if [ -f error.log ]; then
	rm error.log
fi

for i in `seq 1 2`;
do
	./bin/fp $i 6 1 > garbage.out
	if [ $? -ne 0 ]
	then
		echo $i $q $j 2> error.log
	fi
	printf "\n"
done

rm garbage.out

if [ -f error.log ]; then
	echo "errors were found"	
else
	./res/showRes.sh
fi



