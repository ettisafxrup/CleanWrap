#!/usr/bin/env bash

# =========================================
# Thank you for your time in CleanWrap!
#
# Ettisaf Rup
# Software Lead, XtendArena.
# =========================================

set -euo pipefail
IFS=$'\n\t'

readonly BUILD_DIR="release"
readonly ICON_RC="assets/icon.rc"
readonly ICON_OBJ="icon.o"

readonly APP_NAME="CleanWrap"
readonly VERSION="1.0.1"
readonly OUTPUT_EXE="${APP_NAME}.exe"
readonly INNO_SCRIPT="innosetup/cleanwrap_inno.iss"
INSTALLER_MODE=false

print() {
    printf '\n%s\n' "============================================"
    printf '>> %s\n' "$1"
    printf '%s\n\n' "============================================"
}

commandExists() {
    command -v "$1" >/dev/null 2>&1
}

if [ $# -eq 1 ]; then
    INSTALLER_MODE=true
    print "Compilation + Installer build requested"
else
    print "Compilation requested."
fi

if ! commandExists windres; then
    printf 'Error: windres is not installed or not on PATH.\n'
    exit 1
fi

if ! commandExists g++; then
    printf 'Error: g++ is not installed or not on PATH.\n'
    exit 1
fi

if [ "$INSTALLER_MODE" = true ] && ! commandExists ISCC; then
    printf 'Error: ISCC is not installed or not on PATH.\n'
    exit 1
fi

printf 'Starting compilation process...\n\n'

printf 'Compiling CleanWrap...\n'
printf 'Processing icon resource: %s\n' "$ICON_RC"
windres "$ICON_RC" -O coff -o "$ICON_OBJ"
printf 'Icon resource compiled to %s\n\n' "$ICON_OBJ"
printf 'Linking application executable...\n'
g++ -O2 -std=c++20 -Wall -Wextra -Iinclude main.cpp src/*.cpp "$ICON_OBJ" -o "$OUTPUT_EXE" -mwindows -static -static-libgcc -static-libstdc++

rm -f "$ICON_OBJ"
printf '\nCompilation completed successfully: %s\n' "$OUTPUT_EXE"

if [ "$INSTALLER_MODE" = true ]; then
    printf '\nPreparing installer build...\n'
    # make dir if no exists, skip if exists
    mkdir -p "$BUILD_DIR"
    printf 'Running Inno Setup Compiler on %s\n' "$INNO_SCRIPT"
    ISCC "$INNO_SCRIPT"
    printf 'Installer build completed.\n'
fi

printf '\nDone.\n'
