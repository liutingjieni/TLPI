/*************************************************************************
	> File Name: t_mmap.c
	> Author:jieni 
	> Mail: 
	> Created Time: 2020年09月23日 星期三 22时59分10秒
 ************************************************************************/

#include <stdio.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define MEM_SIZE 10

int main(int argc, char*argv[])
{
    char *addr;
    int fd;

    if (argc < 2 || strcmp(argv[1], "--help") == 0) {
        printf("error ");
        exit(1);
    }
    fd = open(argv[1], O_RDWR);
    if (fd == -1) {
        exit(1);
    }
    addr = mmap(NULL, MEM_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (addr== MAP_FAILED) {
        exit(1);
    }

    if (close(fd) == -1) {
        exit(1);
    }
    printf("current string = %.*s\n", MEM_SIZE, addr);

    if (argc > 2) {
        if (strlen(argv[2]) >= MEM_SIZE) {
            printf("new value too large\n");
        }
        memset(addr, 0, MEM_SIZE);
        strncpy(addr, argv[2], MEM_SIZE - 1);
        if (msync(addr, MEM_SIZE, MS_SYNC) == -1) {
            exit(1);
        }
        printf("copied %s to shared memory\n", argv[2]);
    }
}
