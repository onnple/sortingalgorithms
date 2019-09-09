//
// Created by Administrator on 2019/9/9.
// external sorting

#ifndef DATALGORITHM_ESORTING_H
#define DATALGORITHM_ESORTING_H

#include <stdio.h>

typedef struct heapnode{
    int data;
    int i; // 第i个顺串中的数据记录
} HeapNode;

// 二叉堆（最小堆）
typedef struct heap{
    HeapNode *array;
    int size;
} Heap;

// 优先队列主要使用到的操作
extern Heap *heap_new(HeapNode *datas, int size);
extern HeapNode *heap_min(Heap *heap);
extern void heap_replace_min(Heap *heap);

// 交换数据记录
extern void swap(HeapNode *a, HeapNode *b);

// 归并排序
extern void msort(int array[], int left, int right);

// 外部排序
extern void external_sort(char *input, char *output, int runs, int run_size);

extern FILE* openFile(char* fileName, char* mode);

#endif //DATALGORITHM_ESORTING_H
