#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "sorting.h"
#include "esorting.h"


static void esort(void){
    int num_ways = 10;

    int run_size = 1000;

    char input_file[] = "G:/temp/sort/input.txt";
    char output_file[] = "G:/temp/sort/output.txt";

    FILE* in = openFile(input_file, "w");

    srand(time(NULL));

    for (int i = 0; i < num_ways * run_size; i++)
        fprintf(in, "%d ", rand());

    fclose(in);

    external_sort(input_file, output_file, num_ways,
                 run_size);
}

int main(void) {
//    int array[] = {36, 4, 6, 3, 13, 0, 3, 5};
//    bucket_sort(array, 8);
//    print_array(array, 8);
    esort();
    return 0;
}

