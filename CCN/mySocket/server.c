#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(){
        int sockFd, clientFd, clientLen, serverPort = 8000, opt=1;
        struct sockaddr_in address, clientAddress;
        char s[80];
        sockFd = socket(AF_INET, SOCK_STREAM, 0);
        if (sockFd == -1) {
                perror("Socket");
                exit(EXIT_FAILURE);
        }
        if (setsockopt(sockFd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
                perror("Setsockopt");
                exit(EXIT_FAILURE);
        }
        bzero(&address, sizeof(address));
        address.sin_family = AF_INET;
        address.sin_addr.s_addr = INADDR_ANY;
        address.sin_port = htons(serverPort);
        if (bind(sockFd, (struct sockaddr *)&address, sizeof(address)) == -1) {
                perror("Bind");
                exit(EXIT_FAILURE);
        }
        if(listen(sockFd, 1) == -1) {
                perror("Listen");
                exit(EXIT_FAILURE);
        }
        clientLen = sizeof(clientAddress);
        clientFd = accept(sockFd, (struct sockaddr *)&clientAddress, (socklen_t *)&clientLen);
        if(clientFd == -1) {
                perror("Accept");
                exit(EXIT_FAILURE);
        }
        char dst[80];
        inet_ntop(AF_INET, &clientAddress.sin_addr, dst, (socklen_t)clientLen);
        printf("Connection from %s\n", dst);
        char foo[] = "Hekko!\n";
        write(clientFd, foo, sizeof(foo));
        while(read(clientFd, s, sizeof(s)) != 0)
                printf("Got: %s", s);
        close(clientFd);
        close(sockFd);
        return 0;
}
