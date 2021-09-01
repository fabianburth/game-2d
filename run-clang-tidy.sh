#!/bin/bash
JOBS=$(nproc)

# Go to autonomous system directory
cd "$(dirname "$0")" || exit 1
REPO_PATH=$(pwd)

SOURCES_PATH=$REPO_PATH/Game2D/src
echo "$SOURCES_PATH"
compdb -p cmake-build-debug list > compile_commands_copy.json
cat compile_commands_copy.json | jq "[.[] | select(.file | startswith(\"$SOURCES_PATH\"))]" | tee compile_commands.json
run-clang-tidy-10 -j"$JOBS" .
