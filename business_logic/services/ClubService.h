#ifndef CLUBSERVICE_H
#define CLUBSERVICE_H
#include <map>
#include <memory>
#include <queue>
#include <set>
#include <vector>

#include "ClubConfig.h"
#include "ClubResult.h"
#include "Event.h"
#include "Table.h"

class ClubService {
public:
    explicit ClubService(const ClubConfig& config) : config_(config)
    {
        for(int i = 1; i <= config_.table_count; ++i) {
            tables_[i] = Table(i);
        }
    }

    ClubResult run(const std::vector<std::unique_ptr<Event>>& events);

private:
    const ClubConfig& config_;
    std::map<int, Table> tables_;
    std::set<std::string> present_clients_;
    std::queue<std::string> wait_queue_;
    void seatClient(const std::string& name, int table_id, const EventTime& time);
    void leaveClient(const std::string& name, const EventTime& time, std::vector<std::unique_ptr<Event>>& result);
};

#endif //CLUBSERVICE_H
