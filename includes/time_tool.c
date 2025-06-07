#include <stdlib.h>
#include "time_tool.h"
#include <stdio.h>

hour_t to_hour_t(double sec){
    double h, m, s;
    h = sec / 3600;
    int h_final = (int)h;
    double h_frac = h - (double)h_final;
    m = h_frac * 60;
    int m_final = (int)m;
    double m_frac = m - (double)m_final;
    s = m_frac * 60;
    int s_final = (int)s + 1;

    hour_t out = {
        .h = h_final,
        .m = m_final,
        .s = s_final
    };

    return out;
}


double from_hour_t(hour_t t){
    double out = t.s + (t.m * 60) + (t.h * 3600);
    return out;

}


hour_t time_delta(hour_t t1, hour_t t2){
    hour_t out = {.h = t2.h - t1.h, .m = t2.m - t1.m, .s = t2.s - t1.s};
    return out;
}


void print_time(hour_t t){
    printf("%dh%dm%ds\n", t.h, t.m, t.s);
}
