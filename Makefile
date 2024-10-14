CC = clang
CFLAGS = -Wall -Wextra
CLANGFORMAT = clang-format

BUILD_DIR = build/
OUTPUT = archive

SRCFILES := main.c src/archive.c src/list.c
OBJFILES := $(patsubst %.c,$(BUILD_DIR)%.o,$(SRCFILES))

.PHONY: archive
default: archive
archive: $(OBJFILES)
	$(CC) $(CFLAGS) $^ -o $(OUTPUT)

$(BUILD_DIR)%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c -o $@ $<

.PHONY: format
format: 
	find . -iname '*.c' -o -iname '*.h' | xargs clang-format -i

.PHONY: clean
clean: $(BUILD_DIR)
	rm -rf $(BUILD_DIR)*