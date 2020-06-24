CROSS_COMPILE = arm-linux-gnueabi-

AS		= $(CROSS_COMPILE)as
LD		= $(CROSS_COMPILE)ld
CC		= $(CROSS_COMPILE)gcc
CPP		= $(CC) -E
AR		= $(CROSS_COMPILE)ar
NM		= $(CROSS_COMPILE)nm

STRIP		= $(CROSS_COMPILE)strip
OBJCOPY		= $(CROSS_COMPILE)objcopy
OBJDUMP		= $(CROSS_COMPILE)objdump

export AS LD CC CPP AR NM
export STRIP OBJCOPY OBJDUMP

CFLAGS := -Wall -O2 -g -march=armv4 -fno-stack-protector -nostdinc -nostdlib -fno-builtin
CFLAGS += -I $(TOPDIR)/s3c2440 -I $(TOPDIR)/arm -I $(TOPDIR)/source -I $(TOPDIR)/app -I $(TOPDIR)/lib
export CFLAGS

LDFLAGS := lib/libgcc.a -T ucos2.lds
			#-march=armv4 -nostartfiles -Wl,--build-id=none

COPYFLAGS := -O binary

DUMPFLAGS := 

TOPDIR := $(shell pwd)
export TOPDIR

TARGET := ucos2


obj-y += s3c2440/
obj-y += arm/
obj-y += source/
obj-y += app/
obj-y += lib/

all : start_recursive_build $(TARGET)
	@echo $(TARGET) has been built!

.PHONY : start_recursive_build
start_recursive_build:
	make -C ./ -f $(TOPDIR)/Makefile.build

$(TARGET) : built-in.o
	$(LD) -o $(TARGET) built-in.o $(LDFLAGS)
	$(OBJCOPY) $(COPYFLAGS) -S $(TARGET) $(addsuffix .bin,$(TARGET))
	$(OBJDUMP) -D $(TARGET) > $(addsuffix .dis,$(TARGET))

.PHONY : clean
clean:
	rm -f $(shell find -name "*.o")
	rm -f $(shell find -name "*.bin")
	rm -f $(shell find -name "*.dis")
	rm -f $(TARGET)

.PHONY : distclean
distclean:
	rm -f $(shell find -name "*.o")
	rm -f $(shell find -name "*.d")
	rm -f $(shell find -name "*.bin")
	rm -f $(shell find -name "*.dis")
	rm -f $(TARGET)
