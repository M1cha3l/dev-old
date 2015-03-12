/* 
 * lab4: tsort.c
 * Michael Hughes - A00270859
 */
#include <stdio.h>
#include <pthread.h>

struct sort_args {
    int *arrayPtr;  //pointer to array of int
    int begin;
    int ending;
};

void initialize_params(sort_args *args, int arr[], int b, int e)
{
    args->arrayPtr = arr;
    args->begin = b;
    args->ending = e;
}

void swap(int *a, int *b)
{
  int t=*a; *a=*b; *b=t;
}

void sort(void *ptr)
{
  int piv, l, r;
  pthread_t tid1, tid2;
  int ret;
  sort_args *args = (struct sort_args *)prt;
  int *array_ptr;
  array_ptr = args->arrayPtr; 
  int beg = args->begin;
  int end = args->ending;
  if (end > beg + 1)
  {
    piv = *(array_ptr + beg), l = beg + 1, r = end;
    while (l < r)
    {
      if (*(array_ptr + l) <= piv)
        l++;
      else
        swap(*(array_ptr + l), *(array_ptr + (--r)));
    }
    swap(*(array_ptr + (--l), *(array_ptr + beg)));
    args->begin = beg;
    args->ending = l;
    //initialize_params(&args, beg, i);
    ret = pthread_create(&tid1, NULL, sort,(void *)&args);
    if(ret < 0)
    {
        printf("error: thread\n");
        exit(0);
    }
    //initialize_params(&args, beg, l);
    //sort(arr, beg, l);  // Have this in a new thread
    args->begin = r;
    args->ending = end;
    //initialize_params(&args,array r, end);
    ret = pthread_create(&tid2, NULL, sort,(void *)&args);
    if(ret < 0)
    {
        printf("error: thread\n");
        exit(0);
    }
    //initialize_params(&args, r, end);
    //sort(arr, r, end);  // And this too!
    pthread_join(tid1, NULL);
    pthread_join(tid2,NULL);
  }
  pthread_exit(NULL);
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

int main(int argc, char **argv) 
{

    int data[256] = { 1, 3, 5, 7, 4, 5, 6, 77, 43, 56, 78, 23, 23, 59, 73, 34 };
    int begin = 0;
    int end = 15; // Size this to the array (n-1) 
    pthread_t tid;
    int ret;
    sort_args *a;
    int *p;
    p = data;
    //&a->arr =  { 1, 3, 5, 7, 4, 5, 6, 77, 43, 56, 78, 23, 23, 59, 73, 34 };
    initialize_params(a, data, begin, end);
    ret = pthread_create(&tid, NULL, sort, (void *)&a);
    dprint("Unsorted data", data, end);    
    //sort(data, begin, end);
    pthread_join(tid,NULL);
    dprint("Sorted data", data, end);
  
    return (0);
}      
