#!/usr/bin/env bash

action=$1

if [ -z action ]; then
  action="all"
fi

BUILD_DIR=".build"
OUTPUT_NAME="main/hash_table_lib"
TEST_OUTPUT_NAME="test/hash_table_test"

do_clean() {
  rm -r $BUILD_DIR
}

do_cmake() {
  mkdir -p $BUILD_DIR &&
  cd $BUILD_DIR &&
  cmake .. &&
  cd ..
}

do_make() {
  mkdir -p $BUILD_DIR &&
  cd $BUILD_DIR &&
  make &&
  cd ..
}

do_test() {
  cd $BUILD_DIR &&
  ctest --output-on-failure .
}

case "$action" in
  "clean")
    do_clean ;; 
  "cmake")
    do_cmake ;;
  "make")
    do_make ;;
  "test")
    do_test ;;
  "all")
    do_clean && do_cmake && do_make && do_test ;;
  *)
    echo "Usage: $0 [clean | cmake | make | test | all]"
esac

