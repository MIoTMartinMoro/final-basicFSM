CONTIKI=../../../../../../../

TARGET = mikro-e
VERSION? = $(shell git describe --abbrev=4 --dirty --always --tags)

CONTIKI_WITH_IPV6 = 1
CONTIKI_WITH_RPL = 0
USE_SERIAL_PADS = 1

APPS += letmecreateiot

CONTIKI_SOURCEFILES += fsm.c


CFLAGS += -DDEBUG_IP=fe80:0000:0000:0000:0019:f5ff:fe89:1d96
CFLAGS += -DVERSION=$(VERSION)
CFLAGS += -Wall -Wno-pointer-sign
CFLAGS += -I $(CONTIKI)/platform/$(TARGET)
CFLAGS += -fno-short-double
LDFLAGS += -Wl,--defsym,_min_heap_size=32000

APPS += letmecreateiot

SMALL=0

all: main
	xc32-bin2hex main.$(TARGET)

include $(CONTIKI)/Makefile.include
