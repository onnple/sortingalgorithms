//
// Created by Once on 2019/9/8.
//

#include "sorting.h"
#include <stdio.h>
#include <stdlib.h>

void print_array(int array[], int n){
    for (int i = 0; i < n; ++i) {
        printf("%d ", array[i]);
    }
    printf("\n");
}

static void swap(int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

void selection_sort(int array[], int n){
    int i, j, temp;
    for (i = 0; i < n; ++i) {
        temp = i;
        for (j = i + 1; j < n; ++j) {
            if(array[j] < array[temp])
                temp = j;
        }
        swap(&array[i], &array[temp]);
    }
}

void bubble_sort(int array[], int n){
    int i, j;
    for (i = 0; i < n - 1; ++i) {
        for (j = 0; j < n - 1 - i; ++j) {
            if(array[j] > array[j + 1])
                swap(&array[j], &array[j + 1]);
        }
    }
}

void insertion_sort(int array[], int n){
    int i, j, temp;
    for (i = 1; i < n; ++i) {
        temp = array[i];
        for (j = i; j > 0 && array[j - 1] > temp; --j) {
            array[j] = array[j - 1];
        }
        array[j] = temp;
    }
}

void shell_sort(int array[], int n){
    int i, j, temp, gap;
    for (gap = n / 2; gap > 0; gap /= 2) {
        for (i = gap; i < n; ++i) {
            temp = array[i];
            for (j = i; j >= gap && array[j - gap] > temp; j -= gap) {
                array[j] = array[j - gap];
            }
            array[j] = temp;
        }
    }
}

static void heapify(int array[], int i, int n){
    int left, child, temp = array[i];
    while((left = 2 * i + 1) < n){
        child = left;
        if(left + 1 < n && array[left + 1] > array[left])
            child = left + 1;
        if(array[child] > temp)
            array[i] = array[child];
        else
            break;
        i = child;
    }
    array[i] = temp;
}

void heap_sort(int array[], int n){
    for (int i = n / 2; i >= 0; --i)
        heapify(array, i, n);
    for (int j = n - 1; j > 0; --j) {
        swap(&array[0], &array[j]);
        heapify(array, 0, j);
    }
}

static void merge(int array[], int temp[], int ls, int rs, int re){
    int le =  rs - 1, t = ls, count = re - ls + 1;
    while(ls <= le && rs <= re){
        if(array[ls] <= array[rs]){
            temp[t] = array[ls];
            ls++;
            t++;
        }
        else{
            temp[t] = array[rs];
            rs++;
            t++;
        }
    }
    while(ls <= le){
        temp[t] = array[ls];
        ls++;
        t++;
    }
    while(rs <= re){
        temp[t] = array[rs];
        rs++;
        t++;
    }
    for (int i = count; i > 0; --i, re--) {
        array[re] = temp[re];
    }
}

static void msort(int array[], int temp[], int left, int right){
    if(left < right){
        int center = (left + right) / 2;
        msort(array, temp, left, center);
        msort(array, temp, center + 1, right);
        merge(array, temp, left, center + 1, right);
    }
}

void merge_sort(int array[], int n){
    int *temp = (int*)malloc(sizeof(int) * n);
    if(temp){
        msort(array, temp, 0, n - 1);
        free(temp);
    }
    else{
        perror("alloc memory for temp array error");
    }
}

static int get_pivot(int array[], int left, int right){
    int center = (left + right) / 2;
    if(array[left] > array[center])
        swap(&array[left], &array[center]);
    if(array[left] > array[right])
        swap(&array[left], &array[right]);
    if(array[center] > array[right])
        swap(&array[center], &array[right]);
    swap(&array[right - 1], &array[center]);
    return array[right - 1];
}


static void QSort(int array[], int left, int right){
    if(left + 3 <= right){
        int i, j, pivot;
        pivot = get_pivot(array, left, right);
        i = left, j = right - 1;
        while(1){
            while(array[++i] < pivot){}
            while(array[--j] > pivot){}
            if(i < j)
                swap(&array[i], &array[j]);
            else
                break;
        }
        swap(&array[i], &array[right - 1]);
        QSort(array, left, i - 1);
        QSort(array, i + 1, right);
    }
    else
        insertion_sort(array + left, right - left + 1);
}

void quick_sort(int array[], int n){
    QSort(array, 0, n - 1);
}

void bucket_sort(int array[], int n){
    int max = array[0], i;
    for (i = 1; i < n; ++i) {
        if(array[i] > max)
            max = array[i];
    }
    max++;
    int temp[max];
    for (int k = 0; k < max; ++k) {
        temp[k] = 0;
    }
    for (int j = 0; j < n; ++j) {
        temp[array[j]]++;
    }
    int j = 0;
    for (int l = 0; l < max; ++l) {
        while(temp[l] > 0){
            array[j++] = l;
            temp[l]--;
        }
    }
}