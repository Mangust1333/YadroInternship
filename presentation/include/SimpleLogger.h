#ifndef SIMPLELOGGER_H
#define SIMPLELOGGER_H

#include "ClubResult.h"
#include "Event.h"

class SimpleLogger {
public:
    static void log(const TableInfo& table_info);
    static void log(const Event& event);
    static void log(const ClubResult& club_result);
};

#endif //SIMPLELOGGER_H
