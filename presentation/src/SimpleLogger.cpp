#include "SimpleLogger.h"
#include <iostream>

void SimpleLogger::log(const TableInfo &table_info) {
    std::cout << table_info.getTableId() << " " << table_info.getRevenue() << " " << table_info.getOccupiedMinutes() << std::endl;
}

void SimpleLogger::log(const Event& event) {
    std::cout << event.toString() << std::endl;
}

void SimpleLogger::log(const ClubResult& club_result) {
    std::cout << club_result.open_time.toString() << std::endl;
    for(const auto& i : club_result.events) {
        log(*i);
    }
    std::cout << club_result.end_time.toString() << std::endl;
    for(const auto& i : club_result.table_stats) {
        log(i);
    }
}
