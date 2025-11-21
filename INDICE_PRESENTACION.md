# 📚 Índice de Materiales para la Presentación

## Materiales Creados para tu Video de 3 Minutos

He preparado una serie completa de documentos para ayudarte a crear tu video de sustentación del Laboratorio 3. Aquí está todo lo que necesitas:

---

## 🎯 Orden Recomendado de Lectura

### 1. **TARJETA_REFERENCIA.md** ⭐ **EMPIEZA AQUÍ**
   - Resumen ultra-compacto en 1 página
   - Checklist de pre-grabación
   - Timing exacto de 3 minutos
   - Perfecto para tener visible durante la grabación

### 2. **SCRIPT_PRESENTACION.md** ⭐ **SCRIPT PRINCIPAL**
   - Script detallado cronometrado (1 min por sección)
   - Qué decir exactamente en cada parte
   - Comandos a ejecutar en la demo
   - Frases específicas para narrar

### 3. **DATOS_DEMO.md**
   - Resultados reales de las ejecuciones
   - Números exactos para mencionar
   - Análisis de speedup y eficiencia
   - Tabla resumen de performance

### 4. **PRESENTACION_GUIA.md**
   - Guía completa y detallada
   - Explicaciones en profundidad
   - Líneas de código específicas a mostrar
   - Consejos de grabación y herramientas

### 5. **DIAGRAMAS_VISUALES.md**
   - Diagramas ASCII para entender conceptos
   - Visualización de la paralelización
   - Flujos de ejecución
   - Comparativas visuales de speedup

---

## 📂 Estructura de Archivos

```
SO-Lab3-20252/
│
├── 📄 README.md                    # Instrucciones del lab (original)
│
├── 💻 Código fuente:
│   ├── pi.c                        # Versión serial
│   ├── pi_p.c                      # Versión paralela ⭐
│   └── fibonacci.c                 # Generador Fibonacci ⭐
│
├── 📦 Ejecutables:
│   ├── pi_s                        # Compilado de pi.c
│   ├── pi_p                        # Compilado de pi_p.c
│   └── fibonacci                   # Compilado de fibonacci.c
│
└── 🎬 Materiales de Presentación:
    ├── TARJETA_REFERENCIA.md      # Quick reference (1 página) ⭐
    ├── SCRIPT_PRESENTACION.md     # Script cronometrado ⭐
    ├── DATOS_DEMO.md              # Resultados reales ⭐
    ├── PRESENTACION_GUIA.md       # Guía completa
    └── DIAGRAMAS_VISUALES.md      # Visualizaciones
```

---

## 🎬 Pasos para Crear tu Video

### Preparación (15 minutos)
1. ✅ Lee **TARJETA_REFERENCIA.md** completo
2. ✅ Lee **SCRIPT_PRESENTACION.md** 
3. ✅ Revisa **DATOS_DEMO.md** para los números
4. ✅ Compila los programas si es necesario:
   ```bash
   gcc -o pi_s pi.c -lm
   gcc -o pi_p pi_p.c -lpthread -lm
   gcc -o fibonacci fibonacci.c -lpthread
   ```
5. ✅ Practica el script 2-3 veces con cronómetro

### Configuración (5 minutos)
1. ✅ Abre `pi_p.c` en tu editor de código
2. ✅ Abre `fibonacci.c` en otra pestaña
3. ✅ Abre una terminal en el directorio del proyecto
4. ✅ Aumenta el tamaño de fuente (editor y terminal)
5. ✅ Ten **TARJETA_REFERENCIA.md** visible en otra pantalla/ventana
6. ✅ Inicia tu software de grabación (OBS, Zoom, etc.)

### Grabación (3 minutos + intentos)
1. 🎥 Respira profundo
2. 🎥 Inicia la grabación
3. 🎥 Sigue el **SCRIPT_PRESENTACION.md**:
   - Minuto 1: Explica pi_p.c
   - Minuto 2: Explica fibonacci.c
   - Minuto 3: Ejecuta las demos
4. 🎥 Si cometes un error, pausa y vuelve a grabar esa sección

### Post-Producción (10 minutos)
1. ✅ Revisa el video completo
2. ✅ Edita pausas largas o errores
3. ✅ Verifica que el audio sea claro
4. ✅ Confirma que la duración sea ≤ 3 minutos
5. ✅ Exporta en calidad HD (1080p recomendado)

### Entrega
1. ✅ Sube a YouTube (puede ser "No listado")
2. ✅ Copia el enlace
3. ✅ Agrégalo en la primera celda de `analisis.ipynb`

---

## 💡 Consejos Rápidos

### ✅ Haz esto:
- Habla claramente y a ritmo moderado
- Señala con el cursor las líneas importantes
- Menciona números específicos (0.37s, speedup 2.5x)
- Mantén confianza y naturalidad
- Usa un fondo limpio y buena iluminación

### ❌ Evita esto:
- Hablar demasiado rápido (común cuando estás nervioso)
- Usar lenguaje muy técnico sin explicar
- Leer el código directamente sin contexto
- Olvidar mostrar los resultados de las ejecuciones
- Exceder los 3 minutos

---

## 📊 Datos Clave para Mencionar

### Parte 1 (pi_p.c):
- **Estrategia**: Data parallelism, división del rango entre hilos
- **Sin mutex**: Cada hilo suma localmente para evitar contención
- **Recolección**: pthread_join recoge sumas parciales al final

### Parte 2 (fibonacci.c):
- **Memoria compartida**: malloc en main, compartida con worker
- **pthread_join**: CLAVE para sincronización, evita lectura prematura
- **Algoritmo**: Iterativo, arr[i] = arr[i-1] + arr[i-2]

### Demostración:
- **Serial**: 0.374s
- **1 hilo**: 0.376s (overhead mínimo)
- **4 hilos**: 0.149s → **Speedup 2.51x** 🚀
- **Fibonacci**: Secuencia correcta 0,1,1,2,3,5,8,13,21,34,55,89,144,233,377

---

## 🎯 Objetivo del Video

Demostrar que:
1. ✅ Entiendes la estrategia de paralelización
2. ✅ Implementaste correctamente ambos programas
3. ✅ Comprendes la sincronización con pthreads
4. ✅ Los programas funcionan y muestran speedup
5. ✅ Puedes explicar conceptos técnicos claramente

---

## 🆘 ¿Necesitas Ayuda?

Si tienes dudas sobre:
- **Conceptos técnicos**: Revisa **DIAGRAMAS_VISUALES.md**
- **Qué decir**: Sigue **SCRIPT_PRESENTACION.md**
- **Números/datos**: Consulta **DATOS_DEMO.md**
- **Dudas generales**: Lee **PRESENTACION_GUIA.md**

---

## ✨ ¡Buena Suerte!

Tienes todo lo que necesitas para crear un excelente video. Los programas funcionan correctamente, los resultados son buenos, y tienes un speedup real de 2.5x que demuestra el beneficio del paralelismo.

**¡Confía en ti mismo y a grabar!** 🎬

---

*Todos los archivos están en el repositorio. Puedes imprimirlos o tenerlos abiertos durante la grabación.*
