#include "flags.h"

Flags *flagsInit() {
  Flags *flags = calloc(1, sizeof(Flags));
  return flags;
}
void flagsDestroy(Flags *flags) {
  free(flags);
  flags = NULL;
}