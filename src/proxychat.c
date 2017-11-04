//Author: Max Gardiner (Check .h for specific info)

#define SHARED_MEM_SIZE 1024
#define SHARED_INT_SIZE 4

#include "proxychat.h"
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <assert.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char * sharedmemText, * message;
int * sharedmemInt, proxyid;

int main(int argc, char * argv[])
{
    assert(argc == 2);
    
    int shmidInt, shmidStr;
    key_t key = atoi(argv[1]);
    proxyid = key;
    
    message = calloc(SHARED_MEM_SIZE, sizeof(char));
    
    signal(SIGUSR1, usr1_processID);
    kill(getpid(), SIGUSR1);
        
    /* create the shared memory segment */
    if ((shmidInt = shmget(key, SHARED_INT_SIZE, 0666)) < 0)
    {
        printf("Could not locate the shared memory segment\n");
        return 1;
    }
    
    /* attach memory segment to local space */
    if(!(sharedmemInt = shmat(shmidInt, NULL, 0)))
    {
        printf("Could not attach the shared memory to local data space\n");
        return 1;
    }
    
    /* create the shared memory segment */
    if ((shmidStr = shmget(key + SHARED_MEM_SIZE, SHARED_MEM_SIZE, 0666)) < 0)
    {
        printf("Could not locate the shared memory segment\n");
        return 1;
    }
    
    /* attach memory segment to local space */
    if(!(sharedmemText = shmat(shmidStr, NULL, 0)))
    {
        printf("Could not attach the shared memory to local data space\n");
        return 1;
    }
   
   //print pid
   signal(SIGUSR1, usr1_processID);
   *sharedmemInt = getpid();
   kill(key, SIGUSR1);
    
    signal(SIGUSR2, usr2_getMessage);
    signal(SIGINT, sigint_exitMessage);
    
    while(1)
    {
        sleep(1);
        if ((message = fgets(message, SHARED_MEM_SIZE, stdin)) != NULL){
            SendMessage(message, (int)key);
        }
    }
    
    
    return 0;
}

/*************************************************
 *               MESSAGE FUNCTIONS                *
 * **********************************************/

void SendMessage(char * msg, int proxyid){
    assert(strlen(msg) <= SHARED_MEM_SIZE);
    char *localptr = sharedmemText, c;
    int i;
    
    for (i = 0; i < SHARED_MEM_SIZE; i++)
        *localptr++ = '\0';
    
    localptr = sharedmemText;
    
    for (i = 0; i < strlen(msg); i++){
        c = msg[i];
        
        if (c != '\n')
            *localptr++ = c;
    }
    *localptr = '\0';
    
    *sharedmemInt = getpid();
    kill(proxyid, SIGUSR2);
}

/*************************************************
 *               SIGNAL FUNCTIONS                *
 * **********************************************/

void usr1_processID(int signum){
    printf("** ProxyChat ID : %d **\n", getpid());
}

void usr2_getMessage(int signum){
	signal(SIGUSR2, SIG_IGN);
    printf("%d: %s\n", *sharedmemInt, sharedmemText);
    signal(SIGUSR2, usr2_getMessage);
}

void sigint_exitMessage(int signum){
	free(message);
    printf("*** Client %d Exited ***\n", getpid());
    *sharedmemInt = getpid();
    kill(proxyid,SIGCONT);
    kill(getpid(),SIGTERM);
}
