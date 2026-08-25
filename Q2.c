// DAA LAB-5, Q2 - Kth smallest element WITHOUT sorting (Quickselect)
// Time: Best/Avg O(N), Worst O(N^2) | Space: O(1) + O(log N) avg recursion

#include <stdio.h>
#include <stdlib.h>

void swap(int *a, int *b) {
    int t = *a; *a = *b; *b = t;
}

// Lomuto partition - places pivot at correct sorted position
int partition(int A[], int low, int high) {
    int pivot = A[high], i = low - 1;

    for (int j = low; j < high; j++) {
        if (A[j] <= pivot) {
            i++;
            swap(&A[i], &A[j]);
        }
    }
    swap(&A[i + 1], &A[high]);
    return i + 1;
}

// Finds element at 0-indexed rank k without sorting the whole array
int quickSelect(int A[], int low, int high, int k) {
    if (low == high) return A[low];

    int p = partition(A, low, high);

    if (k == p) return A[k];
    if (k < p)  return quickSelect(A, low, p - 1, k);
    return quickSelect(A, p + 1, high, k);
}

void printArray(int A[], int N) {
    for (int i = 0; i < N; i++) printf("%d ", A[i]);
    printf("\n");
}

int main() {
    int N, K;
    printf("Enter N: ");
    scanf("%d", &N);

    int *A = malloc(N * sizeof(int));

    printf("Enter %d elements:\n", N);
    for (int i = 0; i < N; i++)
        scanf("%d", &A[i]);

    printf("Enter K (1 to %d): ", N);
    scanf("%d", &K);

    printf("\nOriginal array: ");
    printArray(A, N);

    // quickSelect partially rearranges A in-place; that's expected
    int result = quickSelect(A, 0, N - 1, K - 1);
    printf("%d'th smallest element = %d\n", K, result);

    free(A);
    return 0;
}