#!/bin/sh

set -e

mkdir -p chroot/etc chroot/lib chroot/lib64

echo /run.so > chroot/etc/ld.so.preload
cp build/run.so chroot/

libs=$(ldd /bin/su | grep --only-matching --extended-regexp "/\S+")
while read -r lib; do
    cp "$lib" "chroot$lib"
done <<< "$libs"
