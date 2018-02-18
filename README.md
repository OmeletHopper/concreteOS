# concreteOS [![Build Status](https://travis-ci.org/OmeletHopper/concreteOS.svg?branch=master)](https://travis-ci.org/OmeletHopper/concreteOS)
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
make test
```
or if you have your kernel saved in an alternate location, run:
```
qemu-system-i386 -kernel /path/to/kernel.elf
```

## Real Hardware
If you want to run the kernel on real hardware, IT MUST BE BOOTED FROM BIOS, NOT UEFI. To boot from an existing GRUB2 installation, add this to your ```/boot/grub/grub.cfg``` below your first existing entry:
```
menuentry "concreteOS" {
        multiboot /path/to/your/concreteOS.elf
}
```

## Contributing
If you want to contribute, that is amazing. You should check out the To-Do list, and maybe start with something there. Also, if you see flaws in code, or better ways to implement things, pull requests are very welcome.

## Credits
Thanks to those at [osdev.org](https://wiki.osdev.org) for everything on their site, without it projects like these wouldn't exist. Also thanks to [osdever.net](https://www.osdever.net), and thanks to [Arjun Sreedharan](http://arjunsreedharan.org/) for his kernel tutorials and more. Code written by Jon Archer.
