#!/usr/bin/env bash

# Script to compile a pdf and perform cleanup

# A function to clean up auxiliary files
cleanup_aux_files() {
    echo "Cleaning up auxiliary files (.aux, .log)..."
    rm -f *.aux *.log
}

exit_script() {
    exit 0
}

KEEP_FILES=false

# Check if -k or --keep was passed anywhere in the arguments
for arg in "$@"; do
    if [ "$arg" == "-k" ] || [ "$arg" == "--keep" ]; then
        KEEP_FILES=true
    fi
done

# If no arguments are provided, or only the keep flag is provided
# (e.g., script runs with 0 args, or just with -k/--keep)
if [ "$#" -eq 0 ] || { [ "$#" -eq 1 ] && [ "$KEEP_FILES" = true ]; }; then
    echo "Compiling all .tex files in this folder."

    for file in *.tex; do
        # Ensure matching files actually exist
        [ -e "$file" ] || continue

        lualatex -interaction=nonstopmode "$file"
    done

else
    # An explicit file was provided (assuming it's the first argument if it isn't the flag)
    if [ "$1" == "-k" ] || [ "$1" == "--keep" ]; then
        TEX_FILE=$2
    else
        TEX_FILE=$1
    fi

    if [ -f "$TEX_FILE" ]; then
        echo "Compiling $TEX_FILE..."
        lualatex -interaction=nonstopmode "$TEX_FILE"
    else
        echo "Error: File '$TEX_FILE' not found."
        exit 1
    fi
fi

# Perform cleanup unless the keep flag was set to true
if [ "$KEEP_FILES" = false ]; then
    cleanup_aux_files
else
    echo "Keeping auxiliary files."
fi

exit_script
