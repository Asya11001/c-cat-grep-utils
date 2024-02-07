
SUCCESS=0
FAIL=0
COUNTER=0
DIFF_RES=""

declare -a tests=(
" -e 'Ms. ' ../../datasets/data1"
" -e 'butt' ../../datasets/data2"
" -e 'e' ../../datasets/data1"
" -e 'q' ../../datasets/data2"
" -e 'd' ../../datasets/data1"
" -e 'qwe' ../../datasets/data2"

" -e 'Ms. ' ../../datasets/data1 ../../datasets/data2"
" -e 'butt' ../../datasets/data2 ../../datasets/data2"
" -e 'e' ../../datasets/data1 ../../datasets/data2"
" -e 'q' ../../datasets/data2 ../../datasets/data2"
" -e 'd' ../../datasets/data1 ../../datasets/data2"
" -e 'qwe' ../../datasets/data2 ../../datasets/data2"

" -e 'Ms. ' ../../datasets/data1 ../../datasets/data2 -f nonexistent.file"
" -e 'butt' ../../datasets/data2 ../../datasets/data2 qwe"
" -e 'e' ../../datasets/data1 ../../datasets/data2 some_bullshit.txt"
" -e 'q' ../../datasets/data2 ../../datasets/data2 ()"
" -e 'qwe' ../../datasets/data2 ../../datasets/data2 >.<"

" -e 'string' ../../datasets/multipleMatсhesInARow"
" -e 'qwe' ../../datasets/qwerty.txt"
" -e 'stuff' ../../datasets/stuffFile"
" -e 'q' ../../datasets/data2"
" -e 'd' ../../datasets/data1"
" -e 'qwe' ../../datasets/data2"

" -e 'god' ../../datasets/TheDreamQuestOfUnknownKadath ../../datasets/TheOtherGods"
" -e 'dark' ../../datasets/TheDreamQuestOfUnknownKadath ../../datasets/TheOtherGods"
" -e 'darkness' ../../datasets/TheDreamQuestOfUnknownKadath ../../datasets/TheOtherGods"
" -e 'abyss' ../../datasets/TheDreamQuestOfUnknownKadath ../../datasets/TheOtherGods"
)
  
declare -a tests_extra=(
" -e Ms.  -h ../../datasets/data1"
" -e butt -h ../../datasets/data2"
" -e e -h ../../datasets/data1"
" -e q -h ../../datasets/data2"
" -e d -h ../../datasets/data1"
" -e qwe -h ../../datasets/data2"

" -e Ms.  -h ../../datasets/data1 ../../datasets/data2"
" -e butt -h ../../datasets/data2 ../../datasets/data2"
" -e e -h ../../datasets/data1 ../../datasets/data2"
" -e q -h ../../datasets/data2 ../../datasets/data2"
" -e d -h ../../datasets/data1 ../../datasets/data2"
" -e qwe -h ../../datasets/data2 ../../datasets/data2"

" -e Ms.  -h ../../datasets/data1 ../../datasets/data2 -f nonexistent.file"
" -e butt -h ../../datasets/data2 ../../datasets/data2 qwe"
" -e e -h ../../datasets/data1 ../../datasets/data2 some_bullshit.txt"
" -e q -h ../../datasets/data2 ../../datasets/data2 ()"
" -e qwe -h ../../datasets/data2 ../../datasets/data2 >.<"

" -e string -h ../../datasets/multipleMatсhesInARow"
" -e qwe -h ../../datasets/qwerty.txt"
" -e stuff -h ../../datasets/stuffFile"
" -e q -h ../../datasets/data2"
" -e d -h ../../datasets/data1"
" -e qwe -h ../../datasets/data2"

" -e god -h ../../datasets/TheDreamQuestOfUnknownKadath ../../datasets/TheOtherGods"
" -e dark -h ../../datasets/TheDreamQuestOfUnknownKadath ../../datasets/TheOtherGods"
" -e darkness -h ../../datasets/TheDreamQuestOfUnknownKadath ../../datasets/TheOtherGods"
" -e abyss -h ../../datasets/TheDreamQuestOfUnknownKadath ../../datasets/TheOtherGods"

" -e Ms.  -s ../../datasets/data1"
" -e butt -s ../../datasets/data2"
" -e e -s ../../datasets/data1"
" -e q -s ../../datasets/data2"
" -e d -s ../../datasets/data1"
" -e qwe -s ../../datasets/data2"

" -e Ms.  -s ../../datasets/data1 ../../datasets/data2"
" -e butt -s ../../datasets/data2 ../../datasets/data2"
" -e e -s ../../datasets/data1 ../../datasets/data2"
" -e q -s ../../datasets/data2 ../../datasets/data2"
" -e d -s ../../datasets/data1 ../../datasets/data2"
" -e qwe -s ../../datasets/data2 ../../datasets/data2"

" -e Ms.  -s ../../datasets/data1 ../../datasets/data2 -f nonexistent.file"
" -e butt -s ../../datasets/data2 ../../datasets/data2 qwe"
" -e e -s ../../datasets/data1 ../../datasets/data2 some_bullshit.txt"
" -e q -s ../../datasets/data2 ../../datasets/data2 ()"
" -e qwe -s ../../datasets/data2 ../../datasets/data2 >.<"

" -e string -s ../../datasets/multipleMatсhesInARow"
" -e qwe -s ../../datasets/qwerty.txt"
" -e stuff -s ../../datasets/stuffFile"
" -e q -s ../../datasets/data2"
" -e d -s ../../datasets/data1"
" -e qwe -s ../../datasets/data2"

" -e god -s ../../datasets/TheDreamQuestOfUnknownKadath ../../datasets/TheOtherGods"
" -e dark -s ../../datasets/TheDreamQuestOfUnknownKadath ../../datasets/TheOtherGods"
" -e darkness -s ../../datasets/TheDreamQuestOfUnknownKadath ../../datasets/TheOtherGods"
" -e abyss -s ../../datasets/TheDreamQuestOfUnknownKadath ../../datasets/TheOtherGods"


" -e Ms.  -o ../../datasets/data1"
" -e butt -o ../../datasets/data2"
" -e q -o ../../datasets/data2"
" -e d -o ../../datasets/data1"
" -e qwe -o ../../datasets/data2"

" -e q -o ../../datasets/data2 ../../datasets/data2"
" -e qwe -o ../../datasets/data2 ../../datasets/data2"

" -e Ms.  -o ../../datasets/data1 ../../datasets/data2 -f nonexistent.file"
" -e q -o ../../datasets/data2 ../../datasets/data2 ()"
" -e qwe -o ../../datasets/data2 ../../datasets/data2 >.<"

" -e string -o ../../datasets/multipleMatсhesInARow"
" -e qwe -o ../../datasets/qwerty.txt"
" -e stuff -o ../../datasets/stuffFile"
" -e q -o ../../datasets/data2"
" -e d -o ../../datasets/data1"
" -e qwe -o ../../datasets/data2"

" -e Ms.  -f ../../datasets/patterns.txt ../../datasets/data1"
" -e butt -f ../../datasets/patterns.txt ../../datasets/data2"
" -e e -f ../../datasets/patterns.txt ../../datasets/data1"
" -e q -f ../../datasets/patterns.txt ../../datasets/data2"
" -e d -f ../../datasets/patterns.txt ../../datasets/data1"
" -e qwe -f ../../datasets/patterns.txt ../../datasets/data2"

" -e Ms.  -f ../../datasets/patterns.txt ../../datasets/data1 ../../datasets/data2"
" -e butt -f ../../datasets/patterns.txt ../../datasets/data2 ../../datasets/data2"
" -e e -f ../../datasets/patterns.txt ../../datasets/data1 ../../datasets/data2"
" -e q -f ../../datasets/patterns.txt ../../datasets/data2 ../../datasets/data2"
" -e d -f ../../datasets/patterns.txt ../../datasets/data1 ../../datasets/data2"
" -e qwe -f ../../datasets/patterns.txt ../../datasets/data2 ../../datasets/data2"

" -e Ms.  -f ../../datasets/patterns.txt ../../datasets/data1 ../../datasets/data2 -f nonexistent.file"
" -e butt -f ../../datasets/patterns.txt ../../datasets/data2 ../../datasets/data2 qwe"
" -e e -f ../../datasets/patterns.txt ../../datasets/data1 ../../datasets/data2 some_bullshit.txt"
" -e q -f ../../datasets/patterns.txt ../../datasets/data2 ../../datasets/data2 ()"
" -e qwe -f ../../datasets/patterns.txt ../../datasets/data2 ../../datasets/data2 >.<"

" -e string -f ../../datasets/patterns.txt ../../datasets/multipleMatсhesInARow"
" -e stuff -f ../../datasets/patterns.txt ../../datasets/stuffFile"
" -e q -f ../../datasets/patterns.txt ../../datasets/data2"
" -e d -f ../../datasets/patterns.txt ../../datasets/data1"
" -e qwe -f ../../datasets/patterns.txt ../../datasets/data2"

" -e god -f ../../datasets/patterns.txt ../../datasets/TheDreamQuestOfUnknownKadath ../../datasets/TheOtherGods"
" -e dark -f ../../datasets/patterns.txt ../../datasets/TheDreamQuestOfUnknownKadath ../../datasets/TheOtherGods"
" -e darkness -f ../../datasets/patterns.txt ../../datasets/TheDreamQuestOfUnknownKadath ../../datasets/TheOtherGods"
" -e abyss -f ../../datasets/patterns.txt ../../datasets/TheDreamQuestOfUnknownKadath ../../datasets/TheOtherGods"
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

for var2 in e
do
    for i in "${tests_extra[@]}"
    do
        var="-$var2"
        testing $i
    done
done