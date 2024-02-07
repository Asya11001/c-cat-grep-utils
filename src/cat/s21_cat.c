#include "s21_cat.h"

int main(int argc, char **argv) {
  int errorCode = mainAction(argc, argv);
  return errorCode;
}

int mainAction(int argc, char **argv) {
  Flags flags = {0};
  int errorCode = flagParser(argc, argv, &flags);
  while (optind < argc && !errorCode) {
    errorCode = handleFile(argv, &flags);
    optind++;
  }
  if (errorCode) {
    fprintf(stderr, USAGE_EXPLANATION_CAT);
  }
  return errorCode;
}

Option *initLongOptions() {
  static Option options[4] = {{"number-nonblank", 0, 0, 'b'},
                              {"number", 0, 0, 'n'},
                              {"squeeze-blank", 0, 0, 's'},
                              {0, 0, 0, 0}};
  return options;
}

int flagParser(int argc, char **argv, Flags *flags) {
  int errorCode = 0;
  int currentOption = 0;
  int index = 0;
  Option *options = initLongOptions();

  while ((currentOption = getopt_long(
              argc, argv, PARSABLE_FLAGS_FOR_GET_OPT_CAT, options, &index)) !=
             -1 &&
         !errorCode) {
    if (currentOption == 'b')
      flags->b = 1;
    else if (currentOption == 'e') {
      flags->e = 1;
      flags->v = 1;
    } else if (currentOption == 'E') {
      flags->e = 1;
    } else if (currentOption == 'n') {
      flags->n = 1;
    } else if (currentOption == 's') {
      flags->s = 1;
    } else if (currentOption == 't') {
      flags->t = 1;
      flags->v = 1;
    } else if (currentOption == 'T') {
      flags->t = 1;
    } else if (currentOption == 'v') {
      flags->v = 1;
    } else {
      errorCode = ERROR_CODE_UNKNOWN_OPTION;
    }
  }
  if (flags->b) {
    flags->n = 0;
  }
  return errorCode;
}

int getCommandChar(int currentChar) {
  int newCurrentChar = 0;
  if (currentChar == ASCII_DEL_CODE) {
    newCurrentChar = ASCII_DEL_CHAR_REPRESENTATION;
  } else {
    newCurrentChar = currentChar + ASCII_SHIFT_TO_PRINTABLE_VALUE;
  }
  return newCurrentChar;
}

void readFile(FILE *fPtr, Flags *flags) {
  int lineCount = INIT_LINE_COUNT;
  int emptyLineCount = INIT_EMPTY_LINE_COUNT;
  int last_char = '\n';
  int cur_char = fgetc(fPtr);

  while (cur_char != EOF) {
    if (flags->s && cur_char == '\n' && last_char == '\n') {
      emptyLineCount++;
    } else {
      emptyLineCount = INIT_EMPTY_LINE_COUNT;
    }
    if (emptyLineCount > 1) {
      cur_char = fgetc(fPtr);
      continue;
    }
    if (last_char == '\n' && ((flags->b && cur_char != '\n') || flags->n)) {
      printf("%6d\t", lineCount++);
    }

    if (flags->t && cur_char == '\t') {
      printf("^");
      cur_char = 'I';
    }
    if (flags->e && cur_char == '\n') printf("$");
    if (flags->v && iscntrl(cur_char) && cur_char != '\n' && cur_char != '\t') {
      printf("^");
      cur_char = getCommandChar(cur_char);
    }
    printf("%c", cur_char);
    last_char = cur_char;
    cur_char = fgetc(fPtr);
  }
}

int handleFile(char *argv[], Flags *flags) {
  FILE *filePtr = NULL;
  int errorCode = 0;

  filePtr = fopen(argv[optind], "r");

  if (filePtr != NULL) {
    readFile(filePtr, flags);
    fclose(filePtr);
  } else {
    errorCode = ERROR_CODE_FILE_OPEN_ERROR;
  }
  return errorCode;
}