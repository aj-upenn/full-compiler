#!/usr/bin/env bash

set -e   # exit immediately on error
set -u   # error on undefined variables

ASM_DIR="../Assembler"
OUT_DIR="./generated_asm"

cd ../CodeGen/

mkdir -p "$OUT_DIR"

for i in $(seq 1 20); do
    SRC="good/good${i}.bminor"
    ASM_TMP="a.s"
    ASM_OUT="$OUT_DIR/good${i}.s"

    echo "=== Generating assembly for $SRC ==="
    ./bminor -codegen "$SRC" "$ASM_TMP"

    mv "$ASM_TMP" "$ASM_OUT"
done

echo "=== Copying assembly files to $ASM_DIR ==="
cp "$OUT_DIR"/*.s "$ASM_DIR/"

cd "$ASM_DIR"

for s in good*.s; do
    echo "=== Parsing $s ==="
    ./assembler -parse "$s"
done

echo "=== Done ==="
