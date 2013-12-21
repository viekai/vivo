#!/bin/sh

if [ $# -eq 1 ];
then
    gdb out/bin/main 
else
    ./out/bin/main
fi
