// DAA LAB-5, Q4 - Heap Sort on N random elements stored in a file
// Time: O(N log N) all cases | Space: O(1) + O(log N) recursion

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void swap(int *a, int *b) {
    int t = *a; *a = *b; *b = t;
}

// Fix max-heap property at index i
void heapify(int A[], int N, int i) {
    int largest = i, left = 2*i + 1, right = 2*i + 2;

    if (left < N && A[left] > A[largest]) largest = left;
    if (right < N && A[right] > A[largest]) largest = right;

    if (largest != i) {
        swap(&A[i], &A[largest]);
        heapify(A, N, largest);
    }
}

void heapSort(int A[], int N) {
    // Build max-heap
    for (int i = N/2 - 1; i >= 0; i--)
        heapify(A, N, i);

    // Extract max repeatedly
    for (int i = N - 1; i >= 1; i--) {
        swap(&A[0], &A[i]);
        heapify(A, i, 0);
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

    heapSort(A, N);

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