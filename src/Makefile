CC = gcc
CFLAGS := -lstdc++ -std=c++17 -Wall -Werror -Wextra -Wno-sign-compare -g -fno-omit-frame-pointer -O1

EXECUTABLE = test

SRC_LIST_TEST = ./tests/test_list.cpp
SRC_STACK_TEST = ./tests/test_stack.cpp
SRC_QUEUE_TEST = ./tests/queue_tests.cc
SRC_TREE_TEST = ./tests/test_tree.cpp
SRC_QUEUE_TEST = ./tests/test_queue.cc
SRC_MAP_TEST = ./tests/map_tests.cc
SRC_SET_TEST = ./tests/set_tests.cc
SRC_MULTISET_TEST = ./tests/multiset_tests.cc
SRC_VECTOR_TEST = ./tests/test_vector.cpp
SRC_ARRAY_TEST = ./tests/test_array.cpp
SRC_ARRAY_TEST = ./tests/test_array.cpp

SOURCE =  $(SRC_VECTOR_TEST) $(SRC_STACK_TEST) $(SRC_LIST_TEST) $(SRC_ARRAY_TEST) $(SRC_TREE_TEST) $(SRC_QUEUE_TEST)
UNAME = $(shell uname)

OPEN_REPORT :=
LEAKS :=

ifeq ($(UNAME), Linux)
OPEN_REPORT += xdg-open
LEAKS += valgrind --leak-check=full -s -q --track-origins=yes
endif

ifeq ($(UNAME), Darwin)
OPEN_REPORT += open
LEAKS += leaks -atExit --
endif

all: clean test

clean:
	@rm -rf $(EXECUTABLE)
	@rm -rf a.out
	@rm -rf $(OBJ_LIST_TEST)
	@rm -rf $(OBJ_STACK_TEST)
	@rm -rf *.gcno *.gcda report
	@rm -rf tests.info

test:
	@$(CC) $(CFLAGS) $(SOURCE) -lgtest_main -lgtest -o $(EXECUTABLE) && ./$(EXECUTABLE)

gcov_report: clean
	@$(CC) $(CFLAGS) $(SOURCE) -lgtest_main -lgtest -o $(EXECUTABLE) --coverage
	@./$(EXECUTABLE)
	mkdir report
	gcovr -r . --html --html-details -o ./report/coverage_report.html --exclude-branches-by-pattern ".*"
	rm -f *.gcda *.gcno
	$(OPEN_REPORT) ./report/coverage_report.html

leaks_check: test
	@$(LEAKS) ./$(EXECUTABLE)


fsanitize_check:
	@$(CC) -fsanitize=address $(CFLAGS) $(SOURCE) -lgtest_main -lgtest -o $(EXECUTABLE) && ./$(EXECUTABLE)

test_list:
	@$(CC) $(CFLAGS) $(SRC_LIST_TEST) -lgtest_main -lgtest -o $(EXECUTABLE) && ./$(EXECUTABLE)

test_stack:
	@$(CC) $(CFLAGS) $(SRC_STACK_TEST) -lgtest_main -lgtest -o $(EXECUTABLE) && ./$(EXECUTABLE)

test_queue:
	@$(CC) $(CFLAGS) $(SRC_QUEUE_TEST) -lgtest_main -lgtest -o $(EXECUTABLE) && ./$(EXECUTABLE)

test_map:
	@$(CC) $(CFLAGS) $(SRC_MAP_TEST) -lgtest_main -lgtest -o $(EXECUTABLE) && ./$(EXECUTABLE)

test_set:
	@$(CC) $(CFLAGS) $(SRC_SET_TEST) -lgtest_main -lgtest -o $(EXECUTABLE) && ./$(EXECUTABLE)

test_multiset:
	@$(CC) $(CFLAGS) $(SRC_MULTISET_TEST) -lgtest_main -lgtest -o $(EXECUTABLE) && ./$(EXECUTABLE)

test_vector:
	@$(CC) $(CFLAGS) $(SRC_VECTOR_TEST) -lgtest_main -lgtest -o $(EXECUTABLE) && ./$(EXECUTABLE)

test_array:
	@$(CC) $(CFLAGS) $(SRC_ARRAY_TEST) -lgtest_main -lgtest -o $(EXECUTABLE) && ./$(EXECUTABLE)

test_tree:
	@$(CC) $(CFLAGS) $(SRC_TREE_TEST) -lgtest_main -lgtest -o $(EXECUTABLE) && ./$(EXECUTABLE)

run:
	./$(EXECUTABLE)

.PHONY: all clean test gcov_report style clang_format leaks_check run