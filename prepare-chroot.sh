#!/bin/sh

set -e

if [ $# != 2 ]; then
    echo "usage: $0 <chroot_dir> <suidexe>" >&2
    exit 1
fi

chroot_dir="$1"
suidexe="$2"

mkdir -p "$chroot_dir/etc" "$chroot_dir/lib" "$chroot_dir/lib64"

echo /run.so > "$chroot_dir/etc/ld.so.preload"
cp build/run.so "$chroot_dir/"

libs=$(ldd "$suidexe" | grep --only-matching --extended-regexp "/\S+")
while read -r lib; do
    cp "$lib" "$chroot_dir$lib"
done <<< "$libs"
