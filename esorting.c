//
// Created by Once on 2019/9/9.
// external sorting

#include "esorting.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int left(int i){
    return 2 * i + 1;
}

static int right(int i){
    return 2 * i + 2;
}

static void heapify(Heap *heap, int i){
    int l = left(i);
    int r = right(i);
    int smallest = i;
    if (l < heap->size && heap->array[l].data < heap->array[i].data)
        smallest = l;
    if (r < heap->size && heap->array[r].data < heap->array[smallest].data)
        smallest = r;
    if (smallest != i)
    {
        swap(&heap->array[i], &heap->array[smallest]);
        heapify(heap, smallest);
    }
}

// 优先队列主要使用到的操作
Heap *heap_new(HeapNode *datas, int size){
    if(datas == NULL || size <= 0)
        return NULL;
    Heap *heap = (Heap*)malloc(sizeof(Heap));
    if(!heap){
        perror("alloc for heap error");
        return NULL;
    }
    heap->size = size;
    heap->array = datas;
    int i = (size - 1) / 2;
    while (i >= 0){
        heapify(heap, i);
        i--;
    }
    return heap;
}

HeapNode *heap_min(Heap *heap){
    if(heap == NULL || heap->size == 0)
        return NULL;
    return &heap->array[0];
}

void heap_replace_min(Heap *heap){
    heapify(heap, 0);
}

// 交换数据记录
void swap(HeapNode *a, HeapNode *b){
    int data = a->data;
    int i = a->i;
    a->data = b->data;
    a->i = b->i;
    b->data = data;
    b->i = i;
}

static void merge(int arr[], int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;
    int L[n1], R[n2];
    for(i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for(j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];
    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
            arr[k++] = L[i++];
        else
            arr[k++] = R[j++];
    }

    while (i < n1)
        arr[k++] = L[i++];

    while(j < n2)
        arr[k++] = R[j++];
}

// 归并排序
void msort(int array[], int left, int right){
    if (left < right)
    {
        int m = left + (right - left) / 2;

        msort(array, left, m);
        msort(array, m + 1, right);

        merge(array, left, m, right);
    }
}

FILE* openFile(char* fileName, char* mode){
    FILE* fp = fopen(fileName, mode);
    if (fp == NULL)
    {
        perror("open file error");
        exit(EXIT_FAILURE);
    }
    return fp;
}

void mergeFiles(char *output_file, int n, int k){
    FILE* in[k];
    for (int i = 0; i < k; i++)
    {
        char fileName[32];
        sprintf(fileName, "G:/temp/sort/%d", i);
        in[i] = openFile(fileName, "r");
    }

    FILE *out = openFile(output_file, "w");

    HeapNode* harr = (HeapNode*)malloc(sizeof(HeapNode) * k);
    if(!harr){
        perror("alloc for k nodes error");
        exit(EXIT_FAILURE);
    }
    int i;
    for (i = 0; i < k; i++)
    {
        if (fscanf(in[i], "%d ", &harr[i].data) != 1)
            break;

        harr[i].i = i;
    }
    Heap *hp = heap_new(harr, i);

    int count = 0;

    while (count != i)
    {
        HeapNode *root = heap_min(hp);
        fprintf(out, "%d ", root->data);

        if (fscanf(in[root->i], "%d ", &root->data) != 1 )
        {
            root->data = INT_MAX;
            count++;
        }

        heap_replace_min(hp);
    }

    for (i = 0; i < k; i++)
        fclose(in[i]);

    fclose(out);
}

static void createInitialRuns(char *input_file, int run_size, int num_ways){
    FILE *in = openFile(input_file, "r");
    FILE* out[num_ways];
    for (int i = 0; i < num_ways; i++)
    {
        char fileName[32];
        sprintf(fileName, "G:/temp/sort/%d", i);
        out[i] = openFile(fileName, "w");
    }

    int* arr = (int*)malloc(run_size * sizeof(int));

    int more_input = 1;
    int next_output_file = 0;

    int i;
    while (more_input)
    {
        for (i = 0; i < run_size; i++)
        {
            if (fscanf(in, "%d ", &arr[i]) != 1)
            {
                more_input = 0;
                break;
            }
        }

        msort(arr, 0, i - 1);

        for (int j = 0; j < i; j++)
            fprintf(out[next_output_file], "%d ", arr[j]);

        next_output_file++;
    }

    for (i = 0; i < num_ways; i++)
        fclose(out[i]);

    fclose(in);
}

// 外部排序
void external_sort(char *input, char *output, int runs, int run_size){
    createInitialRuns(input, run_size, runs);
    mergeFiles(output, run_size, runs);
}