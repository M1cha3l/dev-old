/* 
 * lab4: sort.c
 * Tami Meredith
 */
#include <stdio.h>
#include <pthread.h>

void swap(int *a, int *b)
{
  int t=*a; *a=*b; *b=t;
}

void *sort(int *arr[], int beg, int end)
{
  int piv, l, r;

  if (end > beg + 1)
  {
    piv = arr[beg], l = beg + 1, r = end;
    while (l < r)
    {
      if (arr[l] <= piv)
        l++;
      else
        swap(&arr[l], &arr[--r]);
    }
    swap(&arr[--l], &arr[beg]);
    sort(arr, beg, l);  // Have this in a new thread
    sort(arr, r, end);  // And this too!
  }
  pthread_exit(0);
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
    
    pthread_t tid;
    pthread_attr_t attr;
    int data[256] = { 1, 3, 5, 7, 4, 5, 6, 77, 43, 56, 78, 23, 23, 59, 73, 34 };
    int begin = 0;
    int end = 15; // Size this to the array (n-1) 

    dprint("Unsorted data", data, end); 
    pthread_attr_init(&attr);
    pthread_create(&tid, &attr, sort, NULL);   
    sort(data, begin, end);
    dprint("Sorted data", data, end);
  
    return (0);
}      
