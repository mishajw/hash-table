#include "../include/table.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
  struct table* t = mk_table(100, NULL);

  add_to_table(t, "Element One");

  add_to_table(t, "Element Two");

  return 0;
}

