/*************************************************************************
	> File Name: io.c
	> Author:jieni 
	> Mail: 
	> Created Time: 2020年05月16日 星期六 10时27分13秒
 ************************************************************************/

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    clock_t start, finish;
    start = clock();
    double total_time;
    char s[] = "lala";
    char *s1 = s;
    for(int i = 0; i < 10000000; i++) {
        //比较printf和write系统调用的效率
        //printf("%s", s1);
        write(1, s1, 4);
    }

    finish = clock();
    total_time = (double)(finish - start) / CLOCKS_PER_SEC;
    printf("\n%f seconds\n", total_time);
}
