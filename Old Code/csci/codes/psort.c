/* 
 * lab4: tsort.c
 * Michael Hughes - A00270859
 */
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

typedef struct sort_args {
    int *ptr;
    int  begin;
    int  end;
} sort_args;

void swap(int *a, int *b)
{
    int t=*a; *a=*b; *b=t;
}

void * sort(void *s_args)
{
    int arr[], int beg, int end;
    int piv, l, r;
    sort_args *params = (sort_args *)s_args;
    if (end > beg + 1)
    {
        piv = arr[beg], l = beg + 1, r = end;
        while (l < r)
        {
            if (arr[l] <= piv)
            {
                l++;
            }
            else
            {
                swap(&arr[l], &arr[--r]);
            }
        }
        swap(&arr[--l], &arr[beg]);
        sort(arr, beg, l);  // Have this in a new thread
        sort(arr, r, end);  // And this too!
    }
}

void dprint(char *m, int *d, int n) 
{
    int i;
    printf("%s: %d", m, d[0]);
    for (i = 1; i < n; i++) 
    {
        printf(", %d", d[i]);
    } 
    printf("\n");
}

int main(int argc, char **argv) 
{

    int data[256] = { 1, 3, 5, 7, 4, 5, 6, 77, 43, 56, 78, 23, 23, 59, 73, 34 };
    int begin = 0;
    int end = 15; // Size this to the array (n-1) 

    dprint("Unsorted data", data, end);    
    sort(data, begin, end);
    dprint("Sorted data", data, end);
  
    return (0);
}      
