/*************************************************************************
	> File Name: 10_4_show_time.c
	> Author:jieni 
	> Mail: 
	> Created Time: 2020年01月31日 星期五 00时49分50秒
 ************************************************************************/

#include <stdio.h>
#include <time.h>
#include <locale.h>
#define BUF_SIZE 200

int main()
{
    time_t t;
    struct tm *loc;
    char buf[BUF_SIZE];

    if (setlocale(LC_ALL, "") == NULL) 
        printf("setlocale");
    t = time(NULL);
    printf("ctime() of time() value is: %s", ctime(&t));
    
    loc = localtime(&t);
    if (loc == NULL)
        printf("localtime");
    printf("asctime() of localtime() value is: %s", asctime(loc));

    if (strftime(buf, BUF_SIZE, " %A, %d %B %Y, %H:%M:%S %Z", loc) == 0)
        printf("strftime");
    printf("strftime() of local time is: %s \n", buf);


}
