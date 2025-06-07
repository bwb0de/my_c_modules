#ifndef TIME_TOOL_H
#define TIME_TOOL_H


typedef struct TimeHoras {
    int h;
    int m;
    int s;
} hour_t;


hour_t to_hour_t(double sec);
hour_t time_delta(hour_t t1, hour_t t2);
double from_hour_t(hour_t t);
void print_time(hour_t t);


#endif
