#!/bin/bash

if [ $# -ne 1 ];then 
  echo 'Incorrect arguments'
  exit 1 
fi

nums=$(ls $1 | sort -g)

for n in $nums; do
 echo "$1/$n"
done
