#include "table.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned long hash(unsigned char *str) {
    unsigned long hash = 5381;
    int c;

    while ((c = *str++))
        hash = ((hash << 5) + hash) + c;

    return hash;
}

int eq(char *s1, char *s2) {
  if (strcmp(s1, s2) == 0) {
    return 1;
  } else {
    return 0;
  }
}

int main() {
  struct table* t = mk_table(100, (hash_function) hash, (eq_function) eq);
  
  puts("Building table...");
  for (int i = 0; i < 100; i++) {
    char *key = malloc(20);
    char *value = malloc(20);
    sprintf(key, "key%d", i);
    sprintf(value, "value%d", i);
    table_add(t, key, value);
  }

  puts("Checking everything is stored");
  for (int i = 0; i < 100; i++) {
    char *key = malloc(20);
    sprintf(key, "key%d", i);

    if (!table_exists(t, key)) {
      printf("Key not in table %s\n", key);
    }
  }

  puts("Done");

  return 0;
}

