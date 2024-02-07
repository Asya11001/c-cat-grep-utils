#ifndef S21_CAT_H_
#define S21_CAT_H_

#include <ctype.h>
#include <getopt.h>
#include <stdio.h>
#include <string.h>

#include "../constants.h"

typedef struct option Option;

typedef struct {
  int b;
  int e;
  int n;
  int s;
  int t;
  int v;
} Flags;

int mainAction(int argc, char **argv);

void readFile(FILE *fPtr, Flags *flags);

int handleFile(char *argv[], Flags *flags);

int flagParser(int argc, char **argv, Flags *flags);

#endif  // S21_CAT_H_