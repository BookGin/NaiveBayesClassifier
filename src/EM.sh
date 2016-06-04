#!/bin/sh

# A POSIX variable
OPTIND=1         # Reset in case getopts has been used previously in the shell.

# Initialize our own variables:
data_dir=""
output_file=""
label_size=""

while getopts "n:i:o:" opt; do
    case "$opt" in
    n)  label_size=$OPTARG
        ;;
    i)  data_dir=$OPTARG
        ;;
    o)  output_file=$OPTARG
        ;;
    esac
done

shift $((OPTIND-1))

[ "$1" = "--" ] && shift

echo "data_dir='$data_dir', output_file='$output_file', label_size=$label_size"

label_path=./tmpdir/label-filelist
unlabel_path=./tmpdir/unlabel-filelist
query_path=./tmpdir/querylist

mkdir ./tmpdir/
./script/gen-label-file-list.sh $data_dir/Train $label_size > $label_path
./script/gen-filelist.sh $data_dir/Test > $query_path
./script/gen-filelist.sh $data_dir/Unlabel > $unlabel_path

./EM $label_path $query_path $unlabel_path> $output_file 

rm -rf ./tmpdir
