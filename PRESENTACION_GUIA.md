# Guía de Presentación - Laboratorio 3: Programación Concurrente
**Duración: 3 minutos máximo**

---

## 📋 Estructura de la Presentación

### 1. PARTE 1: Paralelización de π (pi_p.c) - 60 segundos

#### Explicación de la Estrategia de Paralelización

**Mostrar archivo pi_p.c - líneas clave:**

```c
// Estructura para pasar datos a cada hilo (líneas 19-24)
typedef struct {
    int tid;           // ID del hilo
    int n;             // Total de iteraciones
    int num_threads;   // Número total de hilos
    double fH;         // Ancho del intervalo
} thread_arg_t;
```

**Puntos clave a explicar:**

1. **División del trabajo (líneas 34-43):**
   - El rango total [0, n-1] se divide entre T hilos
   - Cada hilo calcula su sub-rango: `start` y `end`
   - Si n no es divisible, los primeros hilos toman una iteración extra
   
   ```c
   int base = n / T;
   int rem = n % T;
   // Cada hilo calcula su rango específico
   ```

2. **Cálculo de suma parcial (líneas 45-50):**
   - Cada hilo calcula su suma local **sin mutex** (sin bloqueos)
   - Evita contención y maximiza el paralelismo
   
   ```c
   double local_sum = 0.0;
   for (i = start; i < end; ++i) {
       double x = fH * ((double)i + 0.5);
       local_sum += f(x);
   }
   ```

3. **Recolección de resultados (líneas 52-58 y 104-117):**
   - Cada hilo retorna su suma parcial mediante `pthread_exit(ret)`
   - El hilo principal usa `pthread_join` para recolectar todas las sumas
   - Suma final = `fH * total_sum`

---

### 2. PARTE 2: Generador de Fibonacci (fibonacci.c) - 60 segundos

#### Arreglo Compartido y Sincronización

**Mostrar archivo fibonacci.c - secciones clave:**

```c
// Estructura para pasar el arreglo compartido (líneas 5-8)
typedef struct {
    unsigned long long *arr;  // Puntero al arreglo compartido
    size_t n;                  // Cantidad de números a generar
} fib_arg_t;
```

**Puntos clave a explicar:**

1. **Memoria compartida (líneas 43-47):**
   ```c
   // Main aloca memoria que será compartida
   unsigned long long *arr = malloc(sizeof(unsigned long long) * N);
   ```

2. **Paso de datos al hilo (líneas 49-54):**
   - Se crea una estructura con el puntero al arreglo y el valor N
   - El hilo trabajador recibe esta estructura como argumento
   ```c
   fib_arg_t arg;
   arg.arr = arr;
   arg.n = N;
   pthread_create(&tid, NULL, worker, &arg);
   ```

3. **Sincronización con pthread_join (línea 61):**
   - `pthread_join` bloquea al hilo principal
   - Garantiza que el hilo trabajador termine antes de leer resultados
   - **Sin pthread_join, se accedería a datos no inicializados**
   
   ```c
   pthread_join(tid, NULL);  // Espera a que worker termine
   // Ahora es seguro imprimir el arreglo
   ```

4. **Generación en el hilo trabajador (líneas 10-27):**
   - Casos base: arr[0]=0, arr[1]=1
   - Loop que calcula arr[i] = arr[i-1] + arr[i-2]

---

### 3. DEMOSTRACIÓN - 60 segundos

#### Comandos a ejecutar en terminal:

```bash
# 1. Ejecutar versión serial de π
./pi_s 100000000

# 2. Ejecutar versión paralela con 1 hilo
./pi_p 100000000 1

# 3. Ejecutar versión paralela con 4 hilos (o 2x núcleos)
./pi_p 100000000 4

# 4. Ejecutar generador de Fibonacci
./fibonacci 15
```

**Qué mostrar en cada ejecución:**

1. **pi_s**: Tiempo de referencia serial (ej: ~0.400 segundos)
2. **pi_p con 1 hilo**: Tiempo similar al serial (pequeño overhead)
3. **pi_p con 4 hilos**: Tiempo **reducido** mostrando speedup (ej: ~0.120 segundos = 3.3x más rápido)
4. **fibonacci**: Secuencia correcta de números de Fibonacci

---

## 🎯 Script Sugerido para Narración

### Introducción (5 segundos)
"Buenos días/tardes. Voy a presentar mi implementación del Laboratorio 3 sobre programación concurrente con Pthreads."

### Parte 1 - pi_p.c (55 segundos)
"En la Parte 1, paralelicé el cálculo de π. La estrategia fue:

Primero, dividí el rango total de iteraciones entre T hilos. Cada hilo recibe su ID, el total de iteraciones, y el número de hilos mediante esta estructura.

Cada hilo calcula su sub-rango específico. Si hay un residuo, los primeros hilos toman una iteración extra para balancear la carga.

Cada hilo ejecuta su bucle independientemente, calculando una suma parcial local sin necesidad de mutex, lo que evita contención.

Finalmente, cada hilo retorna su suma parcial mediante pthread_exit. El hilo principal usa pthread_join para esperar y recolectar todas las sumas, y luego multiplica la suma total por fH para obtener π."

### Parte 2 - fibonacci.c (55 segundos)
"En la Parte 2, implementé un generador de Fibonacci con un hilo trabajador.

El hilo principal aloca memoria dinámica para un arreglo compartido que contendrá los N números de Fibonacci.

Este arreglo se pasa al hilo trabajador mediante una estructura que contiene el puntero al arreglo y el valor N.

El punto clave es la sincronización con pthread_join. Esta llamada bloquea al hilo principal hasta que el trabajador complete su ejecución. Sin esto, el hilo principal intentaría leer el arreglo antes de que los datos estén listos, causando un error.

El hilo trabajador genera la secuencia calculando cada elemento como la suma de los dos anteriores."

### Demostración (55 segundos)
"Ahora las demostraciones:

Primero ejecuto pi_s, la versión serial, que toma [mencionar tiempo].

Luego pi_p con 1 hilo, que tiene un tiempo similar con pequeño overhead.

Ahora pi_p con 4 hilos, que reduce el tiempo significativamente, mostrando un speedup de aproximadamente [calcular Ts/Tp].

Finalmente, fibonacci con 15 elementos genera la secuencia correcta.

Esto demuestra que la paralelización mejora el rendimiento en problemas divisibles. Gracias."

---

## 📊 Datos de Ejemplo para Mencionar

Si tu sistema tiene 4 núcleos y ejecutas con n=100000000:

| Versión | Hilos | Tiempo Aprox. | Speedup |
|---------|-------|---------------|---------|
| pi_s    | 1     | ~0.400s       | 1.0x    |
| pi_p    | 1     | ~0.420s       | 0.95x   |
| pi_p    | 2     | ~0.210s       | 1.9x    |
| pi_p    | 4     | ~0.120s       | 3.3x    |

Fibonacci(15): 0 1 1 2 3 5 8 13 21 34 55 89 144 233 377

---

## ✅ Checklist para la Grabación

- [ ] Tener los archivos pi_p.c y fibonacci.c abiertos en el editor
- [ ] Tener una terminal lista con el directorio del proyecto
- [ ] Compilar los programas antes de grabar
- [ ] Practicar el script al menos 2 veces
- [ ] Verificar que el tiempo total no exceda 3 minutos
- [ ] Asegurar buena iluminación y audio claro
- [ ] Probar la grabación con OBS, Zoom, o la herramienta que uses

---

## 🎬 Herramientas Recomendadas

- **Grabación de pantalla**: OBS Studio, Zoom, Microsoft PowerPoint (con grabación)
- **Editor de código**: VS Code con zoom para mejor visualización
- **Terminal**: Con fuente grande y colores claros
- **Edición**: Cortar pausas o errores con cualquier editor de video

---

## 💡 Consejos Adicionales

1. **Practica varias veces** antes de grabar
2. **Habla claramente** y a ritmo moderado
3. **Resalta las líneas de código** mientras las explicas
4. **Menciona números específicos** en la demostración (tiempos, speedup)
5. **Mantén un tono profesional** pero natural
6. Si te equivocas, **pausa y vuelve a grabar esa sección**

¡Éxito con tu presentación!
