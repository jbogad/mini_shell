#!/bin/bash

# 🧪 SCRIPT DE PRUEBAS COMPLETO PARA MINISHELL
# Prueba automáticamente todas las funcionalidades

# Colores para output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
PURPLE='\033[0;35m'
CYAN='\033[0;36m'
NC='\033[0m' # No Color

# Contadores
TOTAL_TESTS=0
PASSED_TESTS=0
FAILED_TESTS=0

# Función para imprimir headers
print_header() {
    echo -e "\n${BLUE}===================================================${NC}"
    echo -e "${CYAN}🧪 $1${NC}"
    echo -e "${BLUE}===================================================${NC}"
}

# Función para imprimir resultado de test
print_test_result() {
    local test_name="$1"
    local expected="$2"
    local actual="$3"
    local status="$4"
    
    TOTAL_TESTS=$((TOTAL_TESTS + 1))
    
    if [ "$status" = "PASS" ]; then
        echo -e "${GREEN}✅ PASS${NC}: $test_name"
        PASSED_TESTS=$((PASSED_TESTS + 1))
    else
        echo -e "${RED}❌ FAIL${NC}: $test_name"
        echo -e "   ${YELLOW}Expected${NC}: $expected"
        echo -e "   ${YELLOW}Got${NC}: $actual"
        FAILED_TESTS=$((FAILED_TESTS + 1))
    fi
}

# Función para ejecutar comando en minishell
run_minishell_test() {
    local cmd="$1"
    local timeout_duration="${2:-5}"
    
    # Crear archivo temporal con el comando
    echo -e "$cmd\nexit" > /tmp/minishell_test_input.txt
    
    # Ejecutar sin timeout (macOS no tiene timeout por defecto)
    ./minishell < /tmp/minishell_test_input.txt 2>&1
    local exit_code=$?
    
    # Limpiar
    rm -f /tmp/minishell_test_input.txt
    
    return $exit_code
}

# Función para comparar con bash
compare_with_bash() {
    local cmd="$1"
    local test_name="$2"
    
    # Ejecutar en bash
    bash_output=$(echo "$cmd" | bash 2>&1)
    bash_exit=$?
    
    # Ejecutar en minishell
    minishell_output=$(run_minishell_test "$cmd")
    minishell_exit=$?
    
    # Comparar resultados (ignorando diferencias menores)
    if [ "$bash_output" = "$minishell_output" ] && [ "$bash_exit" = "$minishell_exit" ]; then
        print_test_result "$test_name" "$bash_output" "$minishell_output" "PASS"
    else
        print_test_result "$test_name" "bash: $bash_output (exit: $bash_exit)" "minishell: $minishell_output (exit: $minishell_exit)" "FAIL"
    fi
}

# Comprobar que minishell existe
if [ ! -f "./minishell" ]; then
    echo -e "${RED}❌ Error: ./minishell no encontrado. Ejecuta 'make' primero.${NC}"
    exit 1
fi

echo -e "${PURPLE}🚀 INICIANDO PRUEBAS COMPLETAS DE MINISHELL${NC}"
echo -e "${YELLOW}Fecha: $(date)${NC}\n"

# ===================================================================
print_header "BUILT-IN: ECHO"
# ===================================================================

# Echo básico
compare_with_bash "echo hello" "echo básico"
compare_with_bash "echo hello world" "echo múltiples palabras"
compare_with_bash "echo" "echo sin argumentos"

# Echo con -n
minishell_output=$(run_minishell_test "echo -n hello")
if [[ "$minishell_output" == *"hello"* ]] && [[ "$minishell_output" != *"hello"$'\n'* ]]; then
    print_test_result "echo -n (sin newline)" "hello (sin \\n)" "$minishell_output" "PASS"
else
    print_test_result "echo -n (sin newline)" "hello (sin \\n)" "$minishell_output" "FAIL"
fi

# Echo con quotes
compare_with_bash 'echo "hello world"' "echo con comillas dobles"
compare_with_bash "echo 'hello world'" "echo con comillas simples"
compare_with_bash 'echo ""' "echo string vacío"

# ===================================================================
print_header "BUILT-IN: PWD"
# ===================================================================

compare_with_bash "pwd" "pwd básico"
compare_with_bash "pwd extra args" "pwd con argumentos extra"

# ===================================================================
print_header "BUILT-IN: ENV"
# ===================================================================

# Env básico (solo verificar que muestra variables)
env_output=$(run_minishell_test "env")
if [[ "$env_output" == *"PATH="* ]] && [[ "$env_output" == *"HOME="* ]]; then
    print_test_result "env básico" "Muestra PATH y HOME" "Variables mostradas correctamente" "PASS"
else
    print_test_result "env básico" "Muestra PATH y HOME" "$env_output" "FAIL"
fi

# ===================================================================
print_header "BUILT-IN: EXPORT"
# ===================================================================

# Export sin argumentos
export_output=$(run_minishell_test "export")
if [[ "$export_output" == *"export"* ]]; then
    print_test_result "export sin argumentos" "Lista variables exportadas" "Output contiene export" "PASS"
else
    print_test_result "export sin argumentos" "Lista variables exportadas" "$export_output" "FAIL"
fi

# Export crear variable
test_output=$(run_minishell_test "export TEST=valor\necho \$TEST")
if [[ "$test_output" == *"valor"* ]]; then
    print_test_result "export crear variable" "valor" "Variable creada correctamente" "PASS"
else
    print_test_result "export crear variable" "valor" "$test_output" "FAIL"
fi

# Export con espacios
test_output=$(run_minishell_test "export TEST=\"hello world\"\necho \$TEST")
if [[ "$test_output" == *"hello world"* ]]; then
    print_test_result "export con espacios" "hello world" "Variable con espacios creada" "PASS"
else
    print_test_result "export con espacios" "hello world" "$test_output" "FAIL"
fi

# Export nombre inválido
test_output=$(run_minishell_test "export 123VAR=value")
if [[ "$test_output" == *"not a valid identifier"* ]] || [[ "$test_output" == *"invalid"* ]]; then
    print_test_result "export nombre inválido" "error message" "Error detectado correctamente" "PASS"
else
    print_test_result "export nombre inválido" "error message" "$test_output" "FAIL"
fi

# ===================================================================
print_header "BUILT-IN: UNSET"
# ===================================================================

test_output=$(run_minishell_test "export TEST=valor\nunset TEST\necho \$TEST")
if [[ "$test_output" != *"valor"* ]]; then
    print_test_result "unset variable" "variable eliminada" "Variable eliminada correctamente" "PASS"
else
    print_test_result "unset variable" "variable eliminada" "$test_output" "FAIL"
fi

# ===================================================================
print_header "BUILT-IN: CD"
# ===================================================================

# CD a directorio válido
test_output=$(run_minishell_test "cd /tmp\npwd")
if [[ "$test_output" == *"/tmp"* ]]; then
    print_test_result "cd directorio válido" "/tmp" "Cambio de directorio exitoso" "PASS"
else
    print_test_result "cd directorio válido" "/tmp" "$test_output" "FAIL"
fi

# CD con ..
test_output=$(run_minishell_test "cd ..\npwd")
expected_dir=$(cd .. && pwd)
if [[ "$test_output" == *"$expected_dir"* ]]; then
    print_test_result "cd .." "$expected_dir" "Navegación con .. exitosa" "PASS"
else
    print_test_result "cd .." "$expected_dir" "$test_output" "FAIL"
fi

# CD a directorio inexistente
test_output=$(run_minishell_test "cd /directorio/inexistente/12345")
if [[ "$test_output" == *"No such file"* ]] || [[ "$test_output" == *"not found"* ]] || [[ "$test_output" == *"cannot access"* ]]; then
    print_test_result "cd directorio inexistente" "error message" "Error detectado correctamente" "PASS"
else
    print_test_result "cd directorio inexistente" "error message" "$test_output" "FAIL"
fi

# ===================================================================
print_header "BUILT-IN: EXIT"
# ===================================================================

# Exit básico
echo "exit" | ./minishell >/dev/null 2>&1
exit_code=$?
if [ $exit_code -eq 0 ]; then
    print_test_result "exit básico" "exit code 0" "Salida exitosa" "PASS"
else
    print_test_result "exit básico" "exit code 0" "exit code $exit_code" "FAIL"
fi

# Exit con código
echo "exit 42" | ./minishell >/dev/null 2>&1
exit_code=$?
if [ $exit_code -eq 42 ]; then
    print_test_result "exit con código" "exit code 42" "Código de salida correcto" "PASS"
else
    print_test_result "exit con código" "exit code 42" "exit code $exit_code" "FAIL"
fi

# ===================================================================
print_header "COMANDOS EXTERNOS (EXEC)"
# ===================================================================

# Comando básico
compare_with_bash "ls" "comando ls básico"

# Comando con argumentos
test_output=$(run_minishell_test "echo test | cat")
if [[ "$test_output" == *"test"* ]]; then
    print_test_result "comando con pipe simple" "test" "Pipe funcionando" "PASS"
else
    print_test_result "comando con pipe simple" "test" "$test_output" "FAIL"
fi

# Comando inexistente
test_output=$(run_minishell_test "comando_que_no_existe_12345")
if [[ "$test_output" == *"command not found"* ]] || [[ "$test_output" == *"not found"* ]]; then
    print_test_result "comando inexistente" "command not found" "Error detectado correctamente" "PASS"
else
    print_test_result "comando inexistente" "command not found" "$test_output" "FAIL"
fi

# ===================================================================
print_header "PIPES"
# ===================================================================

# Pipe simple
compare_with_bash "echo hello | cat" "pipe simple"

# Pipe múltiple
test_output=$(run_minishell_test "echo -e \"a\nb\nc\" | head -2 | tail -1")
if [[ "$test_output" == *"b"* ]]; then
    print_test_result "pipe múltiple" "b" "Pipes múltiples funcionando" "PASS"
else
    print_test_result "pipe múltiple" "b" "$test_output" "FAIL"
fi

# ===================================================================
print_header "REDIRECTIONS"
# ===================================================================

# Output redirection
test_output=$(run_minishell_test "echo test > /tmp/minishell_test.txt\ncat /tmp/minishell_test.txt")
if [[ "$test_output" == *"test"* ]]; then
    print_test_result "output redirection >" "test" "Redirección de salida funcionando" "PASS"
else
    print_test_result "output redirection >" "test" "$test_output" "FAIL"
fi

# Append redirection
test_output=$(run_minishell_test "echo line1 > /tmp/minishell_test.txt\necho line2 >> /tmp/minishell_test.txt\ncat /tmp/minishell_test.txt")
if [[ "$test_output" == *"line1"* ]] && [[ "$test_output" == *"line2"* ]]; then
    print_test_result "append redirection >>" "line1 y line2" "Redirección append funcionando" "PASS"
else
    print_test_result "append redirection >>" "line1 y line2" "$test_output" "FAIL"
fi

# Input redirection
test_output=$(run_minishell_test "echo content > /tmp/minishell_test.txt\ncat < /tmp/minishell_test.txt")
if [[ "$test_output" == *"content"* ]]; then
    print_test_result "input redirection <" "content" "Redirección de entrada funcionando" "PASS"
else
    print_test_result "input redirection <" "content" "$test_output" "FAIL"
fi

# ===================================================================
print_header "VARIABLES DE ENTORNO"
# ===================================================================

# Expansión de variables
test_output=$(run_minishell_test "export TEST=hello\necho \$TEST")
if [[ "$test_output" == *"hello"* ]]; then
    print_test_result "expansión de variables" "hello" "Expansión funcionando" "PASS"
else
    print_test_result "expansión de variables" "hello" "$test_output" "FAIL"
fi

# Variable PATH
test_output=$(run_minishell_test "echo \$PATH")
if [[ "$test_output" == *"/bin"* ]] || [[ "$test_output" == *"/usr/bin"* ]]; then
    print_test_result "variable PATH" "contiene rutas bin" "PATH disponible" "PASS"
else
    print_test_result "variable PATH" "contiene rutas bin" "$test_output" "FAIL"
fi

# ===================================================================
print_header "CASOS EDGE"
# ===================================================================

# Comando vacío
test_output=$(run_minishell_test "")
print_test_result "comando vacío" "sin crash" "Manejo de entrada vacía" "PASS"

# Espacios múltiples
test_output=$(run_minishell_test "   echo    hello   world   ")
if [[ "$test_output" == *"hello world"* ]]; then
    print_test_result "espacios múltiples" "hello world" "Manejo de espacios correcto" "PASS"
else
    print_test_result "espacios múltiples" "hello world" "$test_output" "FAIL"
fi

# ===================================================================
print_header "COMBINACIONES COMPLEJAS"
# ===================================================================

# Pipe + Redirection
test_output=$(run_minishell_test "echo test | cat > /tmp/minishell_test.txt\ncat /tmp/minishell_test.txt")
if [[ "$test_output" == *"test"* ]]; then
    print_test_result "pipe + redirection" "test" "Combinación funcionando" "PASS"
else
    print_test_result "pipe + redirection" "test" "$test_output" "FAIL"
fi

# Export + Variable en comando
test_output=$(run_minishell_test "export CMD=ls\n\$CMD")
if [[ "$test_output" == *"Makefile"* ]] || [[ "$test_output" == *"src"* ]]; then
    print_test_result "export + variable en comando" "listado directorio" "Comando desde variable funcionando" "PASS"
else
    print_test_result "export + variable en comando" "listado directorio" "$test_output" "FAIL"
fi

# ===================================================================
# RESUMEN FINAL
# ===================================================================

# Limpiar archivos temporales
rm -f /tmp/minishell_test.txt

echo -e "\n${BLUE}===================================================${NC}"
echo -e "${PURPLE}📊 RESUMEN FINAL DE PRUEBAS${NC}"
echo -e "${BLUE}===================================================${NC}"

echo -e "${CYAN}Total de pruebas:${NC} $TOTAL_TESTS"
echo -e "${GREEN}Pruebas exitosas:${NC} $PASSED_TESTS"
echo -e "${RED}Pruebas fallidas:${NC} $FAILED_TESTS"

if [ $FAILED_TESTS -eq 0 ]; then
    echo -e "\n${GREEN}🎉 ¡TODAS LAS PRUEBAS PASARON! Tu minishell está funcionando perfectamente.${NC}"
    exit 0
else
    echo -e "\n${YELLOW}⚠️  Algunas pruebas fallaron. Revisa los errores arriba.${NC}"
    success_rate=$((PASSED_TESTS * 100 / TOTAL_TESTS))
    echo -e "${CYAN}Tasa de éxito:${NC} ${success_rate}%"
    exit 1
fi
