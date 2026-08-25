/*
 * DAA LAB-5, Q3
 * Implement Quick Sort of N random elements stored in a file.
 *
 * Flow:
 *   1. Generate N random integers, write them to "input.txt"
 *   2. Read the N elements from "input.txt" into an array
 *   3. Sort the array using QuickSort
 *   4. Write the sorted array to "output.txt"
 *
 * Time Complexity : Best/Average - O(N log N), Worst - O(N^2)
 * Space Complexity: O(log N) average (recursive call stack), O(N) worst case
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
 * Partition function (Lomuto partition scheme)
 * Places pivot (last element) at its correct sorted position,
 * with smaller elements to its left and larger elements to its right.
 * Returns the final index of the pivot.
 */
int partition(int A[], int low, int high) {
    int pivot = A[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (A[j] <= pivot) {
            i++;
            swap(&A[i], &A[j]);
        }
    }
    swap(&A[i + 1], &A[high]);
    return i + 1;
}

/*
 * QuickSort function - recursively sorts A[low..high] in place
 */
void quickSort(int A[], int low, int high) {
    if (low < high) {
        int pivotIndex = partition(A, low, high);
        quickSort(A, low, pivotIndex - 1);
        quickSort(A, pivotIndex + 1, high);
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

    /* Step 3: Sort using QuickSort */
    quickSort(A, 0, N - 1);

    printf("\nSorted array: ");
    printArray(A, N);

    /* Step 4: Write sorted array to output.txt */
    writeToFile(OUTPUT_FILE, A, N);
    printf("\nSorted elements written to \"%s\".\n", OUTPUT_FILE);

    free(A);
    return 0;
}