.PHONY: all clean dist-clean

MAKE:=make

all: posix-gcc rtems5-leon3-nexysa7

posix-gcc:
	@$(MAKE) -f posix-gcc.mk

rtems5-leon3-nexysa7:
	@$(MAKE) -f rtems5-leon3-nexysa7.mk

clean:
	@$(MAKE) -f posix-gcc.mk clean

dist-clean:
	@$(MAKE) -f posix-gcc.mk dist-clean
	@rm -rf bin
