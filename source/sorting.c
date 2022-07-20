/*============================LIBRARIES && MACROS ================================*/
#include <stdlib.h> /*malloc free*/
#include <string.h> /*memcpy*/
#include <stdio.h>

#include "sorting.h"

#define FAIL 0
#define SUCCESS 1
#define FALSE_INDEX -1

/*========================== FUNCTION DECLARATION ================================*/
static void GetMinAndMax(int *arr, int size, int *max, int *min);
static int CountingSortForRadix(int *arr, int size, int exp);
static int GetNumOfDigit(int num);
void IndexPlacment(int *arr, int size);
static int MergeSortRec(int *arr_to_sort, size_t start, size_t end);
static int Merge(int *old_array, size_t start, size_t end);
static int BinarySearch(int *find_in, int find, int high, int mid, int low);
static void QSortRec(void *base, cmp_func cmp, int size, int low, int high);
static int Partition(void *base, cmp_func cmp, int size, int low, int high);
void Swap(void *data1, void *data2, int ele_size);
static void HeapifyDown(int *arr, size_t index, size_t last_index);
void SwapInt(int *data1, int *data2);

/*============================= FUNCTION DEFINITION ==============================*/
void BubbleSort(int *arr, int size)
{
    int i = 0;
    int j = 0;
    int temp = 0;
    int is_swapped = 0;
    for (i = 0; i < size - 1; ++i)
    {
        is_swapped = 0;
        for (j = 0; j < size - i - 1; ++j)
        {
            if (arr[j] > arr[j + 1])
            {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                is_swapped = 1;
            }
        }
        if (0 == is_swapped)
        {
            break;
        }
    }
}

void SelectionSort(int *arr, int size)
{
    int i = 0;
    int j = 0;
    int temp = 0;
    int smallest = 0;

    for (i = 0; i < size - 1; ++i)
    {
        smallest = i;
        for (j = i; j < size; ++j)
        {
            if (arr[smallest] > arr[j])
            {
                smallest = j;
            }
        }
        temp = arr[i];
        arr[i] = arr[smallest];
        arr[smallest] = temp;
    }
}

void InsertionSort(int *arr, int size)
{
    int i = 1;
    int j = 0;
    int current = 0;

    for (i = 1; i < size; ++i)
    {
        current = arr[i];
        for (j = i - 1; j >= 0; --j)
        {
            if (!(current < arr[j]))
            {
                break;
            }
            arr[j + 1] = arr[j];
        }
        arr[j + 1] = current;
    }
}

int CountingSort(int *arr, int size)
{
    int *count_val = NULL;
    int *temp_arr = NULL;
    int i = 0;
    int max = 0;
    int min = 0;
    int range = 0;
    GetMinAndMax(arr, size, &max, &min);
    range = max - min + 1;

    count_val = (int *)calloc((range), sizeof(int));
    if (NULL == count_val)
    {
        return (FAIL);
    }
    temp_arr = (int *)calloc(size, sizeof(int));
    if (NULL == temp_arr)
    {
        return (FAIL);
    }

    for (i = 0; i < size; ++i)
    {
        ++count_val[arr[i] - min];
    }

    for (i = 1; i < range; ++i)
    {
        count_val[i] += count_val[i - 1];
    }

    for (i = range - 1; i > 0; --i)
    {
        count_val[i] = count_val[i - 1];
    }
    count_val[0] = 0;

    for (i = 0; i < size; ++i)
    {
        temp_arr[count_val[arr[i] - min]] = arr[i];
        ++count_val[arr[i] - min];
    }

    for (i = 0; i < size; ++i)
    {
        arr[i] = temp_arr[i];
    }

    free(count_val);
    free(temp_arr);
    return (SUCCESS);
}

int RadixSort(int *arr, int size)
{
    int i = 0;
    int max = 0;
    int num_digits = 0;
    int status = SUCCESS;
    int exp = 1;
    GetMinAndMax(arr, size, &max, &i);
    num_digits = GetNumOfDigit(max);

    for (i = 0; i < num_digits && status == SUCCESS; ++i, exp *= 10)
    {
        status = CountingSortForRadix(arr, size, exp);
    }
    if (SUCCESS != status)
    {
        return (FAIL);
    }
    return (SUCCESS);
}

static int CountingSortForRadix(int *arr, int size, int exp)
{
    int i = 0;
    int range = 10;
    int *temp_arr = NULL;
    int count_val[10] = {0};

    temp_arr = (int *)calloc(size, sizeof(int));
    if (NULL == temp_arr)
    {
        return (FAIL);
    }

    for (i = 0; i < size; ++i)
    {
        ++count_val[(arr[i] / exp) % 10];
    }

    IndexPlacment(count_val, range);

    for (i = 0; i < size; ++i)
    {
        temp_arr[count_val[(arr[i] / exp) % 10]] = arr[i];
        ++count_val[(arr[i] / exp) % 10];
    }

    for (i = 0; i < size; ++i)
    {
        arr[i] = temp_arr[i];
    }

    free(temp_arr);

    return (SUCCESS);
}

void IndexPlacment(int *arr, int size)
{
    int i = 1;
    for (i = 1; i < size; ++i)
    {
        arr[i] += arr[i - 1];
    }

    for (i = size - 1; i > 0; --i)
    {
        arr[i] = arr[i - 1];
    }
    arr[0] = 0;
}

static int GetNumOfDigit(int num)
{
    int num_digits = 0;
    while (num > 0)
    {
        ++num_digits;
        num /= 10;
    }
    return (num_digits);
}

static void GetMinAndMax(int *arr, int size, int *max, int *min)
{
    int temp_max = arr[0];
    int temp_min = arr[0];
    int i = 0;

    for (i = 0; i < size; ++i)
    {
        if (temp_max < arr[i])
        {
            temp_max = arr[i];
        }
        if (temp_min > arr[i])
        {
            temp_min = arr[i];
        }
    }

    *max = temp_max;
    *min = temp_min;
}

int BinarySearchIterative(int *find_in, size_t size, int find)
{
    int middle;
    int lower = 0;
    int upper = size - 1;
    do
    {
        middle = (lower + upper) / 2;
        (find_in[middle] > find) ? (upper = (middle - 1)) : (lower = (middle + 1));

    } while ((find_in[middle] != find) && (lower <= upper));

    return ((find_in[middle] == find) ? middle : (FALSE_INDEX));
}

int BinarySearchRecursion(int *find_in, size_t size, int find)
{
    return (BinarySearch(find_in, find, (size - 1), ((size - 1) / 2), 0));
}

static int BinarySearch(int *find_in, int find, int high, int mid, int low)
{
    if (high <= low)
    {
        return (FALSE_INDEX);
    }
    if (find_in[mid] == find)
    {
        return (mid);
    }
    else if (find_in[mid] > find)
    {
        return BinarySearch(find_in, find, mid - 1, mid + low / 2, low);
    }
    else
    {
        return BinarySearch(find_in, find, high, mid + high / 2, mid + 1);
    }
}

int MergeSort(int *arr_to_sort, size_t num_elements)
{
    return MergeSortRec(arr_to_sort, 0, num_elements - 1);
}

static int MergeSortRec(int *arr_to_sort, size_t start, size_t end)
{
    int mid = (end + start) / 2;
    if (start < end)
    {
        if (SUCCESS != MergeSortRec(arr_to_sort, start, mid))
        {
            return (FAIL);
        }
        if (SUCCESS != MergeSortRec(arr_to_sort, mid + 1, end))
        {
            return (FAIL);
        }
        return Merge(arr_to_sort, start, end);
    }
    return (SUCCESS);
}

static int Merge(int *old_array, size_t start, size_t end)
{
    int mid = (end + start) / 2;
    int right_size = end - mid;
    int left_size = mid - start + 1;
    int i = 0;
    int left = 0;
    int right = 0;
    int *left_arr;
    int *right_arr;

    left_arr = (int *)malloc(sizeof(int) * left_size);
    if (left_arr == NULL)
    {
        return (FAIL);
    }
    right_arr = (int *)malloc(sizeof(int) * right_size);
    if (right_arr == NULL)
    {
        free(left_arr);
        return (FAIL);
    }

    for (left = 0; left < left_size; ++left)
    {
        left_arr[left] = old_array[left + start];
    }
    for (right = 0; right < right_size; ++right)
    {
        right_arr[right] = old_array[right + mid + 1];
    }

    right = 0;
    left = 0;
    i = start;
    while (left < left_size && right < right_size)
    {
        if (left_arr[left] < right_arr[right])
        {
            old_array[i] = left_arr[left];
            left++;
        }
        else
        {
            old_array[i] = right_arr[right];
            right++;
        }
        i++;
    }

    while (left < left_size)
    {
        old_array[i] = left_arr[left];
        i++;
        left++;
    }

    while (right < right_size)
    {
        old_array[i] = right_arr[right];
        i++;
        right++;
    }

    free(left_arr);
    free(right_arr);
    return (SUCCESS);
}

void QSort(void *base, int num_elements, int size, cmp_func cmp)
{
    QSortRec(base, cmp, size, 0, num_elements - 1);
}

static void QSortRec(void *base, cmp_func cmp, int ele_size, int low, int high)
{
    int pivot;
    if (low < high)
    {
        pivot = Partition(base, cmp, ele_size, low, high);

        QSortRec(base, cmp, ele_size, low, pivot - 1);
        QSortRec(base, cmp, ele_size, pivot + 1, high);
    }
}

static int Partition(void *base, cmp_func cmp, int ele_size, int low, int high)
{
    int pivot = high;
    int i = low, j = low;
    char *arr = (char *)base;

    for (j = low; j < high; ++j)
    {
        if (0 >= cmp(&arr[(ele_size * j)], &arr[(ele_size * pivot)]))
        {
            Swap(&arr[(ele_size * i)], &arr[(ele_size * j)], ele_size);
            ++i;
        }
    }
    Swap(&arr[(ele_size * i)], &arr[(ele_size * pivot)], ele_size);

    return (i);
}

void HeapSort(int *arr, size_t size)
{
    int i;
    for (i = ((size / 2) - 1); i >= 0; --i)
    {
        HeapifyDown(arr, i, size);
    }

    for (i = (size - 1); i >= 0; --i)
    {
        printf("%d %d %d %d %d\n", arr[0], arr[1], arr[2], arr[3], arr[4]);
        SwapInt(&arr[0], &arr[i]);
        HeapifyDown(arr, 0, i);
    }
}

static void HeapifyDown(int *arr, size_t index, size_t size)
{
    size_t left_child_index = ((2 * index) + 1);
    size_t right_child_index = ((2 * index) + 2);
    size_t biggest_index = index;

    if (left_child_index < size && arr[left_child_index] > arr[biggest_index])
    {
        biggest_index = left_child_index;
    }
    if (right_child_index < size && arr[right_child_index] > arr[biggest_index])
    {
        biggest_index = right_child_index;
    }
    if (biggest_index != index)
    {
        SwapInt(&arr[index], &arr[biggest_index]);
        HeapifyDown(arr, biggest_index, size);
    }
}

void SwapInt(int *data1, int *data2)
{
    int tmp = *data1;
    *data1 = *data2;
    *data2 = tmp;
}

void Swap(void *data1, void *data2, int ele_size)
{
    unsigned char *tmp1 = data1, *tmp2 = data2, tmp;
    int i = 0;
    for (i = 0; i != ele_size; ++i)
    {
        tmp = tmp1[i];
        tmp1[i] = tmp2[i];
        tmp2[i] = tmp;
    }
}