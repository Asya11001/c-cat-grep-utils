gcc tests/s21_grep.c -g -o tests/main


valgrind --leak-check=full \
                  --show-leak-kinds=all \
                  --log-file=valgrind-out.txt \
                  tests/main -e "regex" tests/s21_grep.c
ls -l

filename=valgrind-out.txt
while read line; do
echo $line
done < $filename