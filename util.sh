#!/bin/bash

if [ "$1" == "go" ] ; then
    ino build && ino upload && ino serial
elif [ "$1" == "clean" ] ; then
    ino clean && ino build
elif [ "$1" == "editor" ] ; then
    bash -c "cd src && gvim"
elif [ "$1" == "print" ] ; then
    cd src
    enscript -M Letter -C -Ecpp -f Courier9 -o - \
        sketch.ino \
        rubber.h \
        rubber.cpp \
        recordman.h \
        recordman.cpp \
        webman.h \
        webman.cpp | \
            ps2pdf - ~/Desktop/check.pdf
fi
