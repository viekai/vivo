#!/bin/sh

if [ $# -eq 1 ];
then
    gdb out/bin/vivod
else
    ./out/bin/vivod
fi
