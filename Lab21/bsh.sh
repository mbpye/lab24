#!/bin/bash


MIN_SIZE=1000


for file in *; do
    if [ -f "$file" ]; then
        if [ $(stat -c %s "$file") -lt $MIN_SIZE ]; then
            filename=$(basename "$file" | cut -d'.' -f1)
            newname="$filename$(echo "$filename" | head -c 3)"
            mv "$file" "$newname.$(echo "$file" | rev | cut -d'.' -f1 | rev)"
        fi
    fi
done
