#include <ctype.h>
#include <getopt.h>
#include <stdio.h>
#include <string.h>

typedef struct {
  int b;
  int e;
  int n;
  int s;
  int t;
  int v;
} flagsProps;

int mainAction(int argc, char **argv);

void readFile(FILE *fPtr, flagsProps *flags);

int handleFile(char *argv[], flagsProps *flags);

int flagParser(int argc, char **argv, flagsProps *flags);

int main(int argc, char **argv) { return mainAction(argc, argv); }

int mainAction(int argc, char **argv) {
  flagsProps flags = {0};
  int err = flagParser(argc, argv, &flags);
  while (optind < argc && !err) {
    err = handleFile(argv, &flags);
    optind++;
  }
  if (err) fprintf(stderr, "usage: ./s21_cat [-benstuv] [file ...]\n");
  return err;
}

int flagParser(int argc, char **argv, flagsProps *flags) {
  int err = 0, option, index = 0;
  struct option options[] = {
      {"number-nonblank", 0, 0, 'b'},
      {"number", 0, 0, 'n'},
      {"squeeze-blank", 0, 0, 's'},
      {0, 0, 0, 0},
  };
  while ((option = getopt_long(argc, argv, "+beEnstTv", options, &index)) !=
             -1 &&
         !err) {
    if (option == 'b')
      flags->b = 1;
    else if (option == 'e') {
      flags->e = 1;
      flags->v = 1;
    } else if (option == 'E')
      flags->e = 1;
    else if (option == 'n')
      flags->n = 1;
    else if (option == 's')
      flags->s = 1;
    else if (option == 't') {
      flags->t = 1;
      flags->v = 1;
    } else if (option == 'T')
      flags->t = 1;
    else if (option == 'v')
      flags->v = 1;
    else
      err = 1;
  }
  if (flags->b) flags->n = 0;
  return err;
}

void readFile(FILE *fPtr, flagsProps *flags) {
  int str_count = 1, empty_str_count = 0;
  int last_char = '\n', cur_char = fgetc(fPtr);
  while (cur_char != EOF) {
    if (flags->s && cur_char == '\n' && last_char == '\n')
      empty_str_count++;
    else
      empty_str_count = 0;
    if (empty_str_count > 1) {
      cur_char = fgetc(fPtr);
      continue;
    }
    if (last_char == '\n' && ((flags->b && cur_char != '\n') || flags->n))
      printf("%6d\t", str_count++);

    if (flags->t && cur_char == '\t') {
      printf("^");
      cur_char = 'I';
    }
    if (flags->e && cur_char == '\n') printf("$");
    if (flags->v && iscntrl(cur_char) && cur_char != '\n' && cur_char != '\t') {
      printf("^");
      cur_char = cur_char == 0177 ? '?' : (cur_char | 0100);
    }
    printf("%c", cur_char);
    last_char = cur_char;
    cur_char = fgetc(fPtr);
  }
}

int handleFile(char *argv[], flagsProps *flags) {
  FILE *fPtr;
  int error_code = 0;
  fPtr = fopen(argv[optind], "r");
  if (fPtr != NULL) {
    readFile(fPtr, flags);
    fclose(fPtr);
  } else
    error_code = -1;
  return error_code;
}