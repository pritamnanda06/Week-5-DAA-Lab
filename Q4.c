/*
 * DAA LAB-5, Q4
 * Implement Heap Sort on N randomly generated elements stored in a file.
 *
 * Flow:
 *   1. Generate N random integers, write them to "input.txt"
 *   2. Read the N elements from "input.txt" into an array
 *   3. Sort the array using HeapSort
 *   4. Write the sorted array to "output.txt"
 *
 * Time Complexity : O(N log N) in ALL cases (best, average, worst)
 * Space Complexity: O(1) extra (in-place) + O(log N) recursion stack for Heapify
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define INPUT_FILE  "input.txt"
#define OUTPUT_FILE "output.txt"
#define MAX_RANDOM_VALUE 10000

/* Swap two elements */
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

/*
 * Heapify function
 * Ensures the subtree rooted at index i (within a heap of size N) satisfies
 * the max-heap property. Assumes the subtrees rooted at the children of i
 * are already max-heaps.
 */
void heapify(int A[], int N, int i) {
    int largest = i;
    int left  = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < N && A[left] > A[largest])
        largest = left;

    if (right < N && A[right] > A[largest])
        largest = right;

    if (largest != i) {
        swap(&A[i], &A[largest]);
        heapify(A, N, largest);   /* recursively fix the affected subtree */
    }
}

/*
 * BuildMaxHeap function
 * Converts array A of size N into a max-heap.
 * Starts from the last non-leaf node and heapifies each node up to the root.
 */
void buildMaxHeap(int A[], int N) {
    for (int i = (N / 2) - 1; i >= 0; i--)
        heapify(A, N, i);
}

/*
 * HeapSort function
 * Sorts array A of size N in ascending order using Heap Sort.
 */
void heapSort(int A[], int N) {
    buildMaxHeap(A, N);

    for (int i = N - 1; i >= 1; i--) {
        swap(&A[0], &A[i]);   /* move current max to the end */
        heapify(A, i, 0);     /* restore heap property on reduced heap */
    }
}

/*
 * Generates N random integers and writes them to the input file,
 * one element per line.
 */
void generateRandomFile(const char *filename, int N) {
    FILE *fp = fopen(filename, "w");
    if (fp == NULL) {
        printf("Error: could not open %s for writing.\n", filename);
        exit(1);
    }

    srand((unsigned int) time(NULL));
    for (int i = 0; i < N; i++) {
        int value = rand() % MAX_RANDOM_VALUE;
        fprintf(fp, "%d\n", value);
    }

    fclose(fp);
}

/*
 * Reads N integers from the input file into array A.
 */
void readFromFile(const char *filename, int A[], int N) {
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Error: could not open %s for reading.\n", filename);
        exit(1);
    }

    for (int i = 0; i < N; i++) {
        if (fscanf(fp, "%d", &A[i]) != 1) {
            printf("Error: file has fewer than %d elements.\n", N);
            fclose(fp);
            exit(1);
        }
    }

    fclose(fp);
}

/*
 * Writes N integers from array A to the output file, one per line.
 */
void writeToFile(const char *filename, int A[], int N) {
    FILE *fp = fopen(filename, "w");
    if (fp == NULL) {
        printf("Error: could not open %s for writing.\n", filename);
        exit(1);
    }

    for (int i = 0; i < N; i++)
        fprintf(fp, "%d\n", A[i]);

    fclose(fp);
}

/* Utility function to print an array to console */
void printArray(int A[], int N) {
    for (int i = 0; i < N; i++)
        printf("%d ", A[i]);
    printf("\n");
}

int main() {
    int N;

    printf("Enter number of random elements (N): ");
    scanf("%d", &N);

    if (N <= 0) {
        printf("N must be a positive integer.\n");
        return 1;
    }

    int *A = (int *) malloc(N * sizeof(int));
    if (A == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    /* Step 1: Generate N random elements and store them in input.txt */
    generateRandomFile(INPUT_FILE, N);
    printf("\n%d random elements generated and stored in \"%s\".\n", N, INPUT_FILE);

    /* Step 2: Read the elements back from the file */
    readFromFile(INPUT_FILE, A, N);

    printf("\nUnsorted array (read from file): ");
    printArray(A, N);

    /* Step 3: Sort using HeapSort */
    heapSort(A, N);

    printf("\nSorted array: ");
    printArray(A, N);

    /* Step 4: Write sorted array to output.txt */
    writeToFile(OUTPUT_FILE, A, N);
    printf("\nSorted elements written to \"%s\".\n", OUTPUT_FILE);

    free(A);
    return 0;
}