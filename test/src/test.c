#include <stdlib.h>
#include <stdio.h>
#include <check.h>
#include <string.h>

#include "table.h"

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

struct table* default_table() {
  return mk_table(100, (hash_function) hash, (eq_function) eq);
}

char* mk_string(char* unalloc, unsigned int size) {
  char* alloc = malloc(size);
  memset(alloc, 0, size);
  strncpy(alloc, unalloc, size);
  return alloc;
}

START_TEST (add)
{
  struct table *t = default_table();
  table_add(t, mk_string("abc", 5), mk_string("xyz", 5));
  fail_if(strcmp(table_lookup(t, "abc"), "xyz"));
}
END_TEST

Suite* str_suite(void) {
  Suite *suite = suite_create("hash_table");
  TCase *tcase = tcase_create("case");
  tcase_add_test(tcase, add);
  suite_add_tcase(suite, tcase);
  return suite;
}

int main(int argc, char *argv[]) {
  int number_failed;
  Suite *suite = str_suite();
  SRunner *runner = srunner_create(suite);
  srunner_run_all(runner, CK_NORMAL);
  number_failed = srunner_ntests_failed(runner);
  srunner_free(runner);
  return number_failed;
}

