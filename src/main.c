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
  struct table* t = mk_table(100, (HASH_FUNCTION()) hash);

  for (unsigned int i = 0; i < 10; i ++) {
    char *buf = malloc(20 * sizeof(char));
    sprintf(buf, "elem%d", i);

    table_add(t, buf);
  }

  table_print_entries(t);

  return 0;
}

