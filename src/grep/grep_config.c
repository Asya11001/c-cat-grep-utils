#include "grep_config.h"

GrepConfig *initGrepConfig() {
  GrepConfig *grepConfig = calloc(1, sizeof(GrepConfig));

  LastCharState *lastCharState = lastCharStateInit();
  ArrayPattern *arrayPattern = arrayPatternInit();
  Flags *flags = flagsInit();

  grepConfig->lastCharState = lastCharState;
  grepConfig->arrayPattern = arrayPattern;
  grepConfig->flags = flags;

  return grepConfig;
}

void destroyPatternCfg(GrepConfig *grepConfig) {
  arrayPatternDestroy(grepConfig->arrayPattern);
  lastCharStateDestroy(grepConfig->lastCharState);
  flagsDestroy(grepConfig->flags);

  free(grepConfig);
}