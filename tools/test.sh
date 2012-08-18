#!/bin/sh
RET=1
while true; do 
	OUT=$(./a.out < input2 &2>1)
	#RET=$($?)
	if [ "$?" = "0" ] ; then
		echo $OUT
	fi
done
