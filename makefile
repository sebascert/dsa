# arguments for running programs
args ?=

# directories
include_dir     := include
src_dir         := src
test_dir        := test
build_dir       := build
script_dir      := script
doc_dir         := doc
doc_build       := $(doc_dir)/build
doxygen_build   := $(doc_dir)/doxyxml

# targets
lib_target   := $(build_dir)/libdsa.a
test_target  := $(build_dir)/dsa_test

# selected dsa or empty if script fails
selected_dsa := $(shell python3 $(script_dir)/selected_dsa.py dsa_list 2>/dev/null || echo)

# sources and headers
headers      := $(shell find $(include_dir) -name '*.h')
core_headers := $(shell find $(include_dir)/dsa/types $(include_dir)/dsa/utils -name '*.h')
lib_headers  := $(addprefix $(include_dir)/dsa/, $(addsuffix .h, $(selected_dsa)))
sources      := $(shell find $(src_dir) -name '*.c')
core_sources := $(shell find $(src_dir)/utils -name '*.c')
test_sources := $(shell find $(test_dir) -name '*.c')

# objects
source_objs   := $(sources:.c=.o)
test_objs     := $(test_sources:.c=.o)
objs          := $(source_objs) $(test_objs)

lib_core_objs := $(core_sources:.c=.o)
lib_objs      := $(addprefix $(src_dir)/, $(addsuffix .o, $(selected_dsa)))

# env setup
CC        := gcc
CSTD      := c99
AR        := ar
CFLAGS    := -Wall -Wextra -g -std=$(CSTD) -I $(include_dir)

MAKEFLAGS += --no-print-directory

PYVENV    := .venv

CLANGDB   := compile_commands.json

PREFIX    := /usr/local

# target rules
all: lib
lib: $(lib_target)
test: $(test_target)

install: $(lib_target)
	@rm -rf $(PREFIX)/include/dsa/
	@rsync -R $(core_headers) $(lib_headers) $(PREFIX)/
	@cp $(lib_target) $(PREFIX)/lib/

run-test: $(test_target)
	@echo "./$(test_target) $(args)"
	@./$(test_target) $(args)

.PHONY: all lib test install run-test

# utils rules
format:
	@clang-format -i $(headers) $(sources) $(test_sources)

lint: $(CLANGDB)
	@clang-tidy $(headers) $(sources) $(test_sources) -p .

clangdb: clean-clangdb
	@$(MAKE) $(CLANGDB)

doc: $(PYVENV)
	@cd $(doc_dir) && doxygen Doxyfile
	@$(PYVENV)/bin/sphinx-build $(doc_dir) $(doc_build)

.PHONY: format lint clangdb doc

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

$(PYVENV):
	@virtualenv $(PYVENV)
	@$(PYVENV)/bin/pip3 install -r requirements.txt

$(CLANGDB): clean
	@bear -- $(MAKE) $(objs)

# clean rules
clean:
	@find . -name '*.o' -delete
	@rm -rf $(build_dir)

clean-clangdb:
	@rm -f $(CLANGDB)
	@rm -rf .cache/clangd

clean-doc:
	@rm -rf $(doxygen_build)
	@rm -rf $(doc_build)

clean-pyvenv:
	@rm -rf $(PYVENV)

clean-all: clean clean-clangdb clean-doc clean-pyvenv

.PHONY: clean clean-clangdb clean-doc clean-pyvenv clean-all
