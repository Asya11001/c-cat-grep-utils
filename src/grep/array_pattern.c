#include "array_pattern.h"

ArrayPattern *arrayPatternInit() {
  ArrayPattern *arrayPattern = calloc(1, sizeof(ArrayPattern));
  arrayPattern->patterns = calloc(INIT_COUNT, sizeof(char *));
  arrayPattern->count = 0;
  arrayPattern->allocatedMemory = 0;

  if (arrayPattern->patterns) {
    arrayPattern->allocatedMemory = INIT_COUNT;
  } else {
    fprintf(stderr, "memory allocation error!\n");
  }

  return arrayPattern;
}

int arrayPatternRealloc(ArrayPattern *patterns) {
  int errorCode = ERROR_CODE_NO_ERROR;
  char **reservePatternArray = NULL;

  int newArraySize = (patterns->allocatedMemory + APPEND_COUNT);
  size_t newArraySizeInBytes = newArraySize * sizeof(char *);

  reservePatternArray = realloc(patterns->patterns, newArraySizeInBytes);
  if (reservePatternArray) {
    for (int i = patterns->allocatedMemory; i < newArraySize; ++i) {
      reservePatternArray[i] = 0;
    }
    patterns->patterns = reservePatternArray;
    patterns->allocatedMemory = patterns->allocatedMemory + APPEND_COUNT;
  } else {
    errorCode = ERROR_CODE_ALLOCATION_ERROR;
    fprintf(stderr, "Memory reallocation error!\n");
  }
  return errorCode;
}

void arrayPatternPush(ArrayPattern *patterns, char *pattern) {
  size_t length = strlen(pattern);
  char *tempString = calloc(length, sizeof(char) + 1);
  strcpy(tempString, pattern);

  if (patterns->count >= patterns->allocatedMemory)
    arrayPatternRealloc(patterns);

  patterns->patterns[patterns->count] = tempString;
  patterns->count++;
}

void arrayPatternDestroy(ArrayPattern *arrayPattern) {
  for (int i = 0; i < arrayPattern->allocatedMemory; ++i) {
    free(arrayPattern->patterns[i]);
    arrayPattern->patterns[i] = NULL;
  }
  free(arrayPattern->patterns);
  arrayPattern->patterns = NULL;
  free(arrayPattern);
  arrayPattern = NULL;
}