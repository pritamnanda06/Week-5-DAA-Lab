For Q1
------

Algorithm FindMedian(A, N):
    if N is odd:
        return QuickSelect(A, 0, N-1, (N/2))      // middle element
    else:
        left  = QuickSelect(A, 0, N-1, (N/2)-1)
        right = QuickSelect(A, 0, N-1, (N/2))
        return (left + right) / 2.0

Algorithm QuickSelect(A, low, high, k):    // k = 0-indexed rank we want
    if low == high:
        return A[low]

    pivotIndex = Partition(A, low, high)

    if k == pivotIndex:
        return A[k]
    else if k < pivotIndex:
        return QuickSelect(A, low, pivotIndex - 1, k)
    else:
        return QuickSelect(A, pivotIndex + 1, high, k)

Algorithm Partition(A, low, high):
    pivot = A[high]              // choose last element as pivot
    i = low - 1
    for j = low to high - 1:
        if A[j] <= pivot:
            i = i + 1
            swap(A[i], A[j])

How it works
Partition places the pivot at its correct sorted position, with all smaller elements to its left and all larger elements to its right — without fully sorting anything.
We then check: does the pivot's final index match the rank k we want?
If yes → that's our answer.
If k is smaller → recurse only on the left part.
If k is larger → recurse only on the right part.
Unlike Quicksort, we discard one half every time instead of recursing into both — this is what saves time.

## Complexity Analysis

| Case | Time Complexity | Reason |
|---|---|---|
| Best/Average Case | O(N) | Each partition step roughly halves the search space (like Quicksort's average case), giving a recurrence T(N) = T(N/2) + O(N), which solves to O(N) |
| Worst Case | O(N²) | If the pivot is always the smallest/largest element (e.g., already sorted input with last-element pivot), only one element is eliminated per step |
| Space Complexity | O(1) extra (iterative) or O(log N) (recursive call stack, average case) | In-place partitioning |
    swap(A[i+1], A[high])
    return i + 1                 // final position of pivot
