#!/bin/bash

TOKEI=$(command -v tokei)
if [ -z "$TOKEI" ]; then
  echo "Error: tokei not found. Please install Tokei."
  exit 1
fi

find "$1" -type f \( -iname "*.rs" -o -iname "*.rs" \) -print0 | xargs -0 $TOKEI
