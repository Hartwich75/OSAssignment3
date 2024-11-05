#!/bin/bash

test_files=$(find . -name "test_*")
echo "Running test suite..."
for file in $test_files; do
if [[ $file != *.c && $file != *.o ]]; then
    echo "Running test: $file"
    ./"$file" || break
  fi
done
./aq_test
echo "All tests completed"