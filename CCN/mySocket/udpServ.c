#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#define PORT 8080
int main()
{
	struct sockaddr_in serv_addr,cli_addr;
	char buffer[1024];
	socklen_t addr_size;
	int sockfd=socket(AF_INET,SOCK_DGRAM,0);
	if(sockfd<0)
		perror("Error creating socket!");
	memset(&serv_addr, '\0', sizeof(serv_addr));
	serv_addr.sin_family=AF_INET;
	serv_addr.sin_port=htons(PORT);
	bind(sockfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr));
	addr_size=sizeof(cli_addr);
	int n=recvfrom(sockfd,buffer,1024,0,(struct sockaddr*)&cli_addr,&addr_size);
	printf("%s\n",buffer );
}