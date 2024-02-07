#ifndef ARRAY_REGULAR_EXPRESSIONS_H_
#define ARRAY_REGULAR_EXPRESSIONS_H_

#include <regex.h>
#include <stdlib.h>

regex_t *arrayRegularExpressionsInit(int length);
void arrayRegularExpressionsDestroy(regex_t *arrayRegularExpressions,
                                    int length);

#endif  // ARRAY_REGULAR_EXPRESSIONS_H_