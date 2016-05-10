#!/usr/bin/env bash

BUILD_DIR=".build"
OUTPUT_NAME="hash-table"
OUTPUT_FULL="$BUILD_DIR/$OUTPUT_NAME"

do_build() {
  mkdir -p $BUILD_DIR
  gcc ./src/*.c -o $OUTPUT_FULL
}

do_run() {
  $OUTPUT_FULL
}

if do_build; then
  do_run
fi

