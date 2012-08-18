#!/bin/bash
for file in `ls $1`
do
  checksum = `md5 $file`
  echo $file $checksum >> ~/Desktop/md5.txt
done
