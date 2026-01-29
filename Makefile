# TOOLCHAIN
CC      = arm-none-eabi-gcc
OBJCOPY = arm-none-eabi-objcopy
SIZE    = arm-none-eabi-size

# TARGET 
TARGET  = bm-cli
BUILD   = build

# CPU FLAGS 
CPU     = -mcpu=cortex-m3 -mthumb
CFLAGS  = $(CPU) -Wall -Wextra -ffreestanding -nostdlib -O0 -g
LDFLAGS = $(CPU) -T linker.ld -nostdlib -Wl,-Map=$(BUILD)/$(TARGET).map

# SOURCES 
SRC_C   = $(wildcard src/*.c)
SRC_S   = $(wildcard src/*.s)
OBJ     = $(patsubst src/%.c,$(BUILD)/%.o,$(SRC_C)) \
          $(patsubst src/%.s,$(BUILD)/%.o,$(SRC_S))

# RULES 
all: $(BUILD)/$(TARGET).elf

$(BUILD):
	mkdir -p $(BUILD)

$(BUILD)/%.o: src/%.c | $(BUILD)
	$(CC) $(CFLAGS) -Iinclude -c $< -o $@

$(BUILD)/%.o: src/%.s | $(BUILD)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD)/$(TARGET).elf: $(OBJ)
	$(CC) $(OBJ) $(LDFLAGS) -o $@
	$(SIZE) $@

bin: $(BUILD)/$(TARGET).elf
	$(OBJCOPY) -O binary $< $(BUILD)/$(TARGET).bin

run:
	qemu-system-arm \
		-M mps2-an385 \
		-cpu cortex-m3 \
		-kernel $< \
		-nographic \
		-semihosting

clean:
	rm -rf $(BUILD)
