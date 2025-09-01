#!/bin/bash

# 🧪 PRUEBAS ESPECÍFICAS PARA EXPORT
# Script simplificado para probar solo export

echo "🚀 PROBANDO EXPORT ESPECÍFICAMENTE"
echo "=================================="

echo "1️⃣ Probando export sin argumentos:"
echo "export" | ./minishell 2>/dev/null | grep -E "export|PATH|HOME" | head -3

echo -e "\n2️⃣ Probando export crear variable:"
echo -e "export MIVAR=test\necho \$MIVAR\nexit" | ./minishell 2>/dev/null | tail -n +2 | head -1

echo -e "\n3️⃣ Probando export con espacios:"
echo -e "export MIVAR=\"hello world\"\necho \$MIVAR\nexit" | ./minishell 2>/dev/null | tail -n +2 | head -1

echo -e "\n4️⃣ Probando export nombre inválido:"
echo -e "export 123VAR=value\nexit" | ./minishell 2>/dev/null | grep -i "identifier\|invalid\|error" | head -1

echo -e "\n5️⃣ Probando múltiples variables:"
echo -e "export A=1 B=2 C=3\necho \$A \$B \$C\nexit" | ./minishell 2>/dev/null | tail -n +2 | head -1

echo -e "\n6️⃣ Probando variable vacía:"
echo -e "export EMPTY=\necho \"[\$EMPTY]\"\nexit" | ./minishell 2>/dev/null | tail -n +2 | head -1

echo -e "\n✅ EXPORT funciona bien si:"
echo "   - export sin args muestra variables"
echo "   - export VAR=valor crea la variable"
echo "   - echo \$VAR muestra el valor"
echo "   - nombres inválidos dan error"
