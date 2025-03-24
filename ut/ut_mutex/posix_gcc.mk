.PHONY: clean dist-clean

R:=$(shell pwd)

MKDIR:=mkdir

TERMINA_OSAL_DIR:=/opt/termina-osal

include $(TERMINA_OSAL_DIR)/platform/posix_gcc/platform.mk

TARGET_DIR_NAME:=$R/bin/posix_gcc

INCLUDE_DIRS+=$R/include
SRCS+=$(wildcard $R/src/*.c)

TARGET:=$(TARGET_DIR_NAME)/ut_mutex

OBJS+=$(patsubst %.c, %.o, $(patsubst $(TERMINA_OSAL_DIR)/%, $(TARGET_DIR_NAME)/termina/%, $(OSAL_SRCS)))
OBJS+=$(patsubst %.c, %.o, $(patsubst $R/%, $(TARGET_DIR_NAME)/%, $(SRCS)))

CPPFLAGS+=$(patsubst %,-I %,$(INCLUDE_DIRS))

DEPS:=$(patsubst %.o,%.d,$(OBJS))

all: $(TARGET)

$(TARGET_DIR_NAME)/termina/%.o: $(TERMINA_OSAL_DIR)/%.c
	@echo "Building $<"
	@$(MKDIR) -p $(@D)
	@$(CC) $(CFLAGS) $(CPPFLAGS) -MMD -MP -c -o $@ $<

$(TARGET_DIR_NAME)/%.o: $R/%.c
	@echo "Building $<"
	@$(MKDIR) -p $(@D)
	@$(CC) $(CFLAGS) $(CPPFLAGS) -MMD -MP -c -o $@ $<

$(TARGET): $(OBJS)
	@echo "Linking $@"
	@$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -o $@

clean:
	@rm -rf $(OBJS)
	@rm -rf $(DEPS)

dist-clean:
	@rm -rf $(TARGET_DIR_NAME)

-include $(DEPS)
