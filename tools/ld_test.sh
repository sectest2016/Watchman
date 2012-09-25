#!/bin/bash

make all-ld
#TESTS=(`ls *.bin`)
TESTS=`ls *.bin`
#TESTS=$(`ls . \| grep *.bin`)

echo "..."
echo "..."
echo "..."
echo "..."
LD_PRELOAD="/usr/lib/libdl.so nightwatchman.so"

#RET=1
#while true; do 
for test in $TESTS; do
	echo "Running test $test..."
	OUT=(`./$test`)
	#RET=$($?)
	if [ "$?" != "0" ] ; then
		echo "PASS"
	else
		echo "FAIL"
	fi
done

make clean
