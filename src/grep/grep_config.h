#ifndef GREP_CONFIG_H_
#define GREP_CONFIG_H_

#include "array_pattern.h"
#include "flags.h"
#include "last_char_state.h"

GrepConfig *initGrepConfig();

void destroyPatternCfg(GrepConfig *);

#endif  // GREP_CONFIG_H_