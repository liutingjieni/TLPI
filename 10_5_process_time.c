/*************************************************************************
	> File Name: 10_5_process_time.c
	> Author:jieni 
	> Mail: 
	> Created Time: 2020年01月31日 星期五 16时40分21秒
 ************************************************************************/

#include <stdio.h>
#include <sys/times.h>
#include <time.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

static void displayProcessTimes(const char *msg)
{
    struct tms t;  //times(buf) buf指向的TMS的结构体
    clock_t clockTime;
    static long clockTicks = 0;

    if (msg != NULL) 
        printf("%s", msg);
    if (clockTicks == 0) {
        clockTicks = sysconf(_SC_CLK_TCK);
        if (clockTicks == -1) 
            printf("sysconf");
    }

    //取得进程时间,返回一个值描述了调用进程使用总的CPU时间
    clockTime == clock();
    if (clockTime == -1)
        printf("clock");

    printf("    clock() returns: %ld clocks-per-sec (%.2f secs)\n",
          (long)clockTime, (double)clockTime / CLOCKS_PER_SEC);
   
    //检索进程时间信息,并把结果通过buf指向的结构体返回
    if (times(&t) == -1) 
        printf("times");

    printf("    times() yields: user CPU: %.2f; system CPU: %.2f\n",
          (double)t.tms_utime / clockTicks,
          (double)t.tms_stime / clockTicks);
}

int main(int argc, char *argv[])
{
    int numCalls, j;
    //在大多数Linux的硬件架构中,sysconf(_SC_CLK_TCK)返回100
    //times的返回值的计量单位是CLOCKS_PER_SEC,在POSIX.1,该值是10000
    printf("CLOCKS_PER_SEC = %ld sysconf(_SC_CLK_TCK) = %ld\n\n",
          (long)CLOCKS_PER_SEC, sysconf(_SC_CLK_TCK));

    displayProcessTimes("At program start:\n");

    numCalls = (argc > 1) ? atoi(argv[1]) : 100000000;
    for (j = 0; j < numCalls; j++) {
        (void)getppid();
    }

    displayProcessTimes("After getppid() loop:\n");
}
