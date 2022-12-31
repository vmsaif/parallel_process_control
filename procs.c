//-----------------------------------------
// NAME: Saif Mahmud
// REMARKS: USE of SIGHUP with fork to change fileinput while running 
//-----------------------------------------
#include <sys/types.h> // for pid_t
#include <stdio.h>     // for printf
#include <unistd.h>    // for sleep, fork
#include <sys/wait.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>

#define MAX_FORK 1000

int processCount = 0;
int inputCount = 0;

pid_t ppid;
pid_t pids[MAX_FORK];

void exitChild();
void sigIntFunc();
void readFileAgain();
void createForks();
void proccesReduce();
void hupFunc();

int main(void)
{
    ppid = getpid();
    printf("I am parent with pid: %d\n", ppid);
    
    signal(SIGUSR1, proccesReduce);
    signal(SIGHUP, hupFunc);
    signal(SIGINT, sigIntFunc);
    readFileAgain();

    while(1);
    return EXIT_SUCCESS;
} // main

void sigIntFunc() 
{
    if(getpid() != ppid) {
        printf("%d is being killed\n", getpid());
        fflush(stdout);
        kill(ppid, SIGUSR1);
        exit(EXIT_SUCCESS); 
    } else {
        // cleanly exit from main
    }
}

void createForks(){

    if(processCount > inputCount) {
        //remove forks
        for(int i = processCount-1; i > inputCount-1; i--){
            kill(pids[i], SIGINT);
            wait(&pids[i]);
        }

        
        
    } else if(processCount < inputCount){
        //create new forks
        for (int i = processCount; i < inputCount; i++)
        {
            processCount++;
            pids[i] = fork();
            
            if (pids[i] == -1){
                perror("Fork Failed");
                exit(1);
            } else if (pids[i] == 0){ 
                // child
                printf("%d is starting\n", getpid());
                while (1)
                {
                    sleep(1);
                }
                
            } else {
                //parent
                
                sleep(2);
            }
        } // for

    } else {
        printf("same same\n");
    }
    sleep(1);
    
    
}
void hupFunc(){
    readFileAgain();
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
        createForks();
    }
}

void proccesReduce(){
    int index = processCount;
    if(processCount > inputCount){
        index = inputCount;
    }
    pids[index-1] = 0;
    processCount--;
}


