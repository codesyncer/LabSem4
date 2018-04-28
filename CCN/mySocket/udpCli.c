#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#define PORT 8080
int main(int argc, char **argv)
{
	char buffer[1024];
	struct sockaddr_in servAddr;
	int sockfd=socket(PF_INET,SOCK_DGRAM,0);
	servAddr.sin_family=AF_INET;
	servAddr.sin_port=htons(PORT);
	socklen_t servSize=sizeof(servAddr);
	printf("Enter a sentence: \n");
	fgets(buffer,1024,stdin);
	int len=strlen(buffer)+1;
	sendto(sockfd,buffer,len,0,(struct sockaddr *)&servAddr,servSize);

}