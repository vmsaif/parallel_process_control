#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <signal.h>
#define THREADS 1000

void readFileAgain();
void createOrRemoveThreads();
void sigIntFunc();
void hupFunc();

int inputCount = 0;
int threadCount = 0;

pid_t ppid;
pthread_t p[THREADS];

void *no_work(void *);


int main(void)
{
    ppid = getpid();
    printf("I am parent with pid: %d\n", ppid);
    
    signal(SIGHUP, hupFunc);
    signal(SIGINT, sigIntFunc);
    

    readFileAgain();
    
    // join all threads before finishing
    for(int i = 0; i < threadCount; i++){
        pthread_join(p[i], NULL);
    }
    return EXIT_SUCCESS;
}
void *no_work(void *arg)
{
    (void) arg;
    printf("Thread %lu is starting\n", pthread_self());

    while(1)
    {
        sleep(1);
    }
    return NULL;
}
void sigIntFunc() 
{
    for(int i = threadCount-1; i > -1; i--){
        printf("%lu is being killed\n", p[i]);
        fflush(stdout);
        pthread_cancel(p[i]);
    }
}
void hupFunc()
{
    readFileAgain();
}
void createOrRemoveThreads()
{
    // signal(SIGINT, sigIntFunc);
    if(threadCount < inputCount){
        //add threads
        for(int i = threadCount; i < inputCount; i++){
            pthread_create(&p[i], NULL, no_work, NULL);
            threadCount++;
        }
    } else if (threadCount == inputCount){
        printf("Same same");
    } else {
        //remove
        for(int i = threadCount-1; i > inputCount-1; i--)
        {
            printf("%lu is going to a good place, RIP.\n", p[i]);
            pthread_cancel(p[i]);
            threadCount--;
        }
    }
    
}
void readFileAgain()
{
    printf("Reading Config File...\n");
    FILE *fd;
    if((fd = fopen("config.txt", "r")) != NULL){
        fscanf(fd, "%d", &inputCount);
        fclose(fd);
    } else {
        perror("Program exited with following code");
        exit(1);
    }
    printf("Changing settings to %d\n", inputCount);
    if( inputCount < 1){
        printf("The process count should be at least 1. Exiting\n");
        exit(1);
    } else {
        createOrRemoveThreads();
    }
}



