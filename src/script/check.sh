#!/bin/bash

if [ $# -ne 2 ];then 
  echo 'Incorrect arguments'
  exit 1 
fi

error=`diff $1 $2 | grep '^>' | wc -l`
all=`cat $1 | wc -l`
correct=$(($all-$error))
acc=`echo "scale=4;$correct/$all*100.0" | bc`
echo "Correct: $correct/$all"
echo "Accuracy: $acc%"
