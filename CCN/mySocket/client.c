#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>

int main(){
        int sockFd, serverPort= 8000;
        char s[80];
        sockFd = socket(AF_INET, SOCK_DGRAM, 0);
        if(sockFd == -1) {
                perror("Socket");
                exit(EXIT_FAILURE);
        }
        struct sockaddr_in serverAddress;
        bzero(&serverAddress, sizeof(serverAddress));
        serverAddress.sin_family = AF_INET;
        serverAddress.sin_port = htons(serverPort);
        inet_pton(AF_INET, "localhost", &serverAddress.sin_addr);
        if (connect(sockFd, (struct sockaddr*)&serverAddress, (socklen_t)sizeof(serverAddress)) == -1) {
                perror("Connect");
                exit(EXIT_FAILURE);
        }
        char foo[] = "Hekko!\n";
        write(sockFd, foo, sizeof(foo));
        while(read(sockFd, s, sizeof(s)) != 0)
                printf("Got: %s", s);
        close(sockFd);
        return 0;
}
