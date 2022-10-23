#! /usr/bin/bash

D=${1:-$(date +%Y%m%d)}

mkdir $D && cd ./$D

T=$(mktemp)

URL="http://soho.cs.unibo.it:8888/$D"

echo "URL scelto: "$URL
echo "TMP file: "$T

curl -Ls $URL | grep  href | awk '{ print $2 }' | grep -o '".*"' | tr -d '"' > $T

cat $T | while read line; do
	K=$URL/$line
	wget -q $K
done

#http://soho.cs.unibo.it:8888/20220929/
# wget -nH -r --cut-dirs=10 --no-parent --reject "index.html*"  http://soho.cs.unibo.it:8888/20220929/
