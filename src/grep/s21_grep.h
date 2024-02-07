#ifndef S21_GREP_H_
#define S21_GREP_H_

#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "array_regular_expressions.h"
#include "grep_config.h"

void processFile(GrepConfig *grepConfig, char *fileName);

void slice(char *, size_t, size_t);

int mainAction(int argc, char **argv);

int compileRegexp(GrepConfig *grepConfig, regex_t *reg);

int flagParser(int, char **, GrepConfig *, int *);

int getStringFromFile(GrepConfig *, char *);

void handleFile(GrepConfig *, FILE *, regex_t *, char *);

void handleMostPriorityFlags(GrepConfig *, int, char *, int);

#endif  // S21_GREP_H_