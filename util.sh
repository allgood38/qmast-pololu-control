#!/bin/bash

if [ "$1" == "go" ] ; then
    ino build && ino upload && ino serial
elif [ "$1" == "clean" ] ; then
    ino clean && ino build
elif [ "$1" == "editor" ] ; then
    bash -c "cd src && gvim"
elif [ "$1" == "print" ] ; then
    find src/ lib/ -regextype posix-extended \
            -regex '.*.((ino)|(cpp)|h|c)' -print0 | \
        xargs -0 enscript -MLetter -C -Ecpp --color -o - | \
        ps2pdf - ./packaged/source-$(date +%F_%H%M).pdf
elif [ "$1" == "deploy" ] ; then
    NAME="${PWD##*/}"
    TEMPDIR=$(mktemp -d)

    mkdir $TEMPDIR/$NAME
    mkdir $TEMPDIR/libraries
    cp -r src/* $TEMPDIR/$NAME/
    cp -r lib/* $TEMPDIR/libraries/

    pushd $TEMPDIR

    pushd $NAME
    mv sketch.ino ${NAME}.ino
    popd

    zip -r ${NAME}.zip ${NAME}/ libraries/
    popd

    mv $TEMPDIR/${NAME}.zip packaged/${NAME}-$(date +%F-%H%M).zip
fi
