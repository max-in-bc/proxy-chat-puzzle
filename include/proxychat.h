
/*
 * Shared Memory Chatroom Program - The Client
 * By: Max Gardiner
 * CIS 3110 Dave McCaughan
 * Due: February 5, 2012
 * 
 * This half of the program takes the pid of the proxy as a command line argument and uses that as the key to
 * the location of the shared memory segments, to which it attaches local variables. Then it waits constantly 
 * for signals and input from the user (if input is found, SIGUSR is sent to the proxy)
 *      SIGUSR1 : means this client has inputted a message, print "YOU: + 'Your Message'"
 *      SIGUSR2 : means the proxy is signalling a new message, it prints "(shared int):(shared text)"
 *      SIGINT  : means the user may want to quit, if they do it sends a SIGTERM to this client
 *  Note: This can only be terminated with signals
 */
#ifndef _PROXYCHAT_H
#define _PROXYCHAT_H

/*************************************************
 *               HELPER FUNCTIONS                *
 * **********************************************/

/** 
 SendMessage
 *  Prints the message from stdin to shared memory location,
 *  saves process ID in shared memory integer location, then
 *  send signal to proxy that a new message has been sent
 args: 
 *  msg - Message from user to be sent via proxy
 *  proxyid - the pid of the proxy
**/
void SendMessage(char * msg, int proxyid);

  
/*************************************************
 *               SIGNAL FUNCTIONS                *
 * **********************************************/
/** 
 usr1_processID
 *  Prints the process ID of the signalled process
 args: 
 *  signum - POSIX # referring to calling signal
**/
void usr1_processID(int signum);

/** 
 usr1_getMessage
 *  Signal sent by proxy when new message is available to chat clients.
 *  Simply prints the chat message with pid of calling process, like "(PID):(message)"
 args: 
 *  signum - POSIX # referring to calling signal
**/
void usr2_getMessage(int signum);

/** 
 sigint_exitMessage
 *  When CTRL+c is pressed by user, this signal handler is called instead of SIGINT.
 *  It asks user if it is ready to quit, if they are then SIGTERM is sent
 args: 
 *  signum - POSIX # referring to calling signal
**/
void sigint_exitMessage(int signum);

#endif