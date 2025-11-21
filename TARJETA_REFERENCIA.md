# 🎯 Tarjeta de Referencia Rápida - Presentación

## ⏱️ TIMING (Total: 3 minutos)
```
0:00-1:00 → Parte 1: pi_p.c
1:00-2:00 → Parte 2: fibonacci.c
2:00-3:00 → Demostración
```

---

## 📝 PARTE 1: pi_p.c (1 min)

### Puntos clave:
1. ✅ **Estructura thread_arg_t** → Pasa datos a cada hilo
2. ✅ **División del rango** → Cada hilo calcula su sub-rango
3. ✅ **Suma local sin mutex** → Evita contención
4. ✅ **pthread_join recolecta** → Suma parciales al final

### Frase clave:
*"División de datos + sumas locales + recolección sin contención"*

---

## 📝 PARTE 2: fibonacci.c (1 min)

### Puntos clave:
1. ✅ **malloc en main** → Arreglo compartido
2. ✅ **fib_arg_t** → Pasa puntero + N al worker
3. ✅ **pthread_join** → CLAVE: sincronización, evita lectura prematura
4. ✅ **Worker genera** → Secuencia en arreglo compartido

### Frase clave:
*"Memoria compartida + sincronización con pthread_join"*

---

## 💻 DEMOSTRACIÓN (1 min)

### Comandos:
```bash
./pi_s 100000000          # Serial: 0.37s
./pi_p 100000000 1        # 1 hilo: 0.38s
./pi_p 100000000 4        # 4 hilos: 0.15s → Speedup 2.5x
./fibonacci 15            # Secuencia correcta
```

### Frase de cierre:
*"Speedup de 2.5x con 4 hilos demuestra los beneficios del paralelismo"*

---

## 🎬 CHECKLIST PRE-GRABACIÓN

**Compilación:**
```bash
gcc -o pi_s pi.c -lm
gcc -o pi_p pi_p.c -lpthread -lm
gcc -o fibonacci fibonacci.c -lpthread
```

**Configuración:**
- [ ] Fuente grande en editor
- [ ] Fuente grande en terminal
- [ ] Cerrar apps innecesarias
- [ ] Probar grabación 5 segundos
- [ ] Cronómetro visible

---

## 💡 RECORDATORIOS

✅ Señala con el cursor las líneas de código
✅ Habla claramente y pausadamente
✅ Espera a ver resultados completos
✅ Si te equivocas, pausa y regrabas
✅ Mantén confianza y naturalidad

---

## 🚀 ¡A GRABAR!

*Respira profundo, sonríe, y empieza cuando estés listo.*
