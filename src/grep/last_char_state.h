#ifndef LAST_CHAR_STATE_H_
#define LAST_CHAR_STATE_H_

#include <stdio.h>
#include <stdlib.h>

#include "../constants.h"
#include "structs.h"

LastCharState *lastCharStateInit();
void lastCharStateDestroy(LastCharState *lastCharState);

#endif  // LAST_CHAR_STATE_H_