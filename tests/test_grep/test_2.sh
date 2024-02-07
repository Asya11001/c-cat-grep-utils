SUCCESS=0
FAIL=0
COUNTER=0
DIFF_RES=""

ls -l
pwd

declare -a tests=(
"'Ms. ' ../../datasets/data1"
"'butt' ../../datasets/data2"
"'e' ../../datasets/data1"
"'q' ../../datasets/data2"
"'d' ../../datasets/data1"
"'qwe' ../../datasets/data2"

"'Ms. ' ../../datasets/data1 ../../datasets/data2"
"'butt' ../../datasets/data2 ../../datasets/data2"
"'e' ../../datasets/data1 ../../datasets/data2"
"'q' ../../datasets/data2 ../../datasets/data2"
"'d' ../../datasets/data1 ../../datasets/data2"
"'qwe' ../../datasets/data2 ../../datasets/data2"

"'Ms. ' ../../datasets/data1 ../../datasets/data2 -f nonexistent.file"
"'butt' ../../datasets/data2 ../../datasets/data2 qwe"
"'e' ../../datasets/data1 ../../datasets/data2 some_bullshit.txt"
"'q' ../../datasets/data2 ../../datasets/data2 ()"
"'qwe' ../../datasets/data2 ../../datasets/data2 nofile.txt"

"'string' ../../datasets/multipleMatсhesInARow"
"'qwe' ../../datasets/qwerty.txt"
"'q' ../../datasets/data2"
"'d' ../../datasets/data1"
"'qwe' ../../datasets/data2"

"'god' ../../datasets/TheDreamQuestOfUnknownKadath ../../datasets/TheOtherGods"
"'dark' ../../datasets/TheDreamQuestOfUnknownKadath ../../datasets/TheOtherGods"
"'darkness' ../../datasets/TheDreamQuestOfUnknownKadath ../../datasets/TheOtherGods"
"'abyss' ../../datasets/TheDreamQuestOfUnknownKadath ./datasets/TheOtherGods"
)

testing()
{
    t=$(echo $@ | sed "s/VAR/$var/")
    ./s21_grep $t > test_s21_grep.log
    grep $t > test_sys_grep.log
    DIFF_RES="$(diff -s test_s21_grep.log test_sys_grep.log)"
    (( COUNTER++ ))
    if [ "$DIFF_RES" == "Files test_s21_grep.log and test_sys_grep.log are identical" ]
    then
      (( SUCCESS++ ))
      echo "\033[31m$FAIL\033[0m/\033[32m$SUCCESS\033[0m/$COUNTER \033[32msuccess\033[0m grep $t"
    else
      (( FAIL++ ))
      echo "\033[31m$FAIL\033[0m/\033[32m$SUCCESS\033[0m/$COUNTER \033[31mfail\033[0m grep $t"
    fi
    rm test_s21_grep.log test_sys_grep.log
}


for var1 in e i v c l n
do
    for i in "${tests[@]}"
    do
        var="-$var1"
        testing $i
    done
done