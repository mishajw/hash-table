#!/usr/bin/env bash

action=$1

if [ -z action ]; then
  action="all"
fi

BUILD_DIR=".build"
OUTPUT_NAME="main/hash-table"
TEST_OUTPUT_NAME="test/Test"

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

do_run() {
  $BUILD_DIR/$OUTPUT_NAME
}

do_test() {
  $BUILD_DIR/$TEST_OUTPUT_NAME
}

case "$action" in
  "cmake")
    do_cmake ;;
  "make")
    do_make ;;
  "all-run")
    if do_cmake && do_make; then
      do_run
    fi ;;
  "run")
    do_run ;;
  "all-test")
    if do_cmake && do_make; then
      do_test
    fi ;;
  "test")
    do_test ;;
  "all")
    if do_cmake && do_make; then
      do_run ; do_test
    fi ;;
esac

