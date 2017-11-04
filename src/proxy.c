//Author: Max Gardiner (Check .h for specific info)

#define SHARED_MEM_SIZE     1024
#define SHARED_INT_SIZE     4

#ifndef MAX_CLIENTS
#define MAX_CLIENTS     10
#endif

#include "proxy.h"
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>

int clientList[MAX_CLIENTS], nClients = 0;
int * sharedmemInt;
char * sharedmemText; 

int main(int argc, char * argv[])
{
    int shmidStr, shmidInt;
    key_t key = getpid();

    /* create the shared memory segment */
    if((shmidInt = shmget(key, SHARED_INT_SIZE, IPC_CREAT | 0666)) < 0)
    {
        printf("Error creating the shared memory segment1\n");
        return 1;
    }
    
    /* attach the segment to our data space */
    if(!(sharedmemInt = shmat(shmidInt, NULL, 0)))
    {
        printf("Error attaching the segment to local data space\n");
        return 1;
    }
    
    /* create the shared memory segment */
    if((shmidStr = shmget(key + SHARED_MEM_SIZE, SHARED_MEM_SIZE, IPC_CREAT | 0666)) < 0)
    {
        printf("Error creating the shared memory segment1\n");
        return 1;
    }
    
    /* attach the segment to our data space */
    if(!(sharedmemText = shmat(shmidStr, NULL, 0)))
    {
        printf("Error attaching the segment to local data space\n");
        return 1;
    }
    
    
    signal(SIGUSR1, usr1_processID);
    kill(getpid(), SIGUSR1);
        
    signal(SIGUSR1, usr1_newClient);
    signal(SIGUSR2, usr2_newMessage);
    signal(SIGCONT, sigcont_exitClient);    
    
    while (1)
    {
        fflush(stdout);
    }
    
    printf("\n");
    return 0;
}   

/*************************************************
 *               SIGNAL FUNCTIONS                *
 * **********************************************/

void usr1_processID(int signum)
{
    printf("*** PROXY ID : %d ***\n", getpid());
}

void usr1_newClient(int signum)
{
    clientList[nClients] = *sharedmemInt;
    printf("NEW CLIENT %d!\n", clientList[nClients]);
    nClients++;
}

void usr2_newMessage(int signum)
{
    int i;
    for (i = 0; i < nClients; i++){   //Send message to all other clients
        if (clientList[i] != *sharedmemInt)
            kill(clientList[i], SIGUSR2);
    }
}

void sigcont_exitClient(int signum)
{
	printf("* CLIENT EXITTED: %d \n", *sharedmemInt);
}
