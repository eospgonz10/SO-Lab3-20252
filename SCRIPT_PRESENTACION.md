# Script de Presentación - 3 Minutos
## Laboratorio 3: Programación Concurrente con Pthreads

---

## 🎬 PARTE 1: Explicación pi_p.c (1 minuto)

### Mostrar en pantalla: `pi_p.c`

**Hablar mientras muestras el código:**

"En pi_p.c implementé la paralelización del cálculo de π mediante división de datos.

*[Mostrar struct thread_arg_t, líneas 19-24]*
Cada hilo recibe su ID, el número total de iteraciones, y el total de hilos.

*[Mostrar división del rango, líneas 34-43]*
El rango total se divide entre los hilos. Cada uno calcula su inicio y fin específico.

*[Mostrar bucle local_sum, líneas 45-50]*
Cada hilo ejecuta su bucle independientemente, acumulando en una variable local SIN mutex, evitando contención.

*[Mostrar pthread_join en main, líneas 104-117]*
Al finalizar, cada hilo retorna su suma parcial. El main usa pthread_join para recolectar todos los resultados y sumarlos."

---

## 🎬 PARTE 2: Explicación fibonacci.c (1 minuto)

### Mostrar en pantalla: `fibonacci.c`

**Hablar mientras muestras el código:**

"En fibonacci.c implementé un generador con memoria compartida.

*[Mostrar malloc en main, línea 43]*
El hilo principal aloca un arreglo dinámico que será compartido.

*[Mostrar fib_arg_t y paso de estructura, líneas 49-54]*
Paso el puntero al arreglo y el valor N al hilo trabajador mediante esta estructura.

*[Mostrar pthread_join, línea 61]*
pthread_join es CLAVE: bloquea al main hasta que el trabajador termine. Sin esto, leeríamos datos no inicializados.

*[Mostrar worker function, líneas 19-23]*
El trabajador genera la secuencia Fibonacci en el arreglo compartido usando el algoritmo iterativo estándar."

---

## 🎬 PARTE 3: Demostración (1 minuto)

### Mostrar en pantalla: Terminal

**Ejecutar y comentar:**

```bash
# Comando 1
./pi_s 100000000
```
*"Versión serial: toma [X] segundos"*

```bash
# Comando 2
./pi_p 100000000 1
```
*"Con 1 hilo: tiempo similar, pequeño overhead del threading"*

```bash
# Comando 3
./pi_p 100000000 4
```
*"Con 4 hilos: tiempo reducido a [Y] segundos, speedup de [X/Y]. Esto demuestra el beneficio del paralelismo"*

```bash
# Comando 4
./fibonacci 15
```
*"Fibonacci genera la secuencia correcta: 0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, 233, 377"*

**Cierre:**
"Esto demuestra que la paralelización mejora significativamente el rendimiento en problemas divisibles. Gracias."

---

## ⏱️ Timing Sugerido

- **0:00-1:00** - Parte 1: pi_p.c
- **1:00-2:00** - Parte 2: fibonacci.c  
- **2:00-3:00** - Demostración práctica

---

## 📝 Notas de Grabación

### Antes de grabar:
1. ✅ Compilar: `gcc -o pi_s pi.c -lm`
2. ✅ Compilar: `gcc -o pi_p pi_p.c -lpthread -lm`
3. ✅ Compilar: `gcc -o fibonacci fibonacci.c -lpthread`
4. ✅ Aumentar tamaño de fuente en editor y terminal
5. ✅ Cerrar aplicaciones innecesarias

### Durante la grabación:
- Habla claramente y a ritmo moderado
- Señala con el cursor las líneas que mencionas
- Si ejecutas comandos, espera a ver el resultado completo
- Mantén confianza y naturalidad

### Frases útiles:
- "Como pueden ver aquí..."
- "El punto clave es..."
- "Esto garantiza que..."
- "Observen cómo..."

¡Buena suerte!
