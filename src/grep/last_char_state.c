#include "last_char_state.h"

LastCharState *lastCharStateInit() {
  LastCharState *lastCharState = calloc(1, sizeof(LastCharState));
  lastCharState->lastPrintedChar = NULL_TERMINATOR_ASCII_CODE;
  return lastCharState;
}

void lastCharStateDestroy(LastCharState *lastCharState) {
  free(lastCharState);
  lastCharState = NULL;
}