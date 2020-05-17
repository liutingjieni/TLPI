/*************************************************************************
	> File Name: 5_1_bad_exclusive_open.c
	> Author:jieni 
	> Mail: 
	> Created Time: 2020年05月16日 星期六 20时02分13秒
 ************************************************************************/

#include <stdio.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argg, char *argv[])
{
    int fd;

    fd = open(argv[1], O_WRONLY);
    if (fd != -1) {
        printf("pid = %d\n", getpid());
    
    }
    else {
        //未能以独占的方式打开文件
        //sleep(40);
        printf("sleep after");
        if(errno != ENOENT) {
            perror("open");
        }  
        else {
            fd = open(argv[1], O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
            if (fd == -1) {
                perror("open");
            }

            printf("pid = %d\n", getpid());
        }
    }
}
