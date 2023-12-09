#include "sort.h"

void selet_sort(int *arr, int left, int right)
{
    for (int i = left; i < right; i++)
    {
        int min = i;
        for (int j = i + 1; j <= right; j++)
        {
            if (arr[j] < arr[min])
                min = j;
        }
        if (min != i)
        {
            int temp = arr[i];
            arr[i] = arr[min];
            arr[min] = temp;
        }
    }
}