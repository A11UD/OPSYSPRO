#include <stdio.h>
#include <strings.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h> 

#define MYPORT 6901 /* this should be the same as THEIRPORT in fork_socket.c */
#define MAXBUFLEN 100

int main (void)
{
	/* The child's new program.
	This program will replace the parent's program */

	struct sockaddr_in my_addr, their_addr;
	int addr_len, numbytes;
	int UDPSocket;
	char buffer[MAXBUFLEN];

	sleep(1);
	printf("Process[%d]: Child of process[%d] in execution\n",getpid(), getppid());

	/* Initialize own address information */
	my_addr.sin_family = AF_INET;
	my_addr.sin_addr.s_addr = INADDR_ANY;
	my_addr.sin_port = htons(MYPORT);
	bzero(&(my_addr.sin_zero),8);

	/* Create socket */
	if ((UDPSocket = socket(AF_INET, SOCK_DGRAM, 0)) == -1){
		perror("socket");
		return 0;//exit(1);
	}
	if (bind(UDPSocket, (struct sockaddr*)&my_addr, sizeof(struct sockaddr)) == -1){
		perror("bind");
		return 0; //exit(1);
	}

	addr_len = sizeof(struct sockaddr);

	/* Receive message from socket */
	if ((numbytes=recvfrom(UDPSocket, buffer, MAXBUFLEN, 0, (struct sockaddr *)&their_addr, &addr_len)) == -1){
		perror ("revfrom");
		return 0; // exit(1);
	}

	/* Extract the parent's port number (it's at the start of the message) */
	sscanf(buffer, "%d:", &parent_port);  // Extract the parent's port number before the colon

	printf("Process[%d]: Received packet from %s\n", getpid(), inet_ntoa(their_addr.sin_addr));
	printf("Process[%d]: Packet is %d bytes long\n", getpid(), numbytes);
	buffer[numbytes] = '\0';
	printf("Process[%d]: Packet contains \"%s\"\n", getpid(), buffer); 
	
    /* Print parent's port number */
    printf("Process[%d]: Parent's port number is %d\n", getpid(), parent_port);


	sleep(2);
	printf("Process[%d]: Child terminating\n", getpid());
	
	return 0; //exit(0); 
}

