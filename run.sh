#!/usr/bin/env bash

BUILD_DIR=".build"
OUTPUT_NAME="hash-table"
OUTPUT_FULL="$BUILD_DIR/$OUTPUT_NAME"

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
  $OUTPUT_FULL
}

if do_cmake && do_make; then
  do_run
fi

