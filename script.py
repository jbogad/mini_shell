#!/bin/bash
echo "=== TESTING EXPORT ==="

echo "1. Export without arguments:"
export

echo -e "\n2. Creating new variables:"
export TEST="hello world"
export NUMBER=42
export EMPTY=""

echo -e "\n3. Checking created variables:"
export | grep -E "(TEST|NUMBER|EMPTY)"

echo -e "\n4. Error cases:"
export 123INVALID="should fail"
export -INVALID="should fail"

echo -e "\n5. Multiple variables:"
export VAR1="uno" VAR2="dos"

echo -e "\n6. Final state:"
export | tail -10