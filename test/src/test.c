#include <stdlib.h>
#include <stdio.h>
#include <check.h>
#include <string.h>
#include <pthread.h>

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

START_TEST (lookup)
{
  struct table *t = default_table();
  table_add(t, mk_string("abc", 5), mk_string("xyz", 5));
  fail_if(strcmp(table_lookup(t, "abc"), "xyz"));
}
END_TEST

START_TEST (exist)
{
  struct table *t = default_table();
  table_add(t, mk_string("key", 5), mk_string("value", 5));
  fail_if(!table_exists(t, "key"));
  table_remove(t, "key");
  fail_if(table_exists(t, "key"));
}
END_TEST

START_TEST (lookup_stress) {
  int amount = 10000;

  struct table *t = default_table();

  // Build table
  for (int i = 0; i < amount; i++) {
    char *key = malloc(20);
    char *value = malloc(20);
    sprintf(key, "key%d", i);
    sprintf(value, "value%d", i);
    table_add(t, key, value);
  }

  // Check everything stored
  for (int i = 0; i < amount; i++) {
    char *key = malloc(20);
    sprintf(key, "key%d", i);

    fail_if(!table_exists(t, key));
  }
}
END_TEST

struct add_struct {
  struct table *t;
  char *prefix;
  int length;
  int amount;
};

void *add_to_table(struct add_struct *as) {
  for (int i = 0; i < as->amount; i++) {
    char *key = malloc(as->length + 10);
    char *val = malloc(as->length + 10);
    sprintf(key, "%s_key_%d", as->prefix, i);
    sprintf(val, "%s_val_%d", as->prefix, i);

    table_add(as->t, key, val);
  }
}

START_TEST (lookup_multithreaded)
{
  struct table *t = default_table();

  unsigned int thread_amount = 3;
  pthread_t threads[thread_amount];

  // Create threads
  for (int i = 0; i < thread_amount; i ++) {
    struct add_struct *as = malloc(sizeof(struct add_struct));
    as->t = t;
    as->length = 3;
    as->amount = 100;
    as->prefix = malloc(10);
    sprintf(as->prefix, "thread%d", i);

    if (pthread_create(&threads[i], NULL, (void*(*)(void*))add_to_table, as)) {
      printf("Couldn't create thread %d\n", i);
      ck_abort();
    }
  }
 
  // Wait for threads to finish
  for (int i = 0; i < thread_amount; i ++) {
    if(pthread_join(threads[i], NULL)) {
      printf("Couldn't join thread %d\n", i);
      ck_abort();
    }
  }

  table_print_entries(t);
}
END_TEST

Suite* str_suite(void) {
  Suite *suite = suite_create("hash_table");
  TCase *tcase = tcase_create("case");
  tcase_add_test(tcase, lookup);
  tcase_add_test(tcase, exist);
  tcase_add_test(tcase, lookup_stress);
  tcase_add_test(tcase, lookup_multithreaded);
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

