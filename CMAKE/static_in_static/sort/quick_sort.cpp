# include "sort.h"

void quick_sort(int *arr, int l, int r)
{
    if (l >= r)
        return;
    int i = l - 1, j = r + 1, x = arr[l + r >> 1];
    do {
        while (arr[++i] < x);
        while (arr[--j] > x);
        if (i < j)
        {
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    } while (i < j);
    quick_sort(arr, l, j);
    quick_sort(arr, j + 1, r);
}