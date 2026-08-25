// DAA LAB-5, Q1 - Median WITHOUT sorting (Quickselect)
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

double findMedian(int A[], int N) {
    if (N % 2 != 0)
        return quickSelect(A, 0, N - 1, N / 2);

    int left  = quickSelect(A, 0, N - 1, N / 2 - 1);
    int right = quickSelect(A, 0, N - 1, N / 2);
    return (left + right) / 2.0;
}

void printArray(int A[], int N) {
    for (int i = 0; i < N; i++) printf("%d ", A[i]);
    printf("\n");
}

int main() {
    int N;
    printf("Enter N: ");
    scanf("%d", &N);

    int *A = malloc(N * sizeof(int));

    printf("Enter %d elements:\n", N);
    for (int i = 0; i < N; i++)
        scanf("%d", &A[i]);

    printf("\nOriginal array: ");
    printArray(A, N);

    // quickSelect partially rearranges A in-place; that's expected
    printf("Median = %.2f\n", findMedian(A, N));

    free(A);
    return 0;
}