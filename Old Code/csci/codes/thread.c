/*
 * Tami Meredith
 * Class Example: PThreads
 */

/* Example has recycled code and may contain more
   #included files than are actually needed */
#include <sys/types.h>
#include <errno.h>
#include <stdio.h>   
#include <string.h>
#include <stdlib.h>

/* Global Variable so its not on the stack and shared
   by the created threads -- simpler than shared memory! */
int sum;

/* mainline of the created "second" thread */
void *thread_main (void *param) {
    int i, upper = atoi(param);
    sum = 0;

    for (i = 1; i <= upper; i++) {
        sum += i;
    }
    pthread_exit(0);
} // end thread_main ()

/* mainline of the "first" thread */
int main (int argc, char **argv) {

    pthread_t  tid;
    pthread_attr_t attr;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <int>\n", argv[0]);
        exit(EXIT_FAILURE);
    }
 
    /* 1. Initialise */
    pthread_attr_init(&attr);
    /* 2. Create and run */
    pthread_create(&tid, &attr, thread_main, argv[1]);
    /* 3. Wait for it to finish */
    pthread_join(tid, NULL);
    /* 4. Display the result (from shared memory) */
    printf("Sum is %d\n", sum);

    exit(EXIT_SUCCESS);

} // end main ()

