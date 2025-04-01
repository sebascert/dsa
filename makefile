CC := gcc
CFLAGS := -Wall -Wextra
CR_LFLAGS = -lcriterion

# targets
TEST_TARGET = test_dsa

# parameters
ARGS ?=
RELEASE ?= 0

ifeq ($(RELEASE), 1)
	CFLAGS += -O2
else
	CFLAGS += -g -DDEBUG
endif

# directories
SRC_DIR := src
TESTS_DIR := tests
BUILD_DIR := build

CFLAGS += -I './$(SRC_DIR)'

# files and obj files
FILES = $(shell find $(SRC_DIR) -name '*.c')
OBJS = $(FILES:.c=.o)

TESTS_FILES = $(shell find $(TESTS_DIR) -name '*.c')
TESTS_OBJS = $(TESTS_FILES:.c=.o)

# execution rules
all: $(TEST_TARGET)

test: $(TEST_TARGET)
	@echo "running tests: ./$(BUILD_DIR)/$(TEST_TARGET) $(ARGS)"
	@./$(BUILD_DIR)/$(TEST_TARGET) $(ARGS) || echo "exit with status code $$?"

clean:
	@rm -f $(OBJS) $(TESTS_OBJS)

clean-all: clean
	@rm -r $(BUILD_DIR) 2> /dev/null || true

.PHONY: all test clean clean-all

# compilation rules
$(TEST_TARGET): $(BUILD_DIR)/$(TEST_TARGET)
.PHONY: $(TEST_TARGET)

$(BUILD_DIR)/$(TEST_TARGET): $(OBJS) $(TESTS_OBJS) | $(BUILD_DIR)
	@$(CC) $(CFLAGS) $(CR_LFLAGS) $(OBJS) $(TESTS_OBJS) -o $@
	@echo "target: $@"

# background rules
$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "compiling: $<"
