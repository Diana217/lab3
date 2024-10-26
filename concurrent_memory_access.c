#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdatomic.h>

#define NUM_THREADS 4
#define NUM_INCREMENTS 1000000

volatile int volatile_counter = 0;
atomic_int atomic_counter = 0;

void* increment_volatile(void* arg) {
    for (int i = 0; i < NUM_INCREMENTS; i++) {
        volatile_counter++;
    }
    return NULL;
}

void* increment_atomic(void* arg) {
    for (int i = 0; i < NUM_INCREMENTS; i++) {
        atomic_fetch_add(&atomic_counter, 1);
    }
    return NULL;
}

int main() {
    pthread_t threads[NUM_THREADS];

    // Increment volatile
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_create(&threads[i], NULL, increment_volatile, NULL);
    }
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }
    printf("Результат volatile: %d (очікувано %d)\n", volatile_counter, NUM_THREADS * NUM_INCREMENTS);

    // Increment atomic
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_create(&threads[i], NULL, increment_atomic, NULL);
    }
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }
    printf("Результат atomic: %d (очікувано %d)\n", atomic_counter, NUM_THREADS * NUM_INCREMENTS);

    return 0;
}