#!/bin/bash

cd src/grep
pwd
make rebuild
cd ../../tests/test_grep
cp ../../src/grep/s21_grep .
mv s21_grep main
SUCCESS=0
FAIL=0
COUNTER=0
DIFF_RES=""

declare -a tests=(
"s ../../datasets/test_0_grep.txt VAR"
"-e dark ../../datasets/TheDreamQuestOfUnknownKadath"
"-e gods ../../datasets/TheOtherGods"
"-e Kadath -e dark ../../datasets/TheOtherGods ../../datasets/TheDreamQuestOfUnknownKadath"
"-e Godly -e Onward-onward-through -e hippocephalic -e leaped ../../datasets/TheDreamQuestOfUnknownKadath ../../datasets/TheOtherGods"
)

declare -a extra=(
"-n for ../../datasets/test_1_grep.txt ../../datasets/test_2_grep.txt"
"-n for ../../datasets/test_1_grep.txt"
"-n -e "^\\}" ../../datasets/test_1_grep.txt"
"-c -e "/\\" ../../datasets/test_1_grep.txt"
"-ce int ../../datasets/test_1_grep.txt ../../datasets/test_2_grep.txt"
"-e int ../../datasets/test_1_grep.txt"
"-nivh = ../../datasets/test_1_grep.txt ../../datasets/test_2_grep.txt"
"-e"
"-ie INT ../../datasets/test_5_grep.txt"
"-echar ../../datasets/test_1_grep.txt ../../datasets/test_2_grep.txt"
"-ne = -e out ../../datasets/test_5_grep.txt"
"-iv int ../../datasets/test_5_grep.txt"
"-in int ../../datasets/test_5_grep.txt"
"-v ../../datasets/test_1_grep.txt -e ank"
"-noe ) ../../datasets/test_5_grep.txt"
"-l for ../../datasets/test_1_grep.txt ../../datasets/test_2_grep.txt"
"-o -e int ../../datasets/test_4_grep.txt"
"-e = -e out ../../datasets/test_5_grep.txt"
"-e ing -e the -e not -e is ../../datasets/test_6_grep.txt"
"-c -e "'\.'" ../../datasets/test_1_grep.txt -e '\.'"
"-l for no_file.txt ../../datasets/test_2_grep.txt"
)


testing()
{
    t=$(echo $@ | sed "s/VAR/$var/")
    valgrind --leak-check=full \
                      --show-leak-kinds=all \
                      --log-file=valgrind-out.txt \
                      ./main $t > main.log
    RES="$(grep -e "ERROR SUMMARY" valgrind-out.txt)"
    grep -e "ERROR SUMMARY" valgrind-out.txt
    (( COUNTER++ ))
    if [[ $RES == *"0 errors from 0 contexts"* ]]
    then
      (( SUCCESS++ ))
      echo "$FAIL/$SUCCESS/$COUNTER success"
    else
      (( FAIL++ ))
       echo "$FAIL/$SUCCESS/$COUNTER fail"
    fi
}


# специфические тесты
for i in "${extra[@]}"
do
    var="-"
    testing $i
done

# 1 параметр
for var1 in v c l n h o
do
    for i in "${tests[@]}"
    do
        var="-$var1"
        testing $i
    done
done

# 2 параметра
for var1 in v c l n h o
do
    for var2 in v c l n h o
    do
        if [ $var1 != $var2 ]
        then
            for i in "${tests[@]}"
            do
                var="-$var1 -$var2"
                testing $i
            done
        fi
    done
done

# 3 параметра
for var1 in v c l n h o
do
    for var2 in v c l n h o
    do
        for var3 in v c l n h o
        do
            if [ $var1 != $var2 ] && [ $var2 != $var3 ] && [ $var1 != $var3 ]
            then
                for i in "${tests[@]}"
                do
                    var="-$var1 -$var2 -$var3"
                    testing $i
                done
            fi
        done
    done
done

# 2 сдвоенных параметра
for var1 in v c l n h o
do
    for var2 in v c l n h o
    do
        if [ $var1 != $var2 ]
        then
            for i in "${tests[@]}"
            do
                var="-$var1$var2"
                testing $i
            done
        fi
    done
done

# 3 строенных параметра
for var1 in v c l n h o
do
    for var2 in v c l n h o
    do
        for var3 in v c l n h o
        do
            if [ $var1 != $var2 ] && [ $var2 != $var3 ] && [ $var1 != $var3 ]
            then
                for i in "${tests[@]}"
                do
                    var="-$var1$var2$var3"
                    testing $i
                done
            fi
        done
    done
done

echo "\033[31mFAIL: $FAIL\033[0m"
echo "\033[32mSUCCESS: $SUCCESS\033[0m"
echo "ALL: $COUNTER"
