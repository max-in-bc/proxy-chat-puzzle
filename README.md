******************************************************
The Proxy Chat - IRC Style Shared Memory Chat Client
******************************************************
##TO COMPILE##
	TYPE 'make' from the Makefile dir, THEN 'bin/proxy' and 'bin/proxychat' WILL BE CREATED

##TO START PROXY##
	TYPE 'bin/proxy' to start the proxy, any chat clients should take note of the printed PID

##TO START CHAT CLIENTS##
	TYPE 'bin/proxychat ####" WHERE '####' is replaced to the pid of the proxy --This must be run in a different 
	terminal than proxy or any other chat client

NOTE: IN ORDER TO CHANGE THE DEFAULT NUMBER OF MAXIMUM PROXIES, CHANGE THE PREPROCESSOR #DEFINE IN "proxy.c", DEFAULT IS 20

SRC DIRECTORY:
    proxy.c - is the file that starts the shared memory segments, and keeps track of all the chat clients
    proxychat.c - is the file that tells the proxy it is a new client, or tells the proxy it has a new message to send

INCLUDE DIRECTORY:
    proxy.h - proxy header file
    proxychat.h - proxy chat header file
    
BIN DIRECTORY:
    proxy - the executable proxy
    proxychat - the executable proxychat
    
MAIN DIRECTORY:
    MAKEFILE - type "make", "make all", or "make lockdown" to build proxy and proxychat
    README.txt - quick directory info on all files, and how to run the proxy chat
    A1_docs.pdf - info of the problem, and brief description of my solution, and any special design notes/algorithms
