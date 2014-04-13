#!/bin/sh

cd `dirname $0`

if [ $# != 1 ]; then
    echo "./build.sh simple_num"
    exit 1
fi

g++ sample$1.cpp lua_tinker.cpp -o sample$1 -I/usr/local/include -I. -L/usr/local/lib -llua -ldl -lm
