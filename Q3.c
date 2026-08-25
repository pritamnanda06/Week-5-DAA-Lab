// DAA LAB-5, Q3 - Quick Sort on N random elements stored in a file
// Time: Best/Avg O(N log N), Worst O(N^2) | Space: O(log N) avg, O(N) worst

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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

void quickSort(int A[], int low, int high) {
    if (low < high) {
        int p = partition(A, low, high);
        quickSort(A, low, p - 1);
        quickSort(A, p + 1, high);
    }
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

    // Generate random elements and write to input.txt
    srand(time(NULL));
    FILE *in = fopen("input.txt", "w");
    for (int i = 0; i < N; i++) {
        A[i] = rand() % 10000;
        fprintf(in, "%d\n", A[i]);
    }
    fclose(in);

    printf("\nUnsorted: ");
    printArray(A, N);

    quickSort(A, 0, N - 1);

    printf("Sorted:   ");
    printArray(A, N);

    // Write sorted result to output.txt
    FILE *out = fopen("output.txt", "w");
    for (int i = 0; i < N; i++)
        fprintf(out, "%d\n", A[i]);
    fclose(out);

    free(A);
    return 0;
}