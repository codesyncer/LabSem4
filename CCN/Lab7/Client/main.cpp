#include <cstdio>
#include <unistd.h>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define SERVER_PORT 8080

int main(int argc, char **argv) {
    // char hostname[50];
    // printf("%d",gethostname(hostname, sizeof(hostname)));
    printf("%s\n", hostname);
    char fileName[80], recLine[80];
    sockaddr_in serverAddress = sockaddr_in();
    int socketFd = socket(AF_INET, SOCK_DGRAM, 0);
    if (socketFd == -1) {
        perror("Could not open socket");
        return 0;
    }
    bzero(&serverAddress, sizeof(serverAddress));
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(SERVER_PORT);
    inet_pton(AF_INET, "localhost", &serverAddress.sin_addr);
    int connectResult = connect(socketFd, (sockaddr *) &serverAddress, sizeof(serverAddress));
    if (connectResult == -1) {
        perror("Could not connect to server");
        close(socketFd);
        return 0;
    }
    printf("Enter filename: ");
    scanf("%s", fileName);
    write(socketFd, fileName, sizeof(fileName));
    printf("Data from server\n");
    while (read(socketFd, recLine, sizeof(recLine)) != 0) {
        fputs(recLine, stdout);
    }
    close(socketFd);
    printf("\n");
    return 0;
}
