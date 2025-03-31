CC := gcc
CFLAGS := -Wall -Wextra
CR_LFLAGS = -lcriterion

# targets
TARGET = dsa-ctest

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
all: $(TARGET)

test: $(TARGET)
	@echo "./$(BUILD_DIR)/$(TARGET) $(ARGS)"
	@./$(BUILD_DIR)/$(TARGET) $(ARGS) || echo "exit with status code $$?"

clean:
	@rm -f $(OBJS)

clean-all: clean
	@rm -r $(BUILD_DIR) 2> /dev/null || true

.PHONY: all test clean clean-all

# compilation rules
$(TARGET): $(BUILD_DIR)/$(TARGET)
.PHONY: $(TARGET)

$(BUILD_DIR)/$(TARGET): $(OBJS) $(TESTS_OBJS) | $(BUILD_DIR)
	@$(CC) $(CFLAGS) $(CR_LFLAGS) $(OBJS) $(TESTS_OBJS) -o $@

# background rules
$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(TESTS_DIR)/%.o: $(TESTS_DIR)/%.c
	$(CC) $(CFLAGS) $(CR_LFLAGS) -c $< -o $@
