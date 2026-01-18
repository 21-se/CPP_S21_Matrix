COMPILER = g++ # или gcc -x c++ 
CPP_FLAGS = -Wall -Werror -Wextra -std=c++20
GCOV_FLAGS  = -fprofile-arcs -ftest-coverage
CHECK_FLAGS = 
ARCHIVER    = ar
ARCH_FLAGS  = rcs

UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S), Linux)
	CHECK_FLAGS = -lgtest -lgtest_main -pthread
else
	CHECK_FLAGS = -lgtest -lgtest_main
endif

OBJ_DIR   = object_files
COV_DIR   = coverage_report
TEST_DIR  = tests
UTILS_DIR = utils

SOURCES = $(wildcard *.cpp)
OBJECTS = $(addprefix $(OBJ_DIR)/,$(notdir $(SOURCES:.cpp=.o)))
TESTSRC = $(wildcard $(TEST_DIR)/*.cpp)

TEST_TARGET = run_tests
TESTING_LOG = test_report.log

STATIC_LIB = s21_matrix_oop.a

$(OBJ_DIR)/%.o: %.cpp
	$(shell mkdir -p $(OBJ_DIR))
	$(COMPILER) $(CPP_FLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(UTILS_DIR)/%.cpp
	$(shell mkdir -p $(OBJ_DIR))
	$(COMPILER) $(CPP_FLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(UTILS_DIR)/%.cpp
	$(shell mkdir -p $(OBJ_DIR))
	$(COMPILER) $(CPP_FLAGS) -c $< -o $@

$(STATIC_LIB): $(OBJECTS)
	$(ARCHIVER) $(ARCH_FLAGS) $@ $(OBJECTS) 
	ranlib $(STATIC_LIB)

$(TEST_TARGET): $(STATIC_LIB)
	$(COMPILER) $(CPP_FLAGS) $(TESTSRC) $(CHECK_FLAGS) -o $(TEST_TARGET) $(STATIC_LIB)

all: $(STATIC_LIB)

test: $(TEST_TARGET)
	./$(TEST_TARGET) > $(TESTING_LOG)

gcov_report: CPP_FLAGS += $(GCOV_FLAGS)
gcov_report: $(TEST_TARGET)
	$(shell mkdir -p $(COV_DIR))
	./$(TEST_TARGET)
	gcovr -r . --html --html-details --output $(COV_DIR)/coverage_report.html --filter '.*\.cpp' --exclude $(TEST_DIR) --print-summary --txt-metric branch
	gcovr -r . --exclude $(TEST_DIR) > $(TESTING_LOG)

clean:
	rm -rf $(STATIC_LIB)
	rm -rf $(OBJ_DIR)
	rm -rf $(COV_DIR)
	rm -rf $(TEST_TARGET)
	rm -rf $(TESTING_LOG)
	rm -rf *.gcno
	rm -rf *.gcda

format:
	clang-format --style=Google -i *.cpp *.h $(TEST_DIR)/*.cpp

check-format:
	clang-format --style=Google -n *.cpp *.h $(TEST_DIR)/*.cpp

cppcheck:
	cppcheck --enable=all --check-level=exhaustive  --suppress=missingIncludeSystem .

valgrind:
	CK_FORK=no valgrind --leak-check=full --show-leak-kinds=all ./${TEST_TARGET}

.PHONY: all test gcov_report clean format check-format cppcheck valgrind
