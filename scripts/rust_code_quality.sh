#!/bin/bash

PYTHON="$(which python)"
PATH="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
echo $PATH

if [ ! "$PATH/rust-code-analysis/target/debug/rust-code-analysis-cli" ]; then
    echo "Not Found"
    cd "$PATH/rust-code-analysis" || exit 1
    cargo build -p rust-code-analysis-cli
    cd - || exit 1
fi

"$PATH/rust-code-analysis/target/debug/rust-code-analysis-cli" -m -p "$1" --pr -O json > tmp.json

"$PYTHON" "$PATH/parser.py" tmp.json
