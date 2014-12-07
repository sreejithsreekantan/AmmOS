CC	= gcc
CFLAGS	= -Wall -Wextra -nostdlib -fno-builtin -nostartfiles -nodefaultlibs -I. -arch x86_64
LD	= ld
BUILD_DIR=../build
 
OBJFILES = main.o screen.o
 
all: kernel.img
 
.s.o:
	nasm -f elf -o $@ $<
 
.c.o:
	$(CC) $(CFLAGS) -o $@ -c $<
 
kernel.bin: $(OBJFILES)
	$(LD) -e _main -arch x86_64 -o $@ $^
 
kernel.img: kernel.bin
	dd if=/dev/zero of=pad bs=1 count=750
	cat stage1 stage2 pad $< > $@
	#rm $(BUILD_DIR)/*
	mv $(OBJFILES) kernel.bin kernel.img pad $(BUILD_DIR)
 
clean:
	$(RM) $(OBJFILES) kernel.bin kernel.img pad
	rm $(BUILD_DIR)/*
 
install:
	$(RM) $(OBJFILES) kernel.bin