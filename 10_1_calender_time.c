/*************************************************************************
	> File Name: 10_1_calender_time.c
	> Author:jieni 
	> Mail: 
	> Created Time: 2020年01月30日 星期四 19时38分39秒
 ************************************************************************/

#include <stdio.h>
#include <time.h>
#include <locale.h>
#include <sys/time.h>
#define SECONDS_IN_TROPICAL_YEAR (365.24219 * 24 * 60 *60)
#define BUF_SIZE 1000

char *currTime(const char*format)
{
    static char buf[BUF_SIZE];
    time_t t;
    size_t s;
    struct tm *tm;

    t = time(NULL);
    tm = localtime(&t);
    if (tm == NULL) return NULL;
    s = strftime(buf, BUF_SIZE, (format != NULL) ? format : "%c", tm);
    printf("%s\n", buf);
    return (s == 0) ? NULL : buf;
}

int main()
{
    time_t t;
    struct tm *gmp, *locp;
    struct tm gm, loc;
    struct timeval tv;

    t = time(NULL);
    printf("Seconds since the Epoch (1 Jan 1970):%ld", (long)t);
    printf("(about %6.3f years)\n", t / SECONDS_IN_TROPICAL_YEAR);

    if (gettimeofday(&tv, NULL) == -1)
        printf("gettimeofday");
    printf("gettimeofday() returned %ld secs, %ld microsecs\n", (long)tv.tv_sec, (long)tv.tv_usec);

    //函数gmtime()能够把日历时间转换一个对应于UTC的分解时间
    gmp = gmtime(&t);
    if (gmp == NULL)
        printf("gmtime");
    gm = *gmp;
    printf("Broken down by gmtime():\n");
    printf("year = %d mon = %d mday = %d hour = %d min = %d sec = %d",
          gm.tm_year, gm.tm_mon, gm.tm_mday, gm.tm_hour, gm.tm_min, gm.tm_sec);
    printf("wday = %d yday = %d isdst = %d\n", gm.tm_wday, gm.tm_yday, gm.tm_isdst);

    //考虑时区,返回对应于系统本地的一个分解时间
    locp = localtime(&t);
    if (locp == NULL)
        printf("localtime");
    loc = *locp;
    printf("Broken down by localtime():\n");
    printf("year = %d mon = %d mday = %d hour = %d min = %d sec = %d",
          loc.tm_year, loc.tm_mon, loc.tm_mday, loc.tm_hour, loc.tm_min, loc.tm_sec);
    printf("wday = %d yday = %d isdst = %d\n", loc.tm_wday, loc.tm_yday, loc.tm_isdst);

    printf("asctime() formats the gmtime value as: %s", asctime(&gm));
    printf("ctime() formats the time value as: %s", ctime(&t));

    printf("mktime() of gmtime() value: %ld secs\n", (long)mktime(&gm));
    printf("mktime() of localtime() value: %ld secs\n", (long)mktime(&loc));

    char *ct = ctime(&t);
    printf("%s", ct);
    
    //用户格式的本地化字符串 
    currTime(NULL);

}
