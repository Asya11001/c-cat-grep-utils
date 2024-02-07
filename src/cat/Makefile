CC		:=gcc
CFLAGS	:=-Wall -Wextra -Werror -std=c11
SOURCE	:=s21_cat.c
TARGET	:=s21_cat
TEST_SCRIPT_FILE := ../../tests/test_cat/test_1.sh

all: build

build: s21_cat

rebuild: clean build

s21_cat:
	@$(CC) $(CFLAGS) $(SOURCE) -o s21_cat
	@echo "Build finished"

test_1:
	chmod 777 ${TEST_SCRIPT_FILE}
	sh ${TEST_SCRIPT_FILE}

test:
	make test_1

clean:
	-@rm -rf ${TARGET} *.a *.out *.o
	-@rm -rf *.log
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
