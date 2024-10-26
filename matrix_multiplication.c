#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 512

void multiply_matrices(int A[N][N], int B[N][N], int C[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            C[i][j] = 0;
            for (int k = 0; k < N; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

void optimized_multiply_matrices(int A[N][N], int B[N][N], int C[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int k = 0; k < N; k++) {
            int temp = A[i][k];
            for (int j = 0; j < N; j++) {
                C[i][j] += temp * B[k][j];
            }
        }
    }
}

int main() {
    int A[N][N], B[N][N], C[N][N] = {0};

    srand(time(NULL));
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++) {
            A[i][j] = rand() % 10;
            B[i][j] = rand() % 10;
        }

    clock_t start = clock();
    multiply_matrices(A, B, C);
    clock_t end = clock();
    printf("Звичайне множення: %f сек\n", (double)(end - start) / CLOCKS_PER_SEC);

    start = clock();
    optimized_multiply_matrices(A, B, C);
    end = clock();
    printf("Оптимізоване множення: %f сек\n", (double)(end - start) / CLOCKS_PER_SEC);

    return 0;
}