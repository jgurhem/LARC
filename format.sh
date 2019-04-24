#!/bin/bash
git_parent=$(git rev-parse --show-toplevel)

set -e

extensions=(c h cc)
for elt in "${extensions[@]}"
do
	find $git_parent -path "$git_parent/build" -prune -o -name "*.$elt" -print | xargs -i -t clang-format -style=file -i {}
done



