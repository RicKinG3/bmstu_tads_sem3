// del std who yar oostuplrnie
#include <sys/time.h>
#include <time.h>

#include "../inc/sort_std.h"
#include "../inc/rw_student.h"
#include <math.h>
#include <stdio.h>

unsigned long long milliseconds_now(void)
{
    struct timeval val;

    if (gettimeofday(&val, NULL))
        return (unsigned long long)-1;

    return val.tv_sec * 1000ULL + val.tv_usec / 1000ULL;
}

int del_stdnt(inf_stdnt_t *std, int *num_count_std, int key_int)
{
    for (int i = 0; i < *num_count_std; i++)
    {
        if (std[i].year_admission == key_int)
        {
            if (*num_count_std == 1)
                return ERR_DEL;
            for (int j = i; j < *num_count_std; j++)
            {
                std[j] = std[j + 1];
            }
            *num_count_std -= 1;
            i--;
        }
    }
    return PASS;
}

void sort_key_mergesort(key_tables_t *arr, int l, int r)
{
    if (l < r)
    {
        // m is the point where the array is divided into two subarrays
        int m = l + (r - l) / 2;

        sort_key_mergesort(arr, l, m);
        sort_key_mergesort(arr, m + 1, r);

        // Merge the sorted subarrays
        merge(arr, l, m, r);
    }
}
// Merge two subarrays L and M into arr
void merge(key_tables_t *arr, int p, int q, int r)
{
    // Create L ← A[p..q] and M ← A[q+1..r]
    int n1 = q - p + 1;
    int n2 = r - q;

    key_tables_t L[n1];
    key_tables_t M[n2];

    for (int i = 0; i < n1; i++)
    {
        L[i].index = arr[p + i].index;
        L[i].year_admission = arr[p + i].year_admission;
    }

    for (int j = 0; j < n2; j++)
    {
        M[j].index = arr[q + 1 + j].index;
        M[j].year_admission = arr[q + 1 + j].year_admission;
    }

    // Maintain current index of sub-arrays and main array
    int i, j, k;
    i = 0;
    j = 0;
    k = p;

    // Until we reach either end of either L or M, pick larger among
    // elements L and M and place them in the correct position at A[p..r]
    while (i < n1 && j < n2)
    {
        if (L[i].year_admission <= M[j].year_admission)
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = M[j];
            j++;
        }
        k++;
    }

    // When we run out of elements in either L or M,
    // pick up the remaining elements and put in A[p..r]
    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2)
    {
        arr[k] = M[j];
        j++;
        k++;
    }
}

void sort_std(inf_stdnt_t *arr, int l, int r)
{
    if (l < r)
    {
        // m is the point where the array is divided into two subarrays
        int m = l + (r - l) / 2;

        sort_std(arr, l, m);
        sort_std(arr, m + 1, r);

        // Merge the sorted subarrays
        merge_std(arr, l, m, r);
    }
}
void merge_std(inf_stdnt_t *arr, int p, int q, int r)
{
    // Create L ← A[p..q] and M ← A[q+1..r]
    int n1 = q - p + 1;
    int n2 = r - q;

    inf_stdnt_t L[n1];
    inf_stdnt_t M[n2];

    for (int i = 0; i < n1; i++)
        L[i] = arr[p + i];

    for (int j = 0; j < n2; j++)
        M[j] = arr[q + 1 + j];

    // Maintain current index of sub-arrays and main array
    int i, j, k;
    i = 0;
    j = 0;
    k = p;

    // Until we reach either end of either L or M, pick larger among
    // elements L and M and place them in the correct position at A[p..r]
    while (i < n1 && j < n2)
    {
        if (L[i].year_admission <= M[j].year_admission)
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = M[j];
            j++;
        }
        k++;
    }

    // When we run out of elements in either L or M,
    // pick up the remaining elements and put in A[p..r]
    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2)
    {
        arr[k] = M[j];
        j++;
        k++;
    }
}

void bubule_sort_key(key_tables_t *key, int n)
{
    key_tables_t tmp;
    for (int i = 0; i < n - 1; i++)
        // Last i elements are already in place
        for (int j = 0; j < n - i - 1; j++)
            if (key[j].year_admission > key[j + 1].year_admission)
            {
                tmp = key[j];
                key[j] = key[j + 1];
                key[j + 1] = tmp;
            }
}

void bubule_sort_std(inf_stdnt_t *arr, int n)
{
    inf_stdnt_t tmp;
    for (int i = 0; i < n - 1; i++)
        // Last i elements are already in place
        for (int j = 0; j < n - i - 1; j++)
            if (arr[j].year_admission > arr[j + 1].year_admission)
            {
                tmp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = tmp;
            }
}

unsigned long long measured(inf_stdnt_t *arr_stdnt, key_tables_t *arr_key, int num_count_std)
{

    long long time_key = 0, time_std = 0;
    long long unsigned beg, end;
    key_tables_t tmp_key[num_count_std];
    inf_stdnt_t tmp_std[num_count_std];

    input_key_tables(arr_stdnt, arr_key, num_count_std);

    for (int i = 0; i < num_count_std; i++)
    {
        tmp_key[i] = arr_key[i];
        tmp_std[i] = arr_stdnt[i];
    }

    for (int i = 0; i < 10000; i++)
    {
        beg = milliseconds_now();
        sort_key_mergesort(tmp_key, 0, num_count_std - 1);
        end = milliseconds_now();
        time_key += end - beg;
        for (int i = 0; i < num_count_std; i++)
        {
            tmp_key[i] = arr_key[i];
        }
    }
    for (int i = 0; i < num_count_std; i++)
    {
        tmp_key[i] = arr_key[i];
        tmp_std[i] = arr_stdnt[i];
    }
    for (int i = 0; i < 10000; i++)
    {
        beg = milliseconds_now();
        sort_std(tmp_std, 0, num_count_std - 1);
        end = milliseconds_now();
        time_std += end - beg;
        for (int i = 0; i < num_count_std; i++)
        {
            tmp_std[i] = arr_stdnt[i];
        }
    }
    return (((unsigned long long)(time_std - time_key)) / time_key) * 100ULL;
}

void print_table_measure(inf_stdnt_t *arr_stdnt, key_tables_t *arr_key, int num_count_std)
{
    long long time_key = 0, time_std = 0, time_key_bubl = 0, time_std_bubl = 0;
    long long unsigned beg, end;
    input_key_tables(arr_stdnt, arr_key, num_count_std);
    key_tables_t tmp_key[num_count_std];
    inf_stdnt_t tmp_std[num_count_std];

    for (int i = 0; i < num_count_std; i++)
    {
        tmp_key[i] = arr_key[i];
        tmp_std[i] = arr_stdnt[i];
    }

    for (int i = 0; i < 10000; i++)
    {
        beg = milliseconds_now();
        bubule_sort_key(tmp_key, num_count_std);
        end = milliseconds_now();
        time_key_bubl += end - beg;
        for (int i = 0; i < num_count_std; i++)
        {
            tmp_key[i] = arr_key[i];
        }
    }
    for (int i = 0; i < 10000; i++)
    {
        beg = milliseconds_now();
        bubule_sort_std(tmp_std, num_count_std);
        end = milliseconds_now();
        time_std_bubl += end - beg;
        for (int i = 0; i < num_count_std; i++)
        {
            tmp_std[i] = arr_stdnt[i];
        }
    }

    for (int i = 0; i < num_count_std; i++)
    {
        tmp_key[i] = arr_key[i];
        tmp_std[i] = arr_stdnt[i];
    }

    for (int i = 0; i < 10000; i++)
    {
        beg = milliseconds_now();
        sort_key_mergesort(tmp_key, 0, num_count_std - 1);
        end = milliseconds_now();
        time_key += end - beg;
        for (int i = 0; i < num_count_std; i++)
        {
            tmp_key[i] = arr_key[i];
        }
    }

    for (int i = 0; i < 10000; i++)
    {
        beg = milliseconds_now();
        sort_std(tmp_std, 0, num_count_std - 1);
        end = milliseconds_now();
        time_std += end - beg;
        for (int i = 0; i < num_count_std; i++)
        {
            tmp_std[i] = arr_stdnt[i];
        }
    }

    printf("| %-2d | %-14s | %-15s | %-19s | %-19s |\n", num_count_std, "merge sort key", "buble sort key", "merge sort struct", "buble sort struct");
    printf(":-----------------------------------------------------------------------------------:\n");
    printf("| mc | %-14llu | %-15llu | %-19llu | %-19llu |\n\n", time_key, time_key_bubl, time_std, time_std_bubl);
}
