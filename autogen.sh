#!/usr/bin/env /bin/sh

cd $(dirname "$0")

autoreconf --install --force
rm -rf autom4te.cache
