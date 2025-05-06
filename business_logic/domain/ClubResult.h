#ifndef FINALSTATISTIC_H
#define FINALSTATISTIC_H
#include <memory>
#include <vector>

#include "Event.h"
#include "EventTime.h"
#include "TableInfo.h"

struct ClubResult {
    EventTime open_time;
    EventTime end_time;
    std::vector<std::unique_ptr<Event>> events;
    std::vector<TableInfo> table_stats;
};

#endif //FINALSTATISTIC_H
