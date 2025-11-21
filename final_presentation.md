# Guión para Video de 3 Minutos: Paralelización en C

**(Música de fondo suave)**

---

### **Introducción (0:00 - 0:20)**

**[Escena: Título en pantalla: "Computación Paralela: Pi y Fibonacci en C"]**

**Anfitrión:**
¡Hola a todos! En este video, exploraremos cómo la programación paralela puede acelerar nuestros cálculos. Veremos dos ejemplos en C: una aproximación de Pi y la generación de la secuencia de Fibonacci, utilizando la librería Pthreads.

---

### **Parte 1: Explicación del Código - `pi_p.c` (0:20 - 1:10)**

**[Escena: Mostrando el código de `pi_p.c`, específicamente la función `thread_func`]**

**Anfitrión:**
Primero, veamos cómo calculamos Pi de forma paralela. La idea es dividir un bucle de cálculo muy grande entre varios hilos para repartir el trabajo.

En `pi_p.c`, cada hilo ejecuta la función `thread_func`. Aquí, distribuimos las iteraciones del bucle de forma equitativa.

**[Señalar el bloque de código que calcula `start` y `end`]**

Calculamos un `start` y un `end` para el bucle de cada hilo, asegurando que cada uno procese una porción única del total de `n` iteraciones.

**[Señalar el bucle `for` dentro de `thread_func`]**

Cada hilo calcula una suma local.

**[Escena: Cambiar al `main` y mostrar el bucle `pthread_join`]**

Finalmente, en la función `main`, esperamos a que todos los hilos terminen y recolectamos sus sumas parciales. Sumamos todo y obtenemos nuestra aproximación final de Pi. ¡Simple y efectivo!

---

### **Parte 2: Explicación del Código - `fibonacci.c` (1:10 - 1:50)**

**[Escena: Mostrando el código de `fibonacci.c`, la estructura `fib_arg_t` y la función `worker`]**

**Anfitrión:**
Ahora, para Fibonacci. Aquí, el desafío es diferente: un solo hilo de trabajo debe llenar un arreglo que será leído por el hilo principal.

Implementamos esto pasando un puntero a un arreglo compartido. La estructura `fib_arg_t` contiene este puntero y el tamaño de la secuencia.

**[Señalar la función `worker`]**

El hilo trabajador (`worker`) recibe esta estructura, y simplemente llena el arreglo con la secuencia de Fibonacci.

**[Escena: Cambiar al `main` y mostrar `pthread_create` y `pthread_join`]**

La sincronización es crucial. El hilo principal crea el hilo trabajador y luego usa `pthread_join`. Esta función bloquea al hilo principal, forzándolo a esperar a que el trabajador termine. Una vez que `pthread_join` retorna, sabemos que el arreglo está lleno y es seguro imprimir los resultados.

---

### **Parte 3: Demostración (1:50 - 2:45)**

**[Escena: Terminal de comandos]**

**Anfitrión:**
¡Vamos a la demostración! Primero, compilamos nuestro código.

**(Comando: `gcc -o pi_s pi.c -lm && gcc -o pi_p pi_p.c -lm -pthread && gcc -o fibonacci fibonacci.c -pthread`)**

**Anfitrión:**
Ahora, ejecutemos la versión secuencial de Pi con 2 mil millones de iteraciones.

**(Comando: `./pi_s 2000000000`)**
*Observamos el tiempo que tarda.*

**Anfitrión:**
Ahora, la versión paralela, primero con un solo hilo. El tiempo debería ser muy similar.

**(Comando: `./pi_p 2000000000 1`)**
*Vemos un tiempo parecido, quizás con una pequeña sobrecarga.*

**Anfitrión:**
¡Ahora con 8 hilos!

**(Comando: `./pi_p 2000000000 8`)**
*El tiempo de ejecución se reduce drásticamente. ¡Ese es el poder del paralelismo!*

**Anfitrión:**
Finalmente, generemos los primeros 20 números de Fibonacci.

**(Comando: `./fibonacci 20`)**
*La salida muestra la secuencia correcta.*

---

### **Conclusión (2:45 - 3:00)**

**[Escena: Anfitrión hablando a la cámara]**

**Anfitrión:**
Como hemos visto, la paralelización es una herramienta poderosa. Ya sea dividiendo un gran problema en partes más pequeñas o coordinando tareas, Pthreads nos da el control para optimizar nuestro código.

¡Gracias por acompañarme! ¡Hasta la próxima!

**(Música sube y se desvanece)**
