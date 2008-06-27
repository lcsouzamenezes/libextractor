#!/bin/sh

ZZSTARTSEED=0
ZZSTOPSEED=100

# fallbacks for direct, non-"make check" usage
if test x"$testdatadir" = x""
then
  testdatadir=../../test
fi
if test x"$bindir" = x""
then
  bindir=`grep "^prefix = " ./Makefile | cut -d ' ' -f 3`
  bindir="$bindir/bin"
fi


for file in $testdatadir/*.bmp $testdatadir/*.png
do
  if test -f "$file"
  then
    tmpfile=`mktemp`
    if ! test -f "$tmpfile"
    then
      exit 1  
    fi
    seed=$ZZSTARTSEED
    while [ $seed -lt $ZZSTOPSEED ]
    do
      echo "file $file seed $seed"
      zzuf -s $seed cat "$file" > "$tmpfile"
      "$bindir/extract" -n -l libextractor_thumbnail:libextractor_mime "$tmpfile" > /dev/null
      seed=`expr $seed + 1`
    done
    rm -f "$tmpfile"
  fi
done

