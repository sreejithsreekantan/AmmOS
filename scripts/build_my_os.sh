
gcc -Wall -O -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-builtin -fnested-functions -I./include -c -o ./build/main.o ./src/main.c
gcc -Wall -O -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-builtin -fnested-functions -I./include -c -o ./build/screen.o ./src/screen.c
nasm -f aout  -o ./build/start.o ./src/start.asm 

#linux, change the line in start.asm to [BITS 32] or [BITS 64] according to your architecture
#ld -T ./scripts/link.ld ./build/start.o ./build/screen.o ./build/main.o -o ./build/kernel.bin 

ld ./build/screen.o ./build/main.o -o ./build/kernel.bin

echo "Done.."

gcc -c -g -Os -march=i686 -ffreestanding -fno-stack-protector -Wall -Werror -I./include -o ./build/bootloader.o ./src/bootloader.c
ld -static -Tlink.ld -nostdlib --nmagic -o bootloader.elf bootloader.o
objcopy -O binary bootloader.elf bootloader.bin

