#!/bin/bash

if [ $# -ne 1 ];then 
  echo 'Incorrect arguments'
  exit 1 
fi

qry_num=$(ls $1 | wc -l)

for (( i=1; i<=$qry_num; i++ ))
do
   echo "$1/$i"
done
