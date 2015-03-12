/* sort.c 
 * Lab 8: Parallelisation
 * Michael Hughes - A00270859
 */

/* 
 * Program is complete and runs according to specifications.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <errno.h>

#define BADFILE  2
#define BADPARAM 3
#define DEBUG    0


//struct for parameters to pass to sort
typedef struct {
    int beg;
    int end;
    int arr[];
} sort_args;



void error(char *msg, int code)
{
    fprintf(stderr, "Error: %s\nAborting.\n", msg);
    exit(code);
}

void swap(int *a, int *b)
{
    int t=*a; *a=*b; *b=t;
}

void dprint(char *m, int *d, int n) 
{
    int i;
    printf("%s: %d", m, d[0]);
    for (i = 1; i < n; i++) {
        printf(", %d", d[i]);
    } 
    printf("\n");
}

void *sort(void *p)
{
    sort_args *param = (sort_args *)p;
    int piv, l, r;
    int beg, end;
    pthread_t tid1, tid2;
    beg = param->beg;
    end = param->end;

#if DEBUG
    dprint("Unsorted data", param->arr, param->end);
#endif

    if (end > beg + 1)
    {
        piv = param->arr[beg], l = beg + 1, r = end;
        while (l < r)
        {
            if (param->arr[l] <= piv)
                l++;
            else
                swap(&param->arr[l], &param->arr[--r]);
        }
        swap(&param->arr[--l], &param->arr[beg]);

#if DEBUG
    printf("Trace 1\n");
#endif

        //update param for first thread; create and join thread
        param->beg = beg;
        param->end = l;   
        if(pthread_create(&tid1, NULL, sort, (void*)param) < 0)
        {
            error("pthread_create1",EXIT_FAILURE);
        }
        if(pthread_join(tid1,NULL) < 0)
        {
            error("pthread_join1",EXIT_FAILURE);
        }

#if DEBUG
    printf("Trace 2\n");
#endif

        //update param for second thread
        param->beg = r;
        param->end = end;
        if(pthread_create(&tid2, NULL,sort,(void*)param) < 0)
        {
            error("pthread_create2",EXIT_FAILURE);
        }
        if(pthread_join(tid2,NULL) < 0)
        {
            error("pthread_join2",EXIT_FAILURE);
        }
    }

#if DEBUG
    printf("Trace 3\n");
#endif

    pthread_exit(NULL);
}


int main(int argc, char **argv) 
{
    int c;
    int lineCount = 0;
    int sortCount = 0;
    FILE *f;
    char *filename;
    pthread_t tid;
    sort_args *params;

    if(argc != 2)
    {
        error("Invalid parameters. Proper use: ./sort \"filename\"", BADPARAM);
    }
    filename = argv[1];
    f = fopen(filename, "r");
    if(f == NULL)
    {
        error("File not found.", BADFILE);
    }
    else
    {

        if(lineCount == 0)
        { 
            fscanf(f, "%d", &sortCount);
            lineCount++;
        }
        int n;
        params = malloc(sizeof(sort_args) + sortCount * sizeof(int));
        for(n = 0; n < sortCount; n++)
        {
            fscanf(f, "%d",&c);
            params->arr[n] = c;
        }    
    }
    fclose(f);

    int begin = 0;
    int end = sortCount - 1; // Size this to the array (n-1) 

    //update params for thread    
    params->beg = begin;
    params->end = end; 
    dprint("Unsorted data", params->arr, params->end);

    if(pthread_create(&tid, NULL, sort, (void*)params) < 0)
    {
        printf("pthread_create\n");
        exit(EXIT_FAILURE);
    }
    if(pthread_join(tid,NULL) < 0)
    {
        printf("pthread_join\n");
        exit(EXIT_FAILURE);
    } 

    dprint("Sorted data", params->arr, params->end);
  
    return (0);
}      
