#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 1024 * 1024

void sequential_access(int *array) {
    for (int i = 0; i < SIZE; i++) {
        array[i]++;
    }
}

void random_access(int *array) {
    for (int i = 0; i < SIZE; i++) {
        int index = rand() % SIZE;
        array[index]++;
    }
}

int main() {
    int *array = (int*)malloc(SIZE * sizeof(int));
    srand(time(NULL));

    clock_t start = clock();
    sequential_access(array);
    clock_t end = clock();
    printf("Послідовний доступ: %f сек\n", (double)(end - start) / CLOCKS_PER_SEC);

    start = clock();
    random_access(array);
    end = clock();
    printf("Випадковий доступ: %f сек\n", (double)(end - start) / CLOCKS_PER_SEC);

    free(array);
    return 0;
}