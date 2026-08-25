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

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

For Q2
------

### Algorithm

```
Algorithm KthSmallest(A, N, K):
    // K is 1-indexed (1st smallest, 2nd smallest, ... )
    if K < 1 or K > N:
        return "Invalid K"
    return QuickSelect(A, 0, N-1, K-1)     // convert to 0-indexed rank

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
```

### How it Works
- `Partition` places the pivot at its correct sorted position, with all smaller 
  elements to its left and all larger elements to its right — without sorting 
  the rest of the array.
- Compare the pivot's final index to the target rank `k`:
  - If equal → pivot **is** the K'th smallest element, return it.
  - If `k` is smaller → recurse only on the **left** sub-array.
  - If `k` is larger → recurse only on the **right** sub-array.
- Only one half of the array is explored at each step, so we never need to 
  sort the entire list.

### Complexity Analysis

| Case | Time Complexity | Reason |
|---|---|---|
| Best/Average Case | O(N) | Search space roughly halves each partition step: T(N) = T(N/2) + O(N) → O(N) |
| Worst Case | O(N²) | Poor pivot choice (e.g., sorted input with last-element pivot) eliminates only one element per step |
| Space Complexity | O(1) extra (iterative) or O(log N) (recursive call stack, average case) | In-place partitioning |

------------------------------------------------------------------------------------------------------------------------------

For Q3
------

### Algorithm

```
Algorithm QuickSort(A, low, high):
    if low < high:
        pivotIndex = Partition(A, low, high)
        QuickSort(A, low, pivotIndex - 1)      // sort left sub-array
        QuickSort(A, pivotIndex + 1, high)     // sort right sub-array

Algorithm Partition(A, low, high):
    pivot = A[high]              // choose last element as pivot
    i = low - 1
    for j = low to high - 1:
        if A[j] <= pivot:
            i = i + 1
            swap(A[i], A[j])
    swap(A[i+1], A[high])
    return i + 1                 // final position of pivot
```

### Steps
1. Generate N random integers and write them to an input file (`input.txt`).
2. Read the N elements from the file into an array.
3. Apply `QuickSort` on the array in-place.
4. Write the sorted array to an output file (`output.txt`).

### Complexity Analysis

| Case | Time Complexity | Reason |
|---|---|---|
| Best Case | O(N log N) | Pivot always splits array into two roughly equal halves: T(N) = 2T(N/2) + O(N) |
| Average Case | O(N log N) | On random data, partitions are balanced on average |
| Worst Case | O(N²) | Pivot is always the smallest/largest element (e.g., sorted/reverse-sorted input), giving unbalanced partitions: T(N) = T(N-1) + O(N) |
| Space Complexity | O(log N) average, O(N) worst case | Recursive call stack depth (in-place partitioning, no extra array needed) |

--------------------------------------------------------------------------------------------------------------------------------------------------------------

For Q4
------

### Algorithm

```
Algorithm HeapSort(A, N):
    BuildMaxHeap(A, N)                      // Step 1: build max-heap
    for i = N-1 downto 1:
        swap(A[0], A[i])                    // move current max to the end
        Heapify(A, i, 0)                    // restore heap property on reduced heap

Algorithm BuildMaxHeap(A, N):
    for i = (N/2) - 1 downto 0:
        Heapify(A, N, i)

Algorithm Heapify(A, N, i):                 // ensures subtree rooted at i is a max-heap
    largest = i
    left  = 2*i + 1
    right = 2*i + 2

    if left < N and A[left] > A[largest]:
        largest = left
    if right < N and A[right] > A[largest]:
        largest = right

    if largest != i:
        swap(A[i], A[largest])
        Heapify(A, N, largest)              // recursively heapify the affected subtree
```


### Complexity Analysis

| Case | Time Complexity | Reason |
|---|---|---|
| Building the Heap | O(N) | Though a single `Heapify` call is O(log N), tighter analysis over all N/2 calls (most nodes are near the bottom, needing little work) sums to O(N) |
| Best Case | O(N log N) | Extracting max and re-heapifying (O(log N)) is repeated N times regardless of input arrangement |
| Average Case | O(N log N) | Same reasoning — heap operations are always O(log N), independent of data distribution |
| Worst Case | O(N log N) | Unlike Quicksort, Heap Sort has **no bad-input worst case** — always N extractions × O(log N) heapify |
| Space Complexity | O(1) extra (in-place) + O(log N) recursion stack for `Heapify` (or O(1) if implemented iteratively) | No auxiliary array needed |


