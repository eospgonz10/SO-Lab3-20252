#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct {
    unsigned long long *arr;
    size_t n;
} fib_arg_t;

void *worker(void *arg)
{
    fib_arg_t *a = (fib_arg_t*)arg;
    unsigned long long *arr = a->arr;
    size_t n = a->n;

    if (n == 0) {
        pthread_exit(NULL);
    }
    if (n >= 1) arr[0] = 0ULL;
    if (n >= 2) arr[1] = 1ULL;

    for (size_t i = 2; i < n; ++i) {
        arr[i] = arr[i-1] + arr[i-2];
    }

    pthread_exit(NULL);
}

int main(int argc, char **argv)
{
    if (argc < 2) {
        fprintf(stderr, "Usage: %s N\n", argv[0]);
        return 1;
    }

    long tmp = atol(argv[1]);
    if (tmp <= 0) {
        fprintf(stderr, "N must be a positive integer\n");
        return 1;
    }
    size_t N = (size_t)tmp;

    unsigned long long *arr = malloc(sizeof(unsigned long long) * N);
    if (!arr) {
        perror("malloc");
        return 1;
    }

    fib_arg_t arg;
    arg.arr = arr;
    arg.n = N;

    pthread_t tid;
    int rc = pthread_create(&tid, NULL, worker, &arg);
    if (rc) {
        fprintf(stderr, "Error creating thread: %d\n", rc);
        free(arr);
        return 1;
    }

    pthread_join(tid, NULL);

    for (size_t i = 0; i < N; ++i) {
        printf("%llu", arr[i]);
        if (i + 1 < N) printf(" ");
    }
    printf("\n");

    free(arr);
    return 0;
}
