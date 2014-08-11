#!/usr/bin/env /bin/sh

cd $(dirname "$0")

if [ ! -d m4 ]; then
    mkdir m4
fi

autoreconf --install --force
rm -rf autom4te.cache
