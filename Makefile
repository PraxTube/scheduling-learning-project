BUILD_DIR = build

EXERCISE_SRC = src/colors.c \
	       src/FCFS.c \
	       src/HRRN.c \
	       src/LCFS.c \
	       src/MLF.c \
	       src/PRIOP.c \
	       src/queue.c \
	       src/RR.c \
	       src/scheduler.c \
	       src/SRTN.c \

EXERCISE_OBJ = $(addprefix $(BUILD_DIR)/, $(EXERCISE_SRC:%.c=%.o))

TEST_DIR = tests
TEST_SRC = $(wildcard $(TEST_DIR)/test_*.c)
TEST_OBJ = $(addprefix $(BUILD_DIR)/, $(TEST_SRC:%.c=%))
TEST_TARGET = $(notdir $(TEST_OBJ))

CC = clang
CC_FLAGS = -Wall -Wextra -g -gdwarf-4

.PHONY: build
build: $(EXERCISE_OBJ)   # Build the exercise

.PHONY: build_tests
build_tests: $(TEST_OBJ) # Build the tests

.PHONY: all_tests
all_tests: $(TEST_OBJ)   # Run all tests
	@echo " "
	@echo "+-------------------+"
	@echo "| Running all Tests |"
	@echo "+-------------------+"
	@echo " "
	@result=0; \
	for test in $(TEST_TARGET); do \
		make --no-print-directory $$test || result=1; \
		echo " "; \
	done; \
	exit $$result

.PHONY: list_tests
list_tests:
	@echo "List of all test targets"
	@echo "------------------------"
	@for test in $(TEST_TARGET) ; do \
		echo "make $$test"; \
	done

BASH_COLOR_RED = \033[0;31m
BASH_COLOR_NONE = \033[0m
BASH_COLOR_GREEN = \033[32m

.PHONY: $(TEST_TARGET)   # Run a specific test
$(TEST_TARGET): %: $(BUILD_DIR)/tests/%
	@echo ">>> Running $<"
	@test_exec=0; ./$< || test_exec=$$?; \
	if [ $$test_exec -eq 0 ]; then \
	    echo -e "<<< $(BASH_COLOR_GREEN)OK$(BASH_COLOR_NONE)"; \
	else \
	    echo -e "<<< $(BASH_COLOR_RED)FAILED$(BASH_COLOR_NONE)"; \
	fi; \
	exit $$test_exec


$(EXERCISE_OBJ): $(BUILD_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CC_FLAGS) -o $@ -c $<

$(TEST_OBJ): $(BUILD_DIR)/%: %.c $(EXERCISE_OBJ)
	@mkdir -p $(dir $@)
	$(CC) $(CC_FLAGS) -o $@ $< $(EXERCISE_OBJ)

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR)

.PHONY: pack
pack:
	zip -r submission.zip src/
