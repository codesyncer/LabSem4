#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
int main(){
        int sock, client, sentconf;
        struct sockaddr_in serverDetails, clientDetails;
        unsigned int len;
        char *msg = "Hello World!";
        if ((sock = socket(PF_INET, SOCK_STREAM, 0)) == -1) {
                perror("Error creating socket");
                return -1;
        }
        serverDetails.sin_family = AF_INET;
        serverDetails.sin_port = htons(10000);
        serverDetails.sin_addr.s_addr = INADDR_ANY;
        bzero(&serverDetails.sin_zero, 8);
        len = sizeof(struct sockaddr*);
        if((bind(sock, (struct sockaddr*)&serverDetails, len)) == -1) {
                perror("Error in binding");
                return -1;
        }
        if((listen(sock, 5)) == -1) {
                perror("Error in listening");
                return -1;
        }
        while(1) {
                if((client = accept(sock, (struct sockaddr*)&clientDetails, &len)) == -1) {
                        perror("Error in accepting");
                        return -1;
                }
                sentconf = send(client, msg, strlen(msg), 0);
                printf("Sending %d bytes ti clientDetails: %d\n", sentconf, inet_ntoa(clientDetails.sin_addr));
                close(client);
        }
        return 0;
}
