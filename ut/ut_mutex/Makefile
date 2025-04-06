.PHONY: all clean dist-clean

MAKE:=make

all: posix-gcc rtems5-leon3-tsim

posix-gcc:
	@$(MAKE) -f posix-gcc.mk

rtems5-leon3-tsim:
	@$(MAKE) -f rtems5-leon3-tsim.mk

clean:
	@$(MAKE) -f posix-gcc.mk clean

dist-clean:
	@$(MAKE) -f posix-gcc.mk dist-clean
	@rm -rf bin
