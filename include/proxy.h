/*
 * Shared Memory Chatroom Program - The Proxy
 * By: Max Gardiner
 * CIS 3110 Dave McCaughan
 * Due: February 5, 2012
 * 
 * This half of the program creates shared memory spaces (1 for chat and 1 for integer),
 * prints the proxy pid through signal, then waits for 2 possible signals:
 *      SIGUSR1 : means a new client has joined the shared memory server, print the new client's pid
 *      SIGUSR2 : means a client has just sent a new message, forward a SIGUSR1 to every other client
 *  Note: This can only be terminated with signals
 */

#ifndef _PROXY_H
#define _PROXY_H

/*************************************************
 *               SIGNAL FUNCTIONS                *
 * **********************************************/
/** 
 usr1_processID
 *  Prints the process ID of the signalled process (the proxy)
 args: 
 *  signum - POSIX # referring to calling signal
 **/
void usr1_processID(int signum);

/** 
 usr1_newClient
 *  When this is signalled, the proxy prints the pid of the new client (located in shared int)
 args: 
 *  signum - POSIX # referring to calling signal
 **/
void usr1_newClient(int signum);

/** 
 usr2_newMessage
 *  When this is signalled, the proxy iterates through the list of client's pids and sends the
 * signal to tell each one a new message is available
 args: 
 *  signum - POSIX # referring to calling signal
 **/
void usr2_newMessage(int signum);

/**
 sigcont_exitClient
 * 	When this signal occurs, it means a client has saved its pid in the shared in and exited.
 * 	This handler prints which client exited, and removes it from the client lists
 args:
 * 	signum - POSIX # referring to calling signal
 **/
void sigcont_exitClient(int signum);

#endif
