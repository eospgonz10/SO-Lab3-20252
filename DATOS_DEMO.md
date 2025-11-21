# 📊 Datos Reales de Demostración

## Resultados de las Ejecuciones (en tu sistema)

### Sistema:
- **CPU Cores**: 4 núcleos
- **Valor de n**: 100,000,000 iteraciones

---

## 1. pi_s (Versión Serial)
```bash
./pi_s 100000000
```

**Resultado:**
```
pi is approximately = 3.14159265359042638721 
Error               = 0.00000000000063327121
CalcPi time (seconds): 0.374131
```

**Tiempo:** ~0.374 segundos

---

## 2. pi_p con 1 Hilo
```bash
./pi_p 100000000 1
```

**Resultado:**
```
pi is approximately = 3.14159265359042638721
Error               = 0.00000000000063327121
Threads: 1  n: 100000000
CalcPi time (seconds): 0.376209
```

**Tiempo:** ~0.376 segundos
**Speedup:** 0.374 / 0.376 = **0.99x** (overhead mínimo del threading)

---

## 3. pi_p con 4 Hilos
```bash
./pi_p 100000000 4
```

**Resultado:**
```
pi is approximately = 3.14159265358968253778
Error               = 0.00000000000011057821
Threads: 4  n: 100000000
CalcPi time (seconds): 0.149077
```

**Tiempo:** ~0.149 segundos
**Speedup:** 0.374 / 0.149 = **2.51x más rápido** 🚀
**Eficiencia:** 2.51 / 4 = 62.75%

---

## 4. fibonacci con 15 Elementos
```bash
./fibonacci 15
```

**Resultado:**
```
0 1 1 2 3 5 8 13 21 34 55 89 144 233 377
```

✅ Secuencia correcta de Fibonacci

---

## 🎯 Frases para Usar en la Presentación

### Al mostrar pi_s:
"La versión serial toma aproximadamente 0.37 segundos"

### Al mostrar pi_p con 1 hilo:
"Con un solo hilo, el tiempo es prácticamente igual, 0.38 segundos, mostrando un overhead mínimo del threading"

### Al mostrar pi_p con 4 hilos:
"Con 4 hilos, el tiempo se reduce dramáticamente a 0.15 segundos, logrando un speedup de 2.5 veces, con una eficiencia del 63%"

### Al mostrar fibonacci:
"El generador de Fibonacci produce correctamente los primeros 15 números de la secuencia"

---

## 📈 Tabla Resumen

| Programa | Hilos | Tiempo (s) | Speedup | Eficiencia |
|----------|-------|------------|---------|------------|
| pi_s     | 1     | 0.374      | 1.00x   | 100%       |
| pi_p     | 1     | 0.376      | 0.99x   | 99%        |
| pi_p     | 4     | 0.149      | 2.51x   | 63%        |

---

## 💡 Análisis Rápido

**¿Por qué el speedup es 2.51x y no 4x con 4 cores?**

1. **Overhead de sincronización**: Creación de hilos, pthread_join
2. **Memoria compartida**: Acceso a cache compartida entre cores
3. **Ley de Amdahl**: Partes del programa que no se pueden paralelizar
4. **Scheduling del SO**: El sistema operativo gestiona múltiples procesos

**Aún así, es una mejora significativa del 151%** ✅

---

## 🎬 Recomendación de Narración

"Como pueden observar, la versión serial toma 0.37 segundos. Con un hilo paralelo el tiempo es similar, pero al usar los 4 núcleos disponibles, reducimos el tiempo a 0.15 segundos, logrando un speedup de 2.5 veces. Aunque no es un speedup lineal perfecto de 4x debido al overhead de sincronización y la ley de Amdahl, es una mejora sustancial que demuestra los beneficios del paralelismo."
