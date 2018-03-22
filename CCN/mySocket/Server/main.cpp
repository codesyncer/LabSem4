#include <cstdio>
#include <unistd.h>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <signal.h>
#include <stdlib.h>

#define SERVER_PORT 8080
int listenFd, connFd, clientLen;
void my_handler(int s){
        printf("\nBye!\n");
        close(connFd);
        close(listenFd);
        exit(0);
}
int main(int argc, char **argv) {
        signal (SIGINT,my_handler);
        char s[80], f[80];
        FILE *fp;
        sockaddr_in serverAddress = sockaddr_in(), clientAddress = sockaddr_in();
        bzero(&serverAddress, sizeof(serverAddress));
        serverAddress.sin_family = AF_INET;
        serverAddress.sin_port = htons(SERVER_PORT);
        listenFd = socket(AF_INET, SOCK_STREAM, 0);
        if (listenFd == -1) {
                perror("Could not create socket");
                return 0;
        }
        if (bind(listenFd, (sockaddr *) &serverAddress, sizeof(serverAddress)) == -1) {
                perror("Could not bind socket");
                close(listenFd);
                return 0;
        }
        listen(listenFd, 1);
        clientLen = sizeof(clientAddress);
        connFd = accept(listenFd, (sockaddr *) &clientAddress, (socklen_t *) &clientLen);
        if (connFd == -1) {
                perror("Could not accept socket");
                close(listenFd);
                return 0;
        }
        printf("Client Connected!\n");
        read(connFd, f, 80);
        fp = fopen(f, "r");
        printf("Filename: %s\n", f);
        if (fp == nullptr) {
                strcpy(s, "FileNotFound");
                write(connFd, s, sizeof(s));
        } else {
                while (fgets(s, 80, stdin) != nullptr)
                        write(connFd, s, sizeof(s));
                fclose(fp);
        }
        close(connFd);
        close(listenFd);
        return 0;
}
