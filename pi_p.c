#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#include <time.h>

double f(double a)
{
    return (4.0 / (1.0 + a*a));
}

double GetTime()
{
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return ts.tv_sec + ts.tv_nsec * 1e-9;
}

typedef struct {
    int tid;
    int n;
    int num_threads;
    double fH;
} thread_arg_t;

void *thread_func(void *arg)
{
    thread_arg_t *a = (thread_arg_t*)arg;
    int tid = a->tid;
    int n = a->n;
    int T = a->num_threads;
    double fH = a->fH;

    int base = n / T;
    int rem = n % T;
    int start, end;
    if (tid < rem) {
        start = tid * (base + 1);
        end = start + (base + 1);
    } else {
        start = tid * base + rem;
        end = start + base;
    }

    double local_sum = 0.0;
    int i;
    for (i = start; i < end; ++i) {
        double x = fH * ((double)i + 0.5);
        local_sum += f(x);
    }

    double *ret = malloc(sizeof(double));
    if (!ret) {
        perror("malloc");
        pthread_exit(NULL);
    }
    *ret = local_sum;
    pthread_exit(ret);
}

int main(int argc, char **argv)
{
    int n = 2000000000; /* default same as original */
    int num_threads = 1;

    if (argc >= 2) {
        n = atoi(argv[1]);
    }
    if (argc >= 3) {
        num_threads = atoi(argv[2]);
    }

    if (n <= 0 || n > 2147483647) {
        fprintf(stderr, "given value has to be between 0 and 2147483647\n");
        return 1;
    }
    if (num_threads <= 0) num_threads = 1;

    const double fPi25DT = 3.141592653589793238462643;
    double fH = 1.0 / (double)n;

    pthread_t *threads = malloc(sizeof(pthread_t) * num_threads);
    thread_arg_t *args = malloc(sizeof(thread_arg_t) * num_threads);
    if (!threads || !args) {
        perror("malloc");
        return 1;
    }

    double tstart = GetTime();

    int i;
    for (i = 0; i < num_threads; ++i) {
        args[i].tid = i;
        args[i].n = n;
        args[i].num_threads = num_threads;
        args[i].fH = fH;
        int rc = pthread_create(&threads[i], NULL, thread_func, &args[i]);
        if (rc) {
            fprintf(stderr, "Error creating thread %d: %d\n", i, rc);
            return 1;
        }
    }

    double total_sum = 0.0;
    for (i = 0; i < num_threads; ++i) {
        void *res;
        int rc = pthread_join(threads[i], &res);
        if (rc) {
            fprintf(stderr, "Error joining thread %d: %d\n", i, rc);
            return 1;
        }
        if (res) {
            double *partial = (double*)res;
            total_sum += *partial;
            free(partial);
        }
    }

    double pi = fH * total_sum;
    double tend = GetTime();

    printf("\npi is approximately = %.20f\n", pi);
    printf("Error               = %.20f\n", fabs(pi - fPi25DT));
    printf("Threads: %d  n: %d\n", num_threads, n);
    printf("CalcPi time (seconds): %.6f\n", tend - tstart);

    free(threads);
    free(args);
    return 0;
}
