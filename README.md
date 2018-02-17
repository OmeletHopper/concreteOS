# concreteOS
An open source OS I'm making, basically a combination of all my other attempts at OS dev converted into C++ and with actual source structure instead of 10 files in the same directory.

## Compiling
To compile this project, just run:
```
make
```
If you are under Linux, you really shouldn't need special configuration. for Mac, you may need to install a cross compiler, the built in GCC and tools only make MACH binaries. If you are compiling under windows, use the Ubuntu on Windows Subsystem, but if you can do it without it, please let me know how.

## Testing
I recommend testing with QEMU. It's fast, easy, and good enough for me. If you have it installed, run:
```
qemu-system-i386 -kernel /bin/concreteOS.elf
```
or wherever you have your kernel.
