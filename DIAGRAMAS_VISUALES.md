# 📊 Diagramas Visuales para la Presentación

## 1. Paralelización de π (pi_p.c)

### División del Trabajo (Data Parallelism)

```
Rango Total: [0 ... n-1]     n = 100,000,000
                |
                v
        División entre T=4 hilos
                |
    +------+------+------+------+
    |      |      |      |      |
    v      v      v      v      v
  Hilo0  Hilo1  Hilo2  Hilo3
  [0     [25M   [50M   [75M
   a      a      a      a
  25M)   50M)   75M)   100M)
    |      |      |      |
    v      v      v      v
  suma0  suma1  suma2  suma3
    |      |      |      |
    +------+------+------+
            |
            v
      pthread_join
            |
            v
     Suma Total = suma0 + suma1 + suma2 + suma3
            |
            v
        π = fH * Suma Total
```

### Flujo de Ejecución

```
MAIN Thread:
  1. Crea estructura thread_arg_t[4]
  2. pthread_create() × 4
     |
     +---> Worker Thread 0: calcula suma0 [0, 25M)
     |
     +---> Worker Thread 1: calcula suma1 [25M, 50M)
     |
     +---> Worker Thread 2: calcula suma2 [50M, 75M)
     |
     +---> Worker Thread 3: calcula suma3 [75M, 100M)
     |
  3. pthread_join() × 4  <--- Espera a todos
     |
  4. total = suma0 + suma1 + suma2 + suma3
  5. π = fH * total
```

---

## 2. Sincronización en Fibonacci (fibonacci.c)

### Modelo de Memoria Compartida

```
+------------------+
|   MAIN THREAD    |
+------------------+
        |
        v
   malloc(arr[N])  <--- Aloca memoria
        |
        v
   +----+----+
   | arr | N |  <--- fib_arg_t
   +----+----+
        |
        v
   pthread_create(&tid, NULL, worker, &arg)
        |
        v
   +------------------+       +------------------+
   |   MAIN THREAD    |       |  WORKER THREAD   |
   |    (BLOQUEADO)   |       |                  |
   |                  |       | arr[0] = 0       |
   | pthread_join(tid)|       | arr[1] = 1       |
   |       ↓          |       | for i=2 to N:    |
   |    ESPERANDO...  |       |   arr[i] =       |
   |                  |       |   arr[i-1] +     |
   |                  |       |   arr[i-2]       |
   |                  |       | pthread_exit()   |
   +------------------+       +------------------+
            ↑                          |
            |                          |
            +----------<---------------+
                 (worker termina)
                        |
                        v
   +------------------+
   |   MAIN THREAD    |
   |  (DESBLOQUEADO)  |
   +------------------+
        |
        v
   Imprime arr[0] hasta arr[N-1]  <--- SEGURO leer
```

### Cronología

```
Tiempo →

MAIN:   malloc → pthread_create → pthread_join (WAIT) → print arr
                        |                ↑
WORKER:                 └→ genera datos → pthread_exit
                           arr[0..N-1]

⚠️ SIN pthread_join: MAIN imprimiría antes de que datos estén listos!
```

---

## 3. Speedup Visualizado

### Comparación de Tiempos

```
pi_s (Serial):
[████████████████████████████████] 0.374s

pi_p (1 hilo):
[████████████████████████████████] 0.376s (overhead mínimo)

pi_p (4 hilos):
[████████████] 0.149s ⚡ SPEEDUP 2.5x
```

### Métricas de Rendimiento

```
Speedup = T_serial / T_parallel
        = 0.374s / 0.149s
        = 2.51x

Eficiencia = Speedup / Num_Hilos
           = 2.51 / 4
           = 62.75%
```

### ¿Por qué no es 4x con 4 hilos?

```
Factores limitantes:

1. [⚙️ Overhead]  Creación de hilos, sincronización
2. [🔄 Cache]     Competencia por memoria compartida
3. [📊 Amdahl]    Partes seriales (creación, suma final)
4. [⏰ Scheduler] SO gestiona múltiples procesos
```

---

## 4. Conceptos Clave (Para Mencionar)

### Data Parallelism
```
Un problema grande → Dividir en N partes → N hilos trabajan
                                         → Combinar resultados
```

### Ventajas de Suma Local (sin mutex)
```
❌ CON MUTEX:                    ✅ SIN MUTEX:
   Thread 1 → lock → sum → unlock   Thread 1 → local_sum1
   Thread 2 → WAIT → sum → unlock   Thread 2 → local_sum2
   Thread 3 → WAIT → sum → unlock   Thread 3 → local_sum3
   Thread 4 → WAIT → sum → unlock   Thread 4 → local_sum4
   (Serialización!)                 (Paralelismo real!)
                                    Main → suma1+suma2+suma3+suma4
```

### pthread_join como Barrera
```
pthread_join = BARRERA de sincronización

Main debe ESPERAR a que workers terminen
Garantiza visibilidad de datos
Evita condiciones de carrera
```

---

## 5. Fibonacci - Ejemplo Visual

```
Input: N = 10

Arreglo compartido (memoria):
+---+---+---+---+---+---+---+---+---+---+
| 0 | 1 | 1 | 2 | 3 | 5 | 8 | 13| 21| 34|
+---+---+---+---+---+---+---+---+---+---+
  ↑   ↑
  |   |
  |   +-- arr[1] = 1 (caso base)
  +------ arr[0] = 0 (caso base)

Para i >= 2:
arr[i] = arr[i-1] + arr[i-2]

Ejemplo: arr[5] = arr[4] + arr[3] = 3 + 2 = 5
```

---

## 💡 Cómo Usar Estos Diagramas

Durante la explicación, puedes:

1. **Describir verbalmente** estos diagramas mientras muestras el código
2. **Dibujar en una pizarra** si tienes una disponible
3. **Usar gestos con las manos** para mostrar la división y combinación
4. **Crear slides simples** con estos diagramas si usas PowerPoint

**No es necesario mostrar estos diagramas en pantalla**, pero tenerlos en mente
te ayudará a explicar claramente los conceptos.

---

## 🎯 Frases para Usar

- "Como si dividiéramos una tarea grande entre 4 personas"
- "Cada uno trabaja independientemente sin interferir con los demás"
- "Al final, juntamos todos los resultados"
- "pthread_join actúa como un punto de encuentro"
- "Sin esta sincronización, tendríamos un desastre de datos"
