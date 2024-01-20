CC=gcc
CFLAGS=-Wall -Wextra -Werror
SOURCE_GREP= grep/s21_grep.c
SOURCE_CAT= cat/s21_cat.c

all: build


build: s21_grep s21_cat


s21_grep:
	$(CC) $(CFLAGS) $(SOURCE_GREP) -o grep/s21_grep
s21_cat:
	$(CC) $(CFLAGS) $(SOURCE_CAT) -o cat/s21_cat

test_1:
	chmod 777  cat/test_cat/test_1.sh
	sh cat/test_cat/test_1.sh

test_2:
	chmod 777 grep/test_dir/test_2.sh
	sh grep/test_dir/test_2.sh

test_2_leaks:
	chmod 777 grep/test_dir/test_2_leaks.sh
	sh grep/test_dir/test_2_leaks.sh

test_3:
	chmod 777 grep/test_dir/test_3.sh
	sh grep/test_dir/test_3.sh

test_3_leaks:
	chmod 777 grep/test_dir/test_3_leaks.sh
	sh grep/test_dir/test_3_leaks.sh

test_4:
	chmod 777 grep/test_dir/test_grep/test_4.sh
	sh grep/test_dir/test_grep/test_4.sh

test_4_leaks:
	chmod 777 grep/test_dir/test_grep/test_4_leaks.sh
	sh grep/test_dir/test_grep/test_4_leaks.sh

test:
	make test_1
	make test_2
	make test_3
	make test_4

clean:
	rm -rf ./grep/s21_grep ./cat/s21_cat *.a *.out *.o
	rm -rf test_s21_grep.log test_sys_grep.log

check:
	cppcheck --enable=all --suppress=missingIncludeSystem cat/*.c grep/*.c
	clang-format -i -style=Google cat/*.c grep/*.c
	clang-format -n -style=Google cat/*.c grep/*.c

rebuild:
	make clean
	make all
