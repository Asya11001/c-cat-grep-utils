#ifndef CONSTANTS_H_
#define CONSTANTS_H_

#define INIT_COUNT 10
#define APPEND_COUNT 50
#define BUFF_SIZE 1024
#define MAX_MATCHES 512
#define ERROR_CODE_NO_ERROR (0)
#define USAGE_EXPLANATION_GREP \
  "usage: ./s21_grep [-ivclnhso] [-e patterns.txt] [-f file] [file ...]\n"
#define ERROR_MESSAGE_NO_FILE "./s21_grep: %s: No such file or directory\n"
#define ERROR_MESSAGE_COMPILATION_ERROR "./s21_grep: Compilation error!\n"
#define USAGE_EXPLANATION_CAT "usage: ./s21_cat [-benstv] [file ...]\n"
#define NEW_LINE_ASCII_CODE ('\n')
#define NULL_TERMINATOR_ASCII_CODE ('\0')

#define ASCII_DEL_CODE (0177)
#define ASCII_SHIFT_TO_PRINTABLE_VALUE (0100)
#define ASCII_DEL_CHAR_REPRESENTATION '?'

#define PARSABLE_FLAGS_FOR_GET_OPT_CAT "+beEnstTv"
#define PARSABLE_FLAGS_FOR_GET_OPT_GREP "e:ivclnhsf:o"

#define ERROR_CODE_NO_ERROR (0)
#define ERROR_CODE_FILE_OPEN_ERROR (1 << 0)
#define ERROR_CODE_UNKNOWN_OPTION (1 << 1)
#define ERROR_CODE_ALLOCATION_ERROR (1 << 2)

#define INIT_LINE_COUNT (1)
#define INIT_MATCHES_COUNT (0)
#define INIT_EMPTY_LINE_COUNT (0)

#endif  // CONSTANTS_H_