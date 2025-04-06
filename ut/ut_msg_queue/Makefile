.PHONY: all clean dist-clean

MAKE:=make

all: posix-gcc rtems5-leon3-qemu

posix-gcc:
	@$(MAKE) -f posix-gcc.mk

rtems5-leon3-qemu:
	@$(MAKE) -f rtems5-leon3-qemu.mk

clean:
	@$(MAKE) -f posix-gcc.mk clean

dist-clean:
	@$(MAKE) -f posix-gcc.mk dist-clean
	@rm -rf bin
