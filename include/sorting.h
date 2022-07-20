#ifndef __SORTING_H__
#define __SORTING_H__

typedef int (*cmp_func)(const void *, const void *);

void BubbleSort(int *arr, int size);
void SelectionSort(int *arr, int size);
void InsertionSort(int *arr, int size);
int CountingSort(int *arr, int size);
int RadixSort(int *arr, int size);
int MergeSort(int *arr_to_sort, size_t num_elements);
int BinarySearchIterative(int *find_in, size_t size, int find);
int BinarySearchRecursion(int *find_in, size_t size, int find);
void QSort(void *base, int num_elements, int size, cmp_func cmp);
void HeapSort(int *arr, size_t size);
#endif /* __SORTING_H__ */
