#ifndef CLUBCONFIG_H
#define CLUBCONFIG_H

#include "EventTime.h"

struct ClubConfig {
    int table_count = 0;
    EventTime open_time{"00:00"};
    EventTime close_time{"00:00"};
    int hourly_rate = 0;
};


#endif //CLUBCONFIG_H
