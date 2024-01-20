#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INIT_COUNT 10
#define APPEND_COUNT 50
#define BUFF_SIZE 1024
#define MAX_MATCHES 512

typedef struct {
  char lastOutputChar;
} grepState;

typedef struct {
  char **patternArray;
  int count;
  int allocatedMemory;
} patternArrayProps;

typedef struct {
  int e;
  int i;
  int v;
  int c;
  int l;
  int n;
  int h;
  int s;
  int f;
  int o;
} flagsProps;

typedef struct {
  grepState *state;
  patternArrayProps *patterns;
  flagsProps *flags;
  int countFiles;
} grepCfg;

grepCfg *initGrepCfg();

void mainGrep(grepCfg *, char *);

void destroyPatternCfg(grepCfg *);

void slice(char *, size_t, size_t);

int mainAction(int argc, char **argv);

void push(patternArrayProps *, char *);

int compileRegexp(grepCfg *cfg, regex_t *reg);

void reallocPatternArray(patternArrayProps *);

int flagParser(int, char **, grepCfg *, int *);

void getStringFromFile(grepCfg *, char *, int *);

void handleFile(grepCfg *, FILE *, regex_t *, char *);

void handleMostPriorityFlags(grepCfg *, int, char *, int);

int main(int argc, char **argv) { return mainAction(argc, argv); }

int mainAction(int argc, char **argv) {
  int err = 0, fileOpenCode = 1;
  grepCfg *cfg = initGrepCfg();
  err |= flagParser(argc, argv, cfg, &fileOpenCode);
  if (argc > 2 && fileOpenCode && !err)
    for (int i = optind; i < argc; i++) mainGrep(cfg, argv[i]);
  else if (err)
    fprintf(stderr,
            "usage: s21_grep [-ivclnhso] [-e pattern_1] [-f "
            "file] [file] ...]\n");
  destroyPatternCfg(cfg);
  return err;
}

int compileRegexp(grepCfg *cfg, regex_t *reg) {
  int compileStatus = 0;
  for (int i = 0; i < cfg->patterns->count; ++i)
    compileStatus |= regcomp(&reg[i], cfg->patterns->patternArray[i],
                             cfg->flags->i ? REG_ICASE : 0);
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

int flagParser(int argc, char **argv, grepCfg *cfg, int *fileOpenCode) {
  int option, error_code = 0, index = 0;
  struct option options[] = {};
  while ((option = getopt_long(argc, argv, "e:ivclnhsf:o", options, &index)) !=
             -1 &&
         !error_code) {
    if (option == 'e') {
      cfg->flags->e = 1;
      push(cfg->patterns, optarg);
    } else if (option == 'i')
      cfg->flags->i = 1;
    else if (option == 'v')
      cfg->flags->v = 1;
    else if (option == 'c')
      cfg->flags->c = 1;
    else if (option == 'l')
      cfg->flags->l = 1;
    else if (option == 'n')
      cfg->flags->n = 1;
    else if (option == 'h')
      cfg->flags->h = 1;
    else if (option == 's')
      cfg->flags->s = 1;
    else if (option == 'f') {
      cfg->flags->f = 1;
      getStringFromFile(cfg, optarg, fileOpenCode);
    } else if (option == 'o')
      cfg->flags->o = 1;
    else
      error_code = 1;
    if (*fileOpenCode == 0)
      fprintf(stderr, "./s21_grep: %s: No such file or directory\n", optarg);
  }
  if (!cfg->flags->e && !cfg->flags->f && !error_code) {
    char pattern[BUFF_SIZE];
    snprintf(pattern, BUFF_SIZE, "%s", argv[optind]);
    push(cfg->patterns, pattern);
    optind++;
  }
  !error_code ? cfg->countFiles = argc - optind : 1;
  return error_code;
}

void mainGrep(grepCfg *cfg, char *fName) {
  FILE *fPtr = fopen(fName, "r");
  regex_t *reg = malloc(cfg->patterns->count * sizeof(regex_t));
  int compileStatus = compileRegexp(cfg, reg);
  if (!fPtr) {
    if (!cfg->flags->s)
      fprintf(stderr, "s21_grep: %s: No such file or directory\n", fName);
  } else {
    if (compileStatus != 0)
      fprintf(stderr, "Compilation error!\n");
    else
      handleFile(cfg, fPtr, reg, fName);
    fclose(fPtr);
  }
  for (int i = 0; i < cfg->patterns->count; ++i) regfree(&reg[i]);
  free(reg);
}

void getStringFromFile(grepCfg *cfg, char *fName, int *fileOpenCode) {
  FILE *fPtr = fopen(fName, "r");
  if (fPtr == NULL)
    *fileOpenCode = 0;
  else {
    ssize_t lineLength;
    size_t size = 0;
    char *line = NULL;
    do {
      lineLength = getline(&line, &size, fPtr);
      if (lineLength != -1) push(cfg->patterns, line);
    } while (lineLength >= 0);
    free(line);
    fclose(fPtr);
  }
}

void printAllMatchesInString(grepCfg *cfg, FILE *fPtr, regex_t reg, char *fName,
                             regmatch_t *regMatch, char *curLineText) {
  if (!cfg->flags->h && cfg->countFiles > 1) printf("%s:", fName);

  for (regoff_t i = regMatch[0].rm_so; i < regMatch[0].rm_eo; i++)
    putchar(curLineText[i]);
  putchar('\n');
  cfg->state->lastOutputChar = '\n';
  slice(curLineText, regMatch[0].rm_eo, strlen(curLineText));
  int status = regexec(&reg, curLineText, MAX_MATCHES, regMatch, 0);
  if (status == 0)
    return printAllMatchesInString(cfg, fPtr, reg, fName, regMatch,
                                   curLineText);
}

void handleFile(grepCfg *cfg, FILE *fPtr, regex_t *reg, char *fName) {
  ssize_t lineLength;
  size_t size = 0;
  char *line = NULL;
  regmatch_t regMatch[MAX_MATCHES];
  int matchesCount = 0, lineNumber = 1,
      flagPrintMatch = (cfg->flags->c || cfg->flags->l) ? 0 : 1;
  do {
    lineLength = getline(&line, &size, fPtr);
    int matchThisLine = 0;
    for (int i = 0; i < cfg->patterns->count && lineLength != -1; ++i) {
      int status = regexec(&reg[i], line, 1, regMatch, 0), match = 0;
      if ((status == 0 && !cfg->flags->v) ||
          (status == REG_NOMATCH && cfg->flags->v)) {
        match = 1;
        matchThisLine++;
      }
      if (match && flagPrintMatch) {
        if (!cfg->flags->h && cfg->countFiles > 1 && matchThisLine <= 1)
          printf("%s:", fName);
        if (cfg->flags->n && matchThisLine <= 1) printf("%d:", lineNumber);
        if (cfg->flags->o && !cfg->flags->v && matchThisLine <= 1) {
          printAllMatchesInString(cfg, fPtr, reg[i], fName, regMatch, line);
        }
        if (cfg->flags->o && cfg->flags->v && matchThisLine <= 1) {
          printf("%s", line);
          cfg->state->lastOutputChar = line[strlen(line) - 1];
        }
        if (!cfg->flags->o && matchThisLine <= 1) {
          printf("%s", line);
          cfg->state->lastOutputChar = line[strlen(line) - 1];
        }
      }
      matchesCount += (match && matchThisLine <= 1);
    }
    lineNumber++;
  } while (lineLength >= 0);
  handleMostPriorityFlags(cfg, matchesCount, fName, flagPrintMatch);
  free(line);
}

void handleMostPriorityFlags(grepCfg *cfg, int matchesCount, char *fileName,
                             int flagPrintMatch) {
  if (cfg->flags->c) {
    if (cfg->countFiles > 1) {
      if (!cfg->flags->h) printf("%s:", fileName);
      printf("%d\n", cfg->flags->l ? matchesCount > 0 : matchesCount);
    } else
      printf("%d\n", cfg->flags->l ? matchesCount > 0 : matchesCount);
  }
  if (cfg->flags->l && matchesCount > 0) printf("%s\n", fileName);
  if (matchesCount > 0 && flagPrintMatch && cfg->state->lastOutputChar != '\n')
    printf("\n");
}

grepCfg *initGrepCfg() {
  grepCfg *cfg = calloc(1, sizeof(grepCfg));
  grepState *state = calloc(1, sizeof(grepState));
  patternArrayProps *patternCfg = calloc(1, sizeof(patternArrayProps));
  flagsProps *flags = calloc(1, sizeof(flagsProps));
  patternCfg->patternArray = calloc(INIT_COUNT, sizeof(char *));
  patternCfg->count = 0;
  patternCfg->allocatedMemory = 0;
  if (patternCfg->patternArray)
    patternCfg->allocatedMemory = INIT_COUNT;
  else
    fprintf(stderr, "memory allocation error!\n");
  cfg->state = state;
  cfg->patterns = patternCfg;
  cfg->state->lastOutputChar = '\0';
  cfg->flags = flags;
  return cfg;
}

void destroyPatternCfg(grepCfg *cfg) {
  for (int i = 0; i < cfg->patterns->allocatedMemory; ++i)
    free(cfg->patterns->patternArray[i]);
  free(cfg->patterns->patternArray);
  free(cfg->patterns);
  free(cfg->state);
  free(cfg->flags);
  free(cfg);
}

void reallocPatternArray(patternArrayProps *patterns) {
  char **reservePatternArray = NULL;
  reservePatternArray =
      realloc(patterns->patternArray,
              (patterns->allocatedMemory + APPEND_COUNT) * sizeof(char *));
  if (reservePatternArray) {
    for (int i = patterns->allocatedMemory;
         i < patterns->allocatedMemory + APPEND_COUNT; ++i)
      reservePatternArray[i] = 0;
    patterns->patternArray = reservePatternArray;
    patterns->allocatedMemory = patterns->allocatedMemory + APPEND_COUNT;
  } else {
    fprintf(stderr, "memory reallocation error!\n");
  }
}

void push(patternArrayProps *patterns, char *pattern) {
  size_t length = strlen(pattern);
  char *tempString = malloc(length * sizeof(char) + 1);
  strcpy(tempString, pattern);

  if (patterns->count >= patterns->allocatedMemory)
    reallocPatternArray(patterns);

  patterns->patternArray[patterns->count] = tempString;
  patterns->count++;
}