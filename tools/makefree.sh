#!/bin/sh
#XXX generate a tool that deletes all non-gnu code from this project
#this prepares the project for the gnu release
rm ./paid_*
rm ./*/paid_*
rm readme
rm Makefile
mv freeMakefile Makefile

LICENSE=$(echo license)

FILES=$(echo *.h)

#TODO add ability to select watchman features as command arguments
for file in $FILES
    do
        echo "Patching $file with Watchman"

        mv $file $file.tmp
        sed '1i\
$LICENSE' $file.tmp > $file 
	rm $file.tmp
done
