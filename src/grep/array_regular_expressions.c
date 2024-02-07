#include "array_regular_expressions.h"

regex_t *arrayRegularExpressionsInit(int length) {
  regex_t *arrayRegularExpressions = calloc(length, sizeof(regex_t));
  return arrayRegularExpressions;
}
void arrayRegularExpressionsDestroy(regex_t *arrayRegularExpressions,
                                    int length) {
  for (int i = 0; i < length; ++i) {
    regfree(&arrayRegularExpressions[i]);
  }
  free(arrayRegularExpressions);
  arrayRegularExpressions = NULL;
}