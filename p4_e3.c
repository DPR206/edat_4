#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "types.h"
#include "file_utils.h"
#include "bstree.h"
#include "search_queue.h"

void get_median(SearchQueue *sq, float *median);

void data_free(SearchQueue *sq);

int main(int argc, char const *argv[]){
    FILE *fin = NULL, *fout = NULL;
    int num, i;
    float mean = 0, median = 0;
    float tmp, *grade = NULL, *aux = NULL;
    SearchQueue *sq = NULL;

    if(argc != 2){
        printf("Input must be <%s> <Input file>", argv[0]);
        exit(EXIT_FAILURE);
    }

    fin = fopen(argv[1], "r");
    if(!fin){
        exit(EXIT_FAILURE);
    }
    fout = stdout;

    fscanf(fin, "%d", &num);
    if (num < 1){
        fclose(fin);
        exit(EXIT_FAILURE);
    }

    sq =search_queue_new(float_print, float_cmp);
    for(i=1; i<=num; i++){
        if (fscanf(fin, "%f", &tmp)==1){
            grade = float_init(tmp);
            search_queue_push(sq, grade);

            mean+=tmp;
        }
    }
    mean = (float)mean/num;
    get_median(sq, &median);

    fprintf(fout, "Ordered grades: ");
    search_queue_print(fout, sq);
    fprintf(fout, "\n");

    fprintf(fout, "Mean: ");
    fprintf(fout, "%.2f", mean);
    fprintf(fout, "\n");

    fprintf(fout, "Median: ");
    fprintf(fout, "%.2f", median);
    fprintf(fout, "\n");

    fprintf(fout, "Lowest grades: ");
    for (i=0; i<3; i++){
        aux = search_queue_pop(sq);
        fprintf(fout, "%.2f ", *aux);
        float_free(aux);
    }
    fprintf(fout, "\n");

    fprintf(fout, "Highest grades: ");
    for (i=0; i<3; i++){
        aux = search_queue_popBack(sq);
        fprintf(fout, "%.2f ", *aux);
        float_free(aux);
    }
    fprintf(fout, "\n");

    fclose(fin);
    data_free(sq);
    search_queue_free(sq);
    
    exit(EXIT_SUCCESS);
}

void data_free(SearchQueue *sq){
    float *aux = NULL;
    int i;
    size_t size;

    if(!sq) return;

    size = search_queue_size(sq);
    for(i=0; i<size; i++){
        aux = search_queue_pop(sq);
        float_free(aux);
    }
}

void get_median(SearchQueue *sq, float *median){
    int num, i;
    float *tmp = NULL;
    SearchQueue *aux = NULL;

    if(!sq) return;

    aux = search_queue_new(float_print, float_cmp);
    if(!aux) return;

    num = search_queue_size(sq);

    for(i=0; i<num; i++){
        tmp = search_queue_pop(sq);

        if(num%2 == 0){
            if(i == num/2 - 1){
                *median = *tmp;
            } else if (i == num/2){
                *median += *tmp;
            }
        } else {
            if(i == num /2){
                *median = *tmp;
            }
        }
        search_queue_push(aux, tmp);
    }
    if(num%2 == 0){
        *median /= 2;
    }

    for(i=0; i<num; i++){
        tmp = search_queue_pop(aux);
        search_queue_push(sq, tmp);
    }

    search_queue_free(aux);
}