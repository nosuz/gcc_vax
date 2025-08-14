# ===== config =====
CROSS ?= vax-unknown-netbsdelf

CC      := $(CROSS)-gcc
AS      := $(CROSS)-as
LD      := $(CROSS)-ld
OBJCOPY := $(CROSS)-objcopy
OBJDUMP := $(CROSS)-objdump

# CFLAGS  ?= -ffreestanding -fno-builtin -Wall -Wextra -Os
# CFLAGS  ?= -ffreestanding -fno-builtin -Wall -Wextra -O2
CFLAGS  ?= -ffreestanding -fno-builtin -Wall -Wextra
ASFLAGS ?=
LDFLAGS ?= -nostdlib -Wl,-T,vax.ld

TARGET  := app
ELF     := $(TARGET).elf
BIN     := $(TARGET).bin
LST     := $(TARGET).lst
MAP     := $(TARGET).map

OBJS    := start.o main.o

# ===== rules =====
.PHONY: all clean

all: $(ELF) $(BIN) $(LST)

$(ELF): $(OBJS) vax.ld
	$(CC) $(LDFLAGS) -Wl,-Map,$(MAP) -o $@ $(OBJS)

$(BIN): $(ELF)
	$(OBJCOPY) -O binary $< $@

$(LST): $(ELF)
	$(OBJDUMP) -d $< > $@

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

%.o: %.S
	$(AS) $(ASFLAGS) -o $@ $<

clean:
	rm -f $(OBJS) $(ELF) $(BIN) $(LST) $(MAP)
