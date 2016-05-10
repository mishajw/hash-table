#include "../include/table.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
  struct table* t = mk_table(100, NULL);

  struct table_entry* te = mk_entry();
  add_to_table(t, te, 5);

  return 0;
}

