# 🧪 PRUEBAS PARA PIPES Y REDIRECTIONS

## ✅ ERRORES DE SINTAXIS (Deben fallar como bash)

### 1. Pipe al inicio
```bash
| ls
# Esperado: bash: syntax error near unexpected token `|'
```

### 2. Pipe al final
```bash
ls |
# Esperado: bash: syntax error near unexpected token `|'
```

### 3. Pipes consecutivos
```bash
ls || pwd
# Esperado: bash: syntax error near unexpected token `|'
```

## ✅ PIPES BÁSICOS (Deben funcionar)

### 1. Pipe simple
```bash
echo "hello world" | wc -l
# Esperado: 1
```

### 2. Pipe con ls
```bash
ls | wc -l
# Esperado: número de archivos en directorio
```

### 3. Pipe con grep
```bash
echo -e "line1\nline2\nline3" | grep "line2"
# Esperado: line2
```

### 4. Múltiples pipes
```bash
ls | head -3 | tail -1
# Esperado: tercer archivo del directorio
```

## ✅ REDIRECTIONS BÁSICAS (Deben funcionar)

### 1. Redirección de salida
```bash
echo "test output" > test_file.txt
cat test_file.txt
# Esperado: test output
```

### 2. Redirección de entrada
```bash
echo "input content" > input.txt
wc -l < input.txt
# Esperado: 1
```

### 3. Append
```bash
echo "line1" > append_test.txt
echo "line2" >> append_test.txt
cat append_test.txt
# Esperado: line1\nline2
```

## ✅ PIPES + REDIRECTIONS (Combinados)

### 1. Pipe con redirección de salida
```bash
echo "hello" | tr 'a-z' 'A-Z' > upper.txt
cat upper.txt
# Esperado: HELLO
```

### 2. Redirección de entrada con pipe
```bash
echo "test line" > input_pipe.txt
cat < input_pipe.txt | wc -w
# Esperado: 2
```

### 3. Múltiples pipes con redirección
```bash
echo -e "apple\nbanana\ncherry" | grep "a" | wc -l > count.txt
cat count.txt
# Esperado: 2
```

## ✅ CASOS COMPLEJOS

### 1. Pipe con built-ins
```bash
pwd | cat
# Esperado: directorio actual
```

### 2. Echo con pipe
```bash
echo "testing pipes" | cat | cat
# Esperado: testing pipes
```

### 3. Múltiples redirecciones
```bash
echo "content" > file1.txt
cat < file1.txt > file2.txt
cat file2.txt
# Esperado: content
```

## 🧹 LIMPIEZA
```bash
rm -f test_file.txt input.txt append_test.txt upper.txt input_pipe.txt count.txt file1.txt file2.txt
```

## 🎯 INSTRUCCIONES DE USO

1. **Ejecuta tu minishell:**
   ```bash
   ./minishell
   ```

2. **Copia y pega cada comando** uno por uno en tu minishell

3. **Verifica que:**
   - ❌ Los errores de sintaxis muestren el mensaje correcto
   - ✅ Los pipes funcionen como en bash
   - ✅ Las redirections funcionen como en bash
   - ✅ Las combinaciones funcionen correctamente

4. **Si algo falla:**
   - Anota cuál comando falló
   - Describe qué comportamiento esperabas vs qué obtuviste
   - Usa los debugs para identificar el problema

## 🚀 COMANDOS RÁPIDOS PARA PROBAR

```bash
# Errores de sintaxis
| ls
ls |
ls || pwd

# Pipes básicos
echo "hello" | wc -l
ls | head -2

# Redirections
echo "test" > file.txt && cat file.txt
echo "append" >> file.txt && cat file.txt

# Combinados
echo "mix" | cat > mixed.txt && cat mixed.txt

# Limpieza
rm -f *.txt
```
