#!/bin/bash

if [ $# -ne 2 ];then 
  echo 'Incorrect arguments'
  exit 1 
fi

for topic in `ls $1`;do
  echo ":$topic"
  for file in `ls "$1/$topic" | head -n $2`;do
    echo "$1/$topic/$file"
  done
done

