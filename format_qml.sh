#!/bin/bash

# Directory to start formatting from (current directory by default)
DIR="${1:-.}"

# Find all .qml files in the directory and its subdirectories
find "$DIR" -type f -name "*.qml" | while read -r file; do
    echo "Formatting $file..."
    qmlformat -i 2 "$file" -o "$file"
done

echo "Formatting complete!"