#!/bin/bash

if [ $# -ne 2 ];then 
  echo 'Incorrect arguments'
  exit 1 
fi

error=`diff $1 $2 | grep '^>' | wc -l`
all=`cat $1 | wc -l`
error_rate=`echo "scale=4;$error/$all*100.0" | bc`
echo "Wrong: $error/$all"
echo "Error rate: $error_rate%"
