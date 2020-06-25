
DEVICETREE ?= test/qemu_sifive_e31.dts
OUTPUT_DIR ?= build

generate: virtualenv $(OUTPUT_DIR) scripts/codegen.py scripts/intgen.py
	. venv/bin/activate && python3 scripts/codegen.py \
		--dts $(DEVICETREE) \
		--output-dir $(OUTPUT_DIR)
	. venv/bin/activate && python3 scripts/intgen.py \
		--dts $(DEVICETREE) \
		--output-dir $(OUTPUT_DIR)

$(OUTPUT_DIR):
	mkdir -p $@

virtualenv: venv/bin/activate

venv/bin/activate: requirements.txt
	python3 -m venv venv
	. venv/bin/activate && python3 -m pip install -r requirements.txt

METAL_SRCS = $(wildcard src/*.c src/*.S src/drivers/*.c) build/src/interrupt_table.c build/src/jump_table.S
GLOSS_SRCS = $(wildcard gloss/*.c) $(wildcard gloss/*.S)

build/src/interrupt_table.c: generate
build/src/jump_table.S: generate

CFLAGS=-march=rv32imac -mabi=ilp32 -mcmodel=medlow -ffunction-sections -fdata-sections -Ibuild -I. --specs=nano.specs -DMTIME_RATE_HZ_DEF=32768 -O0 -g
LDFLAGS=-Wl,--gc-sections -Wl,-Map,hello.map -nostartfiles -nostdlib -Ttest/qemu_sifive_e31.lds
LDLIBS=-Wl,--start-group -lc -lgcc -lm -Wl,--end-group

CC=riscv64-unknown-elf-gcc

hello: hello-src/hello.c $(METAL_SRCS) $(GLOSS_SRCS)
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@ $(LDLIBS)

.PHONY: simulate
simulate: hello
	qemu-system-riscv32 -readconfig test/qemu_sifive_e31.cfg -kernel hello -nographic

clean:
	-rm -rf venv
	-rm -r $(OUTPUT_DIR)
	-rm -f hello hello.map