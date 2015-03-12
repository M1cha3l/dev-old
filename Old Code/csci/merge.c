/* merge.c
 * Michael Hughes - A00270859
 * Lab 9: Merge
 */

/* Program is complete but does not run according to specifications. The
 * don't alternate between each other. Each run until it is finish.
 */

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <errno.h>


#define BADFILE  2
#define BADPARAM 3
#define DEBUG    1

sem_t mutex1;
sem_t mutex2;

typedef struct {
    char *file;
    FILE *mf;
} read_args;

void error(char *msg, int code)
{
    fprintf(stderr, "Error: %s\nAborting.\n", msg);
    exit(code);
}

void *readFile1(void *p)
{

    read_args *param = (read_args *)p;
    FILE *f1;
    char *line;
    size_t len = 0;
    ssize_t read;
    int lineCount = 1;
    f1 = fopen(param->file, "r");
    if(f1 == NULL)
    {
        error("File not found.", BADFILE);
    }


    while((read = getline(&line, &len, f1)) != -1)
    {  
        sem_wait(&mutex1);
        fprintf(param->mf,"%s: %d: %s", param->file, lineCount,line);
        
#if DEBUG        
        printf("%s: %d: %s", param->file, lineCount,line);
#endif 

        sem_post(&mutex2);
        lineCount++;
    } 
    fclose(f1);
    pthread_exit(NULL);
}

void *readFile2(void *p)
{

    read_args *param = (read_args *)p;
    FILE *f1;
    char *line;
    size_t len = 0;
    ssize_t read;
    int lineCount = 1;
    f1 = fopen(param->file, "r");
    if(f1 == NULL)
    {
        error("File not found.", BADFILE);
    }

    while((read = getline(&line, &len, f1)) != -1)
    {  
        sem_wait(&mutex2);
        fprintf(param->mf,"%s: %d: %s", param->file, lineCount,line);
        
#if DEBUG        
        printf("%s: %d: %s", param->file, lineCount,line);
#endif 

        sem_post(&mutex1);
        lineCount++;
    }
    
    fclose(f1);
    pthread_exit(NULL);
}


int main(int argc, char **argv)
{
    FILE *f;
    char *mergedfile;
    pthread_t tid1, tid2;
    read_args *p1;
    read_args *p2;
    p1 = malloc(sizeof(read_args));
    p2 = malloc(sizeof(read_args));
    if(argc != 4)
    {
        error("Invalid parameters. Proper use: ./merge <file1> <file2>" 
            " <mergedfile>", BADPARAM);
    }
    
    p1->file = argv[1];
    p2->file = argv[2];
    
    mergedfile = argv[3];
    f = fopen(mergedfile, "w");
    if(f == NULL)
    {
        error("Can't open file.", BADFILE);
    }
    p1->mf = f;
    p2->mf = f;

    sem_init(&mutex1, 0, 1);
    sem_init(&mutex2, 0, 0);
    if(pthread_create(&tid1, NULL, readFile1, (void*)p1) < 0)
    {
        error("Can't create first thread", EXIT_FAILURE);
    }
    if(pthread_create(&tid2, NULL, readFile2, (void*)p2) < 0)
    {
        error("Can't create second thread", EXIT_FAILURE);
    }
    if(pthread_join(tid1, NULL) < 0)
    {
        error("Can't join first thread", EXIT_FAILURE);
    }
    if(pthread_join(tid2, NULL) < 0)
    {
        error("Can't join second thread", EXIT_FAILURE);
    }
    sem_destroy(&mutex1);
    sem_destroy(&mutex2);
    fclose(f);
    return(EXIT_SUCCESS);

}
