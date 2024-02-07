#include "s21_grep.h"

int main(int argc, char **argv) { return mainAction(argc, argv); }

int mainAction(int argc, char **argv) {
  int errorCode = ERROR_CODE_NO_ERROR;
  int errorCodeFileOpen = ERROR_CODE_NO_ERROR;

  GrepConfig *grepConfig = initGrepConfig();

  errorCode = flagParser(argc, argv, grepConfig, &errorCodeFileOpen);

  if (argc > 2 && !errorCodeFileOpen && !errorCode) {
    for (int i = optind; i < argc; i++) {
      processFile(grepConfig, argv[i]);
    }
  } else if (errorCode) {
    fprintf(stderr, USAGE_EXPLANATION_GREP);
  }
  destroyPatternCfg(grepConfig);
  return errorCode;
}

int compileRegexp(GrepConfig *grepConfig, regex_t *reg) {
  int compileStatus = 0;
  for (int i = 0; i < grepConfig->arrayPattern->count; ++i) {
    int compileFlag = 0;
    if (grepConfig->flags->i) {
      compileFlag = REG_ICASE;
    }
    compileStatus |=
        regcomp(&reg[i], grepConfig->arrayPattern->patterns[i], compileFlag);
  }
  return compileStatus;
}

void slice(char *src, size_t start, size_t end) {
  if (start < end) {
    char tempString[(end - start) + 1];
    strncpy(tempString, src + (start == 0 ? start + 1 : start),
            (size_t)(end - (start == 0 ? start + 1 : start)));
    tempString[(end - start)] = '\0';
    strcpy(src, tempString);
  } else {
    strcpy(src, "");
  }
}

int getCountFiles(int argc) {
  int result = argc - optind;
  return result;
}

int flagParser(int argc, char **argv, GrepConfig *grepConfig, int *pErrorCode) {
  int option, errorCode = 0, index = 0;
  int errorCodeFileOpenLocal = ERROR_CODE_NO_ERROR;
  struct option options[] = {};
  do {
    option = getopt_long(argc, argv, PARSABLE_FLAGS_FOR_GET_OPT_GREP, options,
                         &index);
    if (option == -1) {
      break;
    }
    if (option == 'e') {
      grepConfig->flags->e = 1;
      arrayPatternPush(grepConfig->arrayPattern, optarg);
    } else if (option == 'i')
      grepConfig->flags->i = 1;
    else if (option == 'v')
      grepConfig->flags->v = 1;
    else if (option == 'c')
      grepConfig->flags->c = 1;
    else if (option == 'l')
      grepConfig->flags->l = 1;
    else if (option == 'n')
      grepConfig->flags->n = 1;
    else if (option == 'h')
      grepConfig->flags->h = 1;
    else if (option == 's')
      grepConfig->flags->s = 1;
    else if (option == 'f') {
      grepConfig->flags->f = 1;
      errorCodeFileOpenLocal = getStringFromFile(grepConfig, optarg);
    } else if (option == 'o') {
      grepConfig->flags->o = 1;
    } else {
      errorCode = ERROR_CODE_UNKNOWN_OPTION;
    }
    if (errorCodeFileOpenLocal == ERROR_CODE_FILE_OPEN_ERROR) {
      *pErrorCode = errorCodeFileOpenLocal;
      fprintf(stderr, ERROR_MESSAGE_NO_FILE, optarg);
    }

  } while (!errorCode);

  if (!grepConfig->flags->e && !grepConfig->flags->f && !errorCode) {
    char pattern[BUFF_SIZE] = {0};
    snprintf(pattern, BUFF_SIZE, "%s", argv[optind]);
    arrayPatternPush(grepConfig->arrayPattern, pattern);
    optind++;
  }
  if (!errorCode) {
    grepConfig->countFiles = getCountFiles(argc);
  }

  return errorCode;
}

void processFile(GrepConfig *grepConfig, char *fileName) {
  FILE *filePtr = fopen(fileName, "r");
  regex_t *arrayRegularExpressions =
      arrayRegularExpressionsInit(grepConfig->arrayPattern->count);
  int errorCode = compileRegexp(grepConfig, arrayRegularExpressions);

  if (!filePtr) {
    if (!grepConfig->flags->s) {
      fprintf(stderr, ERROR_MESSAGE_NO_FILE, fileName);
    }
  } else {
    if (!errorCode) {
      handleFile(grepConfig, filePtr, arrayRegularExpressions, fileName);
    } else {
      fprintf(stderr, ERROR_MESSAGE_COMPILATION_ERROR);
    }
    fclose(filePtr);
  }

  arrayRegularExpressionsDestroy(arrayRegularExpressions,
                                 grepConfig->arrayPattern->count);
}

void cutLastSymbolInString(char *string) {
  string[strlen(string) - 1] = NULL_TERMINATOR_ASCII_CODE;
}

int getStringFromFile(GrepConfig *grepConfig, char *fileName) {
  int errorCode = ERROR_CODE_NO_ERROR;

  FILE *filePtr = fopen(fileName, "r");

  if (filePtr == NULL) {
    errorCode = ERROR_CODE_FILE_OPEN_ERROR;
  } else {
    ssize_t lineLength;
    size_t size = 0;
    char *line = NULL;
    do {
      lineLength = getline(&line, &size, filePtr);
      if (lineLength != -1) {
        cutLastSymbolInString(line);
        arrayPatternPush(grepConfig->arrayPattern, line);
      }
    } while (lineLength >= 0);

    free(line);
    fclose(filePtr);
  }
  return errorCode;
}

void printAllMatchesInString(GrepConfig *grepConfig, FILE *filePtr, regex_t reg,
                             char *fileName, regmatch_t *regMatch,
                             char *curLineText) {
  if (!grepConfig->flags->h && grepConfig->countFiles > 1) {
    printf("%s:", fileName);
  }

  for (regoff_t i = regMatch[0].rm_so; i < regMatch[0].rm_eo; i++) {
    putchar(curLineText[i]);
  }
  putchar('\n');
  grepConfig->lastCharState->lastPrintedChar = NEW_LINE_ASCII_CODE;
  slice(curLineText, regMatch[0].rm_eo, strlen(curLineText));
  int status = regexec(&reg, curLineText, MAX_MATCHES, regMatch, 0);
  if (status == 0) {
    printAllMatchesInString(grepConfig, filePtr, reg, fileName, regMatch,
                            curLineText);
  } else {
    return;
  }
}

int getFlagPrintMatch(Flags *flags) {
  int result = 1;
  if (flags->c || flags->l) {
    result = 0;
  }
  return result;
}

int handleCommonPriorityFlags(GrepConfig *grepConfig, FILE *filePtr,
                              regex_t *reg, char *fileName) {
  char *line = NULL;
  ssize_t lineLength;
  size_t size = 0;
  regmatch_t regMatch[MAX_MATCHES];
  int lineNumber = INIT_LINE_COUNT;
  int matchesCount = INIT_MATCHES_COUNT;

  int flagPrintMatch = getFlagPrintMatch(grepConfig->flags);

  do {
    lineLength = getline(&line, &size, filePtr);
    int matchThisLine = 0;
    for (int i = 0; i < grepConfig->arrayPattern->count && lineLength != -1;
         ++i) {
      int status = regexec(&reg[i], line, 1, regMatch, 0), match = 0;
      if ((status == 0 && !grepConfig->flags->v) ||
          (status == REG_NOMATCH && grepConfig->flags->v)) {
        match = 1;
        matchThisLine++;
      }
      if (match && flagPrintMatch) {
        if (!grepConfig->flags->h && grepConfig->countFiles > 1 &&
            matchThisLine <= 1)
          printf("%s:", fileName);
        if (grepConfig->flags->n && matchThisLine <= 1)
          printf("%d:", lineNumber);
        if (grepConfig->flags->o && !grepConfig->flags->v &&
            matchThisLine <= 1) {
          printAllMatchesInString(grepConfig, filePtr, reg[i], fileName,
                                  regMatch, line);
        }
        if (grepConfig->flags->o && grepConfig->flags->v &&
            matchThisLine <= 1) {
          printf("%s", line);
          grepConfig->lastCharState->lastPrintedChar = line[strlen(line) - 1];
        }
        if (!grepConfig->flags->o && matchThisLine <= 1) {
          printf("%s", line);
          grepConfig->lastCharState->lastPrintedChar = line[strlen(line) - 1];
        }
      }
      matchesCount += (match && matchThisLine <= 1);
    }
    lineNumber++;
  } while (lineLength >= 0);

  free(line);
  return matchesCount;
}

void handleFile(GrepConfig *grepConfig, FILE *filePtr, regex_t *reg,
                char *fileName) {
  int matchesCount = INIT_MATCHES_COUNT;

  int flagPrintMatch = getFlagPrintMatch(grepConfig->flags);

  matchesCount = handleCommonPriorityFlags(grepConfig, filePtr, reg, fileName);
  handleMostPriorityFlags(grepConfig, matchesCount, fileName, flagPrintMatch);
}

int getMatchingCountBasedOnPrintingFilesWithMatch(GrepConfig *grepConfig,
                                                  int matchesCount) {
  int newMatchesCount = matchesCount;
  if (matchesCount > 0 && grepConfig->flags->l) {
    newMatchesCount = 1;
  }
  return newMatchesCount;
}

void handleMostPriorityFlags(GrepConfig *grepConfig, int matchesCount,
                             char *fileName, int flagPrintMatch) {
  matchesCount =
      getMatchingCountBasedOnPrintingFilesWithMatch(grepConfig, matchesCount);

  if (grepConfig->flags->c) {
    if (grepConfig->countFiles > 1) {
      if (!grepConfig->flags->h) {
        printf("%s:", fileName);
      }
      printf("%d\n", matchesCount);
    } else {
      printf("%d\n", matchesCount);
    }
  }
  if (grepConfig->flags->l && matchesCount > 0) {
    printf("%s\n", fileName);
  }

  int lastPrintedCharIsNewLine =
      grepConfig->lastCharState->lastPrintedChar == NEW_LINE_ASCII_CODE;
  int flagPrintNewLineAtTheEnd = matchesCount > 0;
  flagPrintNewLineAtTheEnd = flagPrintNewLineAtTheEnd && flagPrintMatch;
  flagPrintNewLineAtTheEnd =
      flagPrintNewLineAtTheEnd && !lastPrintedCharIsNewLine;

  if (flagPrintNewLineAtTheEnd) {
    printf("\n");
  }
}
