#!/bin/bash

# Create .clang-format configuration file
cat > .clang-format << 'EOL'
---
Language: Cpp
BasedOnStyle: Google
IndentWidth: 2
SpaceBeforeParens: Always
SpaceInEmptyParentheses: false
SpacesInParentheses: true
SpacesBeforeTrailingComments: 2
BreakBeforeBraces: Attach
ColumnLimit: 100
AccessModifierOffset: -2
AlignAfterOpenBracket: Align
AllowShortFunctionsOnASingleLine: Empty
AllowShortIfStatementsOnASingleLine: false
AllowShortLoopsOnASingleLine: false
BinPackArguments: false
BinPackParameters: false
SpaceBeforeRangeBasedForLoopColon: true
SpaceBeforeCtorInitializerColon: true
SpaceBeforeInheritanceColon: true
SpacesInConditionalStatement: true
SpacesInContainerLiterals: true
EOL

# Find and format files
find . -type f \( -name "*.cpp" -o -name "*.hpp" -o -name "*.h" \) -print0 | xargs -0 clang-format -i -style=file

rm .clang-format

echo "Formatting complete!"