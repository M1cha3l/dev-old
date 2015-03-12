/* 
 * lab4: tsort.c
 * Michael Hughes - A00270859
 */
#include <stdio.h>
#include <string.h>


typedef struct sort_args {
    int begin;
    int end;
    int arr[16];
} sort_args ;

sort_args srt;

void swap(int *a, int *b)
{
  int t=*a; *a=*b; *b=t;
}


void sort(void *p)
{
  sort_args *params = (sort_args *)p;
//  sort_args p1, p2;
  
  int piv, l, r;
  int beg, end;
  
  beg = params->begin;
  end = params->end;
  //int *ptr = arr;
  if (end > beg + 1)
  {
    piv = params->arr[beg];
    l = beg + 1;
    r = end;
    while (l < r)
    {
      if ((params->arr[l]) <= piv)
        l++;
      else
        swap(&params->arr[l], &params->arr[--r]);
    }
    swap(&params->arr[--l], &params->arr[beg]);
    params->begin = beg;
    params->end = end;
    sort(params);  // Have this in a new thread
    params->begin = r;
    params->end = end;
    sort(params);  // And this too!
  }
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
    
    sort_args *p;
    int data[256] = { 1, 3, 5, 7, 4, 5, 6, 77, 43, 56, 78, 23, 23, 59, 73, 34 };
    int begin = 0;
    int end = 15; // Size this to the array (n-1) 
    memcpy(&p->arr, &data, sizeof(data));
    p->begin = begin;
    p->end = end;
    dprint("Unsorted data", data, end);    
    sort(void *p);
    dprint("Sorted data", data, end);
  
    return (0);
}      
