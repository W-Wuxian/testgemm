#!/bin/bash

exp=$PWD/example
srcp=$PWD/src

CFLT="-O3 -march=native -DITYPE=I64 -DTYPE=float -DETYPE=TGFloat"
CDBL="-O3 -march=native -DITYPE=I64 -DTYPE=double -DETYPE=TGDouble"
CCX32="-O3 -march=native -DITYPE=I64 -DTYPE=comple32 -DETYPE=TGComple32"
CCX64="-O3 -march=native -DITYPE=I64 -DTYPE=comple64 -DETYPE=TGComple64"
for i in "flt" "dbl" "cx32" "cx64"
do
    echo "Case $i"
    cat $exp/$i > $exp/Makefile.am
    cat $srcp/$i > $srcp/Makefile.am
    autoconf 
    automake --add-missing
    if [[ "$i" = "flt" ]]
    then
        CFLAGS=$CFLT
        #./configure --prefix=$PWD/build
        #make
        #make install
    elif [[ "$i" = "dbl" ]]
    then
        CFLAGS=$CDBL
        ./configure --prefix=$PWD/build
        make
        make install
    elif [[ "$i" = "cx32" ]]
    then
        CFLAGS=$CCX32
    elif [[ "$i" = "cx64" ]]
    then
        CFLAGS=$CCX64
    fi
    echo $CFLAGS
    #./configure --prefix=$PWD/build CFLAGS=$CFLAGS
done

echo "" > $exp/Makefile.am
echo "" > $srcp/Makefile.am