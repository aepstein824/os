gcc -o kernel.o -c kernel.c -nostdlib -nostartfiles -nodefaultlibs
gcc -o string.o -c string.c -nostdlib -nostartfiles -nodefaultlibs
ld -T linker.ld -o kernel.bin loader.o kernel.o string.o
qemu -kernel kernel.bin
