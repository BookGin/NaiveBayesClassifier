#!/bin/bash

for topic in `ls $1`;do
  echo ":$topic"
  if [ "$2" == "" ]; then
    for file in `ls "$1/$topic"`;do
      echo "$1/$topic/$file"
    done
  else
    for file in `ls "$1/$topic" | head -n $2`;do
      echo "$1/$topic/$file"
    done
  fi
done

