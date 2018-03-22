#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#define BUFF_SIZE 2048
int main(int argc, char *argv[]){
        int srcFd, dstFd, readSize, writeSize, ret = 0;
        char *src, *dst, buffer[BUFF_SIZE];
        if (argc != 3) {
                fprintf(stderr, "Usage: ./mycopy src dst\n");
                return 1;
        }
        src = argv[1], dst=argv[2];
        srcFd = open(src, O_RDONLY);
        if(srcFd == -1) {
                perror("Cannot open src file");
                return 2;
        }
        dstFd = open(dst, O_WRONLY | O_CREAT, 0644);
        if(dstFd == -1) {
                perror("Cannot open dst file");
                close(srcFd);
                return 3;
        }
        while((readSize = read(srcFd, &buffer, BUFF_SIZE)) > 0) {
                if(write (dstFd, &buffer, readSize)!=readSize) {
                        perror("Error while writing");
                        ret = 4;
                        break;
                }
        }
        if(readSize == -1) {
                perror("Error while reading");
                ret = 5;
        }
        close(srcFd);
        close(dstFd);
        return ret;
}
