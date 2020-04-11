#!/usr/bin/bash
if [[ -z $1 ]]; then
	echo "usage: $0 width"
fi
for i in *.svg; do
	inkscape -C -w $1 -e=${i/%svg/png} $i
	mv ${i/%svg/png} img
done
