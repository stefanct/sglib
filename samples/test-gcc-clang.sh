#!/bin/sh

set -e

GCC="$(which gcc)"
CLANG="$(which clang)"
if [ ! -z "$GCC" ]; then
    CC="$GCC" make
fi
if [ ! -z "$CLANG" ]; then
    CC="$CLANG" make
fi
