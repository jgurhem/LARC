#!/bin/bash
git_parent=$(git rev-parse --show-toplevel)
format=clang-format
#use clang-format v8.0.0
# cmd to create .clang-format file :
#$format -dump-config -style=llvm > .clang-format
set -e

extensions=(c h cc)
for elt in "${extensions[@]}"
do
	find $git_parent -path "$git_parent/build" -prune -o -name "*.$elt" -print | xargs -i -t $format -style=file -i {}
done



