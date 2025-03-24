.PHONY: all clean dist-clean

MAKE:=make

all: posix_gcc rtems5_leon3_tsim

posix_gcc:
	@$(MAKE) -f posix_gcc.mk

rtems5_leon3_tsim:
	@$(MAKE) -f rtems5_leon3_tsim.mk

clean:
	@$(MAKE) -f posix_gcc.mk clean

dist-clean:
	@$(MAKE) -f posix_gcc.mk dist-clean
	@rm -rf bin
