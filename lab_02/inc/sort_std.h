#ifndef __SORT_STD_H__
#define __SORT_STD_H__

#include "../inc/struct_inf_stdnt.h"
#include"../inc/error.h"

int del_stdnt(inf_stdnt_t *std, int *num_count_std, int key_int);
void merge(key_tables_t *arr, int p, int q, int r);
void sort_key_mergesort(key_tables_t *arr, int l, int r);
unsigned long long  measured(inf_stdnt_t *arr_stdnt, key_tables_t *arr_key, int num_count_std);
void bubule_sort_key(key_tables_t *key, int n);
void bubule_sort_std(inf_stdnt_t *arr, int n);

void merge_std(inf_stdnt_t *arr, int p, int q, int r);
unsigned long long milliseconds_now(void);
void print_table_measure(inf_stdnt_t * arr_stdnt,key_tables_t * arr_key,int  num_count_std);
void sort_std(inf_stdnt_t *arr, int l, int r);

#endif