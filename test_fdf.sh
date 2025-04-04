#!/bin/bash

EXEC=./fdf
MAP_DIR=maps
GREEN="\033[0;32m"
RED="\033[0;31m"
RESET="\033[0m"

function print_status() {
    if [ $1 -eq 0 ]; then
        echo -e "${GREEN}[OK]${RESET} $2"
    else
        echo -e "${RED}[FAIL]${RESET} $2"
    fi
}

function test_compilation() {
    make re > /dev/null 2>&1
    if [ ! -x "$EXEC" ]; then
        print_status 1 "Executable $EXEC not found"
        exit 1
    else
        print_status 0 "Compilation successful"
    fi
}

function test_error_handling() {
    $EXEC > /dev/null 2>&1
    print_status $? "No parameter (should fail gracefully)"

    $EXEC too many params > /dev/null 2>&1
    print_status $? "Too many parameters"

	$EXEC /does/not/exist.fdf > /dev/null 2>&1
	if [ $? -ne 0 ]; then
		print_status 0 "Non-existent file"
	else
		print_status 1 "Non-existent file"
	fi
}

function test_map() {
    local map=$1
    $EXEC $MAP_DIR/$map > /dev/null 2>&1 &
    sleep 2
    pkill -f "$EXEC"  # simulate user closing window
    print_status $? "Running with map '$map'"
}

function main() {
    echo "🧪 Running tests for FDF"
    test_compilation
    test_error_handling

    test_map basictest.fdf
    test_map 42.fdf

    echo "✅ Tests completed"
}

main
