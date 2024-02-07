#ifndef FLAGS_H_
#define FLAGS_H_

#include <stdio.h>
#include <stdlib.h>

#include "structs.h"

Flags* flagsInit();
void flagsDestroy(Flags* flags);

#endif  // FLAGS_H_