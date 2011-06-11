# clean
rm -rf *.o
rm -rf *.bin

nasm -f elf -o loader.o loader.s
gcc -o kernel.o -c kernel.c -nostdlib -nostartfiles -nodefaultlibs
gcc -o string.o -c string.c -nostdlib -nostartfiles -nodefaultlibs
gcc -o console.o -c console.c -nostdlib -nostartfiles -nodefaultlibs
ld -T linker.ld -o kernel.bin loader.o kernel.o string.o console.o
qemu -kernel kernel.bin
