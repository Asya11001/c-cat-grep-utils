#ifndef ARRAY_PATTERN_H_
#define ARRAY_PATTERN_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../constants.h"
#include "structs.h"

ArrayPattern *arrayPatternInit();
int arrayPatternRealloc(ArrayPattern *patterns);
void arrayPatternPush(ArrayPattern *patterns, char *pattern);
void arrayPatternDestroy(ArrayPattern *arrayPattern);

#endif  // ARRAY_PATTERN_H_