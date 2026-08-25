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
    swap(A[i+1], A[high])
    return i + 1                 // final position of pivot
