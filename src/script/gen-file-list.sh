#!/bin/bash

if [ $# -ne 1 ];then 
  echo 'Incorrect arguments'
  exit 1 
fi

for topic in `ls $1`;do
  echo ":$topic"
  for file in `ls "$1/$topic"`;do
    echo "$1/$topic/$file"
  done
done

