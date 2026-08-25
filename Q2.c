/*
 * DAA LAB-5, Q2
 * Find the K'th smallest element of a list of N numbers WITHOUT sorting the list.
 * Approach: Quickselect (based on Quicksort partitioning)
 *
 * Time Complexity : Best/Average - O(N), Worst - O(N^2)
 * Space Complexity: O(1) extra (iterative partition) + O(log N) avg recursion stack
 */

#include <stdio.h>
#include <stdlib.h>

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
 * QuickSelect function
 * Finds the element that would be at index k (0-indexed) if the array were sorted,
 * WITHOUT sorting the entire array.
 */
int quickSelect(int A[], int low, int high, int k) {
    if (low == high)
        return A[low];

    int pivotIndex = partition(A, low, high);

    if (k == pivotIndex)
        return A[k];
    else if (k < pivotIndex)
        return quickSelect(A, low, pivotIndex - 1, k);
    else
        return quickSelect(A, pivotIndex + 1, high, k);
}

/*
 * Finds the K'th smallest element of array A of size N (K is 1-indexed).
 * Returns the element, or exits with an error message if K is invalid.
 */
int kthSmallest(int A[], int N, int K) {
    if (K < 1 || K > N) {
        printf("Invalid value of K. K must be between 1 and %d.\n", N);
        exit(1);
    }
    return quickSelect(A, 0, N - 1, K - 1);   /* convert K to 0-indexed rank */
}

/* Utility function to print an array */
void printArray(int A[], int N) {
    for (int i = 0; i < N; i++)
        printf("%d ", A[i]);
    printf("\n");
}

int main() {
    int N, K;

    printf("Enter number of elements (N): ");
    scanf("%d", &N);

    int *A = (int *) malloc(N * sizeof(int));
    if (A == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    printf("Enter %d elements:\n", N);
    for (int i = 0; i < N; i++)
        scanf("%d", &A[i]);

    printf("Enter the value of K (1 to %d): ", N);
    scanf("%d", &K);

    printf("\nOriginal array: ");
    printArray(A, N);

    /* NOTE: quickSelect rearranges (partially permutes) the array in-place,
       since partitioning swaps elements. This is expected for this method. */
    int result = kthSmallest(A, N, K);

    printf("%d'th smallest element = %d\n", K, result);

    free(A);
    return 0;
}