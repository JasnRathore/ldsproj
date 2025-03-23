#include <ctype.h>
#include "common.h"

void toLowerString(char *str) {
    for (int i = 0; str[i]; i++) {
        str[i] = tolower(str[i]);
    }
}
