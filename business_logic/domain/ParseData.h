#ifndef PARSEDATA_H
#define PARSEDATA_H
#include <memory>
#include <vector>
#include "ClubConfig.h"
#include "Event.h"

struct ParseData {
    ClubConfig config;
    std::vector<std::unique_ptr<Event>> events;
};

#endif //PARSEDATA_H
