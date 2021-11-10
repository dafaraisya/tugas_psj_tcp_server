#include <stdio.h>      /* for printf() and fprintf() */
#include <sys/socket.h> /* for socket(), bind(), and connect() */
#include <arpa/inet.h>  /* for sockaddr_in and inet_ntoa() */
#include <stdlib.h>     /* for atoi() and exit() */
#include <string.h>     /* for memset() */
#include <unistd.h>     /* for close() */
#include <pthread.h>        /* for POSIX threads */

#define MAXPENDING 5    /* Maximum outstanding connection requests */
#define RCVBUFSIZE 1000   /* Size of receive buffer */

void DieWithError(char *errorMessage);
void HandleTCPClient(int clntSocket);
int CreateTCPServerSocket(unsigned short port);
int AcceptTCPConnection(int servSock);
void *ThreadMain(void *arg);            /* Main program of a thread */

/* Structure of arguments to pass to client thread */
struct ThreadArgs
{
    int clntSock;                      /* Socket descriptor for client */
};

int main(int argc, char *argv[])
{
    int servSock;                    /* Socket descriptor for server */
    int clntSock;                    /* Socket descriptor for client */
    unsigned short echoServPort;     /* Server port */
    pthread_t threadID;              /* Thread ID from pthread_create() */
    struct ThreadArgs *threadArgs;   /* Pointer to argument structure for thread */
    char jumlahthread;

    if (argc != 2)     /* Test for correct number of arguments */
    {
        fprintf(stderr,"Usage:  %s <SERVER PORT>\n", argv[0]);
        exit(1);
    }

    echoServPort = atoi(argv[1]);  /* First arg:  local port */

    /* Create socket for incoming connections */
    servSock = CreateTCPServerSocket(echoServPort);
    jumlahthread = 0;

    for (;;) /* run forever */
    {
	clntSock = AcceptTCPConnection(servSock);

        /* Create separate memory for client argument */
        if ((threadArgs = (struct ThreadArgs *) malloc(sizeof(struct ThreadArgs))) 
               == NULL)
            DieWithError("malloc() failed");
        threadArgs -> clntSock = clntSock;
	jumlahthread = jumlahthread +1;

        /* Create client thread */
        if (pthread_create(&threadID, NULL, ThreadMain, (void *) threadArgs) != 0)
            DieWithError("pthread_create() failed");
        printf("with thread %ld\n", (long int) threadID);
	printf("jumlah thread %d\n", jumlahthread);
	printf("port %d\n", echoServPort);
    }
    /* NOT REACHED */
}

int AcceptTCPConnection(int servSock)
{
    int clntSock;                    /* Socket descriptor for client */
    struct sockaddr_in echoClntAddr; /* Client address */
    unsigned int clntLen;            /* Length of client address data structure */

    /* Set the size of the in-out parameter */
    clntLen = sizeof(echoClntAddr);
    
    /* Wait for a client to connect */
    if ((clntSock = accept(servSock, (struct sockaddr *) &echoClntAddr, 
           &clntLen)) < 0)
        DieWithError("accept() failed");
    
    /* clntSock is connected to a client! */
    
    printf("Handling client %s\n", inet_ntoa(echoClntAddr.sin_addr));

    return clntSock;
}

int CreateTCPServerSocket(unsigned short port)
{
    int sock;                        /* socket to create */
    struct sockaddr_in echoServAddr; /* Local address */

    /* Create socket for incoming connections */
    if ((sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
        DieWithError("socket() failed");
      
    /* Construct local address structure */
    memset(&echoServAddr, 0, sizeof(echoServAddr));   /* Zero out structure */
    echoServAddr.sin_family = AF_INET;                /* Internet address family */
    echoServAddr.sin_addr.s_addr = htonl(INADDR_ANY); /* Any incoming interface */
    echoServAddr.sin_port = htons(port);              /* Local port */

    /* Bind to the local address */
    if (bind(sock, (struct sockaddr *) &echoServAddr, sizeof(echoServAddr)) < 0)
        DieWithError("bind() failed");

    /* Mark the socket so it will listen for incoming connections */
    if (listen(sock, MAXPENDING) < 0)
        DieWithError("listen() failed");

    return sock;
}

void DieWithError(char *errorMessage)
{
    perror(errorMessage);
    exit(1);
}

void HandleTCPClient(int clntSocket) //    int jmlthread)
{
    char echoBuffer[RCVBUFSIZE];        /* Buffer for echo string */                 
	char simpanid[RCVBUFSIZE];
	char simpanpesan[RCVBUFSIZE];
    char simpannama[RCVBUFSIZE]="nama client: ";
    char nama [RCVBUFSIZE];
	
    int recvMsgSize;  /* Size of received message */
  
  send(clntSocket,simpannama,RCVBUFSIZE,0);

    if ((recvMsgSize = recv(clntSocket, echoBuffer, RCVBUFSIZE, 0)) < 1)
        DieWithError("recv() failed");

    sprintf (nama,"%s", echoBuffer);

     if ((recvMsgSize = recv(clntSocket, echoBuffer, RCVBUFSIZE, 0)) < 1)
        DieWithError("recv() failed");


    
    while (recvMsgSize > 0)      /* zero indicates end of transmission */
    {
 /*echo message back to client */     
 FILE *filesocket= fopen( "filesocket.txt","r");
 FILE *filelog=fopen ("filelog.txt","a");

sprintf (simpanid, "%s", nama);
sprintf (simpanpesan, "\npesan dari %sisi pesan: %s \n", simpanid, echoBuffer);
 fprintf(filelog, "%s",simpanpesan);


int a=4;
while (a<20){
    if (a!=clntSocket){

        send(a, simpanpesan, strlen (simpanpesan),0);
    }

    a=a+1;

}
        fclose(filelog);
        //fclose(filesocket);
        

        /* See if there is more data to receive */
    if ((recvMsgSize =  recv(clntSocket, echoBuffer, RCVBUFSIZE, 0)) < 1)
            DieWithError("recv() failed");
    }

    close(clntSocket);    /* Close client socket */
}

void *ThreadMain(void *threadArgs)
{
    int clntSock;                   /* Socket descriptor for client connection */

    /* Guarantees that thread resources are deallocated upon return */
    pthread_detach(pthread_self()); 

    /* Extract socket file descriptor from argument */
    clntSock = ((struct ThreadArgs *) threadArgs) -> clntSock;
    free(threadArgs);              /* Deallocate memory for argument */
    printf("clntSockID %d\n", clntSock);

    FILE *filesocket = fopen ("filesocketid.txt","a");
    fprintf(filesocket, "client id %d\n", clntSock);
    fclose(filesocket);
    HandleTCPClient(clntSock);
    return (NULL);
}

