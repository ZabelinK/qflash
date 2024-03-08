#ifndef DBG_TIME_H
#define DBG_TIME_H

#include <sys/time.h>
#include <sys/sysinfo.h>


static char line[1024];

static const char * get_time(void) {
    static char time_buf[50];
    struct timeval  tv;
    time_t time;
    suseconds_t millitm;
    struct tm *ti;

    gettimeofday (&tv, NULL);

    time= tv.tv_sec;
    millitm = (tv.tv_usec + 500) / 1000;

    if (millitm == 1000) {
        ++time;
        millitm = 0;
    }

    ti = localtime(&time);
    sprintf(time_buf, "[%02d-%02d_%02d:%02d:%02d:%03d]", ti->tm_mon+1, ti->tm_mday, ti->tm_hour, ti->tm_min, ti->tm_sec, (int)millitm);
    return time_buf;
}

void dbg_time (const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    snprintf(line, sizeof(line), "%s ", get_time());
    vsnprintf(line + strlen(line), sizeof(line) - strlen(line), fmt, args);
    fprintf(stdout, "%s", line);
}

#endif