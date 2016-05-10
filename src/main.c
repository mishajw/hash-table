#include "../include/table.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned long hash(unsigned char *str) {
    unsigned long hash = 5381;
    int c;

    while (c = *str++)
        hash = ((hash << 5) + hash) + c;

    return hash;
}

int main() {
  struct table* t = mk_table(100, NULL);

  add_to_table(t, "Element One");

  add_to_table(t, "Element Two");

  return 0;
}

