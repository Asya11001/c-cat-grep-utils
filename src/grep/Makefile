CC		:=gcc
CFLAGS	:=-Wall -Wextra -Werror
SOURCE	:=s21_grep.c array_pattern.c grep_config.c flags.c last_char_state.c array_regular_expressions.c
TARGET	:=s21_grep
TEST_SCRIPT_FILE_2 := ../../tests/test_grep/test_2.sh
TEST_SCRIPT_FILE_3 := ../../tests/test_grep/test_3.sh
TEST_SCRIPT_FILE_4 := ../../tests/test_grep/test_4.sh
TEST_SCRIPT_FILE_VALGRIND := ../../test_valgrind/run.sh

all: rebuild

build: s21_grep

s21_grep:
	@$(CC) $(CFLAGS) $(SOURCE) -o s21_grep
	@echo "Build finished"

rebuild: clean build

test_2:
	chmod 777 ${TEST_SCRIPT_FILE_2}
	sh ${TEST_SCRIPT_FILE_2}

test_3:
	chmod 777 ${TEST_SCRIPT_FILE_3}
	sh ${TEST_SCRIPT_FILE_3}

test_4:
	chmod 777 ${TEST_SCRIPT_FILE_4}
	sh ${TEST_SCRIPT_FILE_4}

test_valgrind:
	chmod 777 ${TEST_SCRIPT_FILE_VALGRIND}
	sh ${TEST_SCRIPT_FILE_VALGRIND}

test:
	make test_2
	make test_3
	make test_4

clean:
	-@rm -rf ./${TARGET} *.a *.out *.o
	-@rm -rf test_s21_grep.log test_sys_grep.log
	-@echo "Clean finished"

style:
	@cp ../../materials/linters/.clang-format .
	@find ../../ -type f -name "*.c" -exec clang-format -i {} \;
	@find ../../ -type f -name "*.h" -exec clang-format -i {} \;
	@rm .clang-format
	@echo "Target style is finished"

style_check:
	@cp ../../materials/linters/.clang-format .
	@find ../../ -type f -name "*.c" -exec clang-format -n {} \;
	@find ../../ -type f -name "*.h" -exec clang-format -n {} \;
	@rm .clang-format
	@echo "Target style_check is finished"

cppcheck:
	@find ../../ -type f -name "*.h" -exec cppcheck --enable=all --suppress=missingIncludeSystem {} \;
