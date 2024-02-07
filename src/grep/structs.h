#ifndef STRUCTS_H_
#define STRUCTS_H_

typedef struct {
  char lastPrintedChar;
} LastCharState;

typedef struct {
  char **patterns;
  int count;
  int allocatedMemory;
} ArrayPattern;

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
} Flags;

typedef struct {
  LastCharState *lastCharState;
  ArrayPattern *arrayPattern;
  Flags *flags;
  int countFiles;
} GrepConfig;

#endif  // STRUCTS_H_