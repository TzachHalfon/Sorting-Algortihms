#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#include "sorting.h"
/*
typedef int (*compare)(const void *, const void *);
static int IntCompare(const void *, const void *); */
void PrintArray(int *arr, int size);
void CheckIfArrayIsSorted(int *arr, int size);

int main(void)
{
    int arr[] = {5, 4, 3, 2, 1};
    HeapSort(arr, 5);
    CheckIfArrayIsSorted(arr, 5);
    return 0;
}

/*
void InitializeArr(int *arr, int size);

int main(void)
{
    const int size = 50000;
    int arr[50000];
    clock_t start ,end;
    InitializeArr(arr, size);
    start = clock();
    BubbleSort(arr,size);
    end = clock();
    printf("Total time taken by CPU for BubbleSort: %ldms\n",(end-start) / (CLOCKS_PER_SEC / 1000));
    CheckIfArrayIsSorted(arr,size);
    InitializeArr(arr, size);
    start = clock();
    InsertionSort(arr,size);
    end = clock();
    printf("Total time taken by CPU for InsertionSort: %ldms\n",(end-start) / (CLOCKS_PER_SEC / 1000));
    CheckIfArrayIsSorted(arr,size);
    InitializeArr(arr, size);
    start = clock();
    SelectionSort(arr,size);
    end = clock();
    printf("Total time taken by CPU for SelectionSort: %ldms\n",(end-start) / (CLOCKS_PER_SEC / 1000));
    CheckIfArrayIsSorted(arr,size);
    InitializeArr(arr, size);
    start = clock();
    qsort(arr, size, sizeof(int), IntCompare);
    end = clock();
    printf("Total time taken by CPU for qsort: %ldms\n",(end-start) / (CLOCKS_PER_SEC / 1000));
    CheckIfArrayIsSorted(arr,size);
    return 0;
}


void InitializeArr(int *arr, int size)
{
    int i = 0;
    srand(time(NULL));
    for(i = 0; i < size; ++i)
    {
        arr[i] = rand() % 9999;
    }
}


static int IntCompare(const void *num1, const void *num2)
{
    return (*(int *)num1 - *(int *)num2);
}
*/
void CheckIfArrayIsSorted(int *arr, int size)
{
    int i = 0;
    for (i = 0; i < size - 1; ++i)
    {
        if (arr[i] > arr[i + 1])
        {
            printf("not sorted!\n");
            printf("%d %d\n", arr[i], arr[i + 1]);
            return;
        }
    }
    printf("sorted!\n");
}

void PrintArray(int *arr, int size)
{
    int i = 0;
    for (i = 0; i < size; ++i)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}
