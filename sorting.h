//
// Created by Once on 2019/9/8.
//

#ifndef DATALGORITHM_SORTING_H
#define DATALGORITHM_SORTING_H

extern void print_array(int array[], int n);
// 选择排序
extern void selection_sort(int array[], int n);
// 冒泡排序
extern void bubble_sort(int array[], int n);
// 插入排序
extern void insertion_sort(int array[], int n);
// 希尔排序
extern void shell_sort(int array[], int n);
// 堆排序
extern void heap_sort(int array[], int n);
// 归并排序
extern void merge_sort(int array[], int n);
// 快速排序
extern void quick_sort(int array[], int n);
// 桶排序
extern void bucket_sort(int array[], int n);

#endif //DATALGORITHM_SORTING_H
