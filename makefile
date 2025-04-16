# arguments for running programs
args ?=

# directories
include_dir := include
src_dir     := src
test_dir    := test
build_dir   := build
script_dir  := script

# targets
lib_target   := $(build_dir)/libdsa.a
test_target  := $(build_dir)/dsa_test

# selected dsa or empty if script fails
selected_dsa := $(shell python3 $(script_dir)/selected_dsa.py dsa_list 2>/dev/null || echo)

# sources and headers
headers      := $(shell find $(include_dir) -name '*.h')
core_headers := $(shell find $(include_dir)/dsa/types $(include_dir)/dsa/utils -name '*.h')
sources      := $(shell find $(src_dir) -name '*.c')
core_sources := $(shell find $(src_dir)/utils -name '*.c')
test         := $(shell find $(test_dir) -name '*.c')

# objects
source_objs   := $(sources:.c=.o)
test_objs     := $(test:.c=.o)

lib_core_objs := $(core_sources:.c=.o)
lib_objs      := $(addprefix $(src_dir)/, $(addsuffix .o, $(selected_dsa)))
lib_includes  := $(addprefix $(include_dir)/, $(addsuffix .o, $(selected_dsa)))

# c setup
CC        := gcc
AR        := ar
CFLAGS    := -Wall -Wextra -g -std=c99 -I $(include_dir)

# target rules
all: lib
lib: $(lib_target)
test: $(test_target)

install: $(lib_target)
	@mkdir -p /usr/local/include/dsa
	@cp $(lib_includes) /usr/local/include/dsa/
	@cp $(lib_target) /usr/local/lib/

run-test: $(test_target)
	@echo "./$(test_target) $(args)"
	@./$(test_target) $(ARGS)

.PHONY: all lib test install run-test

# utils rules
format:
	clang-format -i $(headers) $(sources) $(test)

clangdb:
	@(MAKE) clean-all
	@bear -- make

.PHONY: run-test clangdb

# compilation rules
$(lib_target): $(lib_objs) $(lib_core_objs) | $(build_dir)
	$(AR) rcs $@ $^
	@echo "build lib to: $@"

$(test_target): $(source_objs) $(test_objs) | $(build_dir)
	$(CC) $(CFLAGS) -lcriterion $(source_objs) $(test_objs) -o $@
	@echo "build test to: $@"

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(build_dir):
	@mkdir -p $(build_dir)

# clean rules
clean:
	@find . -name '*.o' -delete
	@rm -rf $(build_dir) 2> /dev/null

clean-docs:
	@rm -rf doxygen

clean-clangdb:
	@rm -f compile_commands.js
	@rm -rf .cache/clangd

clean-all: clean clean-docs clean-clangdb

.PHONY: clean clean-docs clean-clangdb clean-all
