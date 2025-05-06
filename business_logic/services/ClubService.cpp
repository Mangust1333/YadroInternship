#include "ClubService.h"
#include "ClientArrived.h"
#include "ClientLeft.h"
#include "ClientSatDown.h"
#include "ClientWaiting.h"
#include "ClientFinal.h"
#include "ClientSatByQueue.h"
#include "ErrorEvent.h"

ClubResult ClubService::run(const std::vector<std::unique_ptr<Event>>& events) {
    std::vector<std::unique_ptr<Event>> result_events;

    for (const auto& evt : events) {
        result_events.push_back(evt->clone());
        const EventTime& time = evt->getTime();
        const std::string& name = evt->getName();

        switch (evt->getId()) {
            case 1:
                if (present_clients_.contains(name)) {
                    result_events.push_back(std::make_unique<ErrorEvent>(time, "YouShallNotPass"));
                    break;
                }

                if (time < config_.open_time || time > config_.close_time) {
                    result_events.push_back(std::make_unique<ErrorEvent>(time, "NotOpenYet"));
                    break;
                }

                present_clients_.insert(name);
                break;

            case 2: {
                int table_id = dynamic_cast<ClientSatDownEvent*>(evt.get())->getTableId();
                if (!present_clients_.contains(name)) {
                    result_events.push_back(std::make_unique<ErrorEvent>(time, "ClientUnknown"));
                    break;
                }

                if (tables_[table_id].isOccupied()) {
                    result_events.push_back(std::make_unique<ErrorEvent>(time, "PlaceIsBusy"));
                    break;
                }

                seatClient(name, table_id, time);
                break;
            }
            case 3: {
                if (!present_clients_.contains(name)) {
                    result_events.push_back(std::make_unique<ErrorEvent>(time, "ClientUnknown"));
                    break;
                }

                bool hasFree = false;
                for (const auto& [id, table] : tables_) {
                    if (!table.isOccupied()) {
                        hasFree = true;
                        break;
                    }
                }

                if (hasFree) {
                    result_events.push_back(std::make_unique<ErrorEvent>(time, "ICanWaitNoLonger!"));
                    break;
                }

                if (wait_queue_.size() >= config_.table_count) {
                    present_clients_.erase(name);
                    result_events.push_back(std::make_unique<ClientFinalEvent>(time, name));
                    break;
                }

                wait_queue_.push(name);
                break;
            }
            case 4:
                if (!present_clients_.contains(name)) {
                    result_events.push_back(std::make_unique<ErrorEvent>(time, "ClientUnknown"));
                    break;
                }

                leaveClient(name, time, result_events);
                break;
        }
    }

    for (const std::string& name : std::set(present_clients_.begin(), present_clients_.end())) {
        leaveClient(name, config_.close_time, result_events);
        result_events.push_back(std::make_unique<ClientFinalEvent>(config_.close_time, name));
    }

    std::vector<TableInfo> stats;
    for (const auto& [id, table] : tables_) {
        stats.emplace_back(
            id,
            table.getTotalIncome(),
            table.getTotalIncome()
        );
    }

    return ClubResult{
        config_.open_time,
        config_.close_time,
        std::move(result_events),
        std::move(stats)
    };
}

void ClubService::seatClient(const std::string& name, int table_id, const EventTime& time) {
    for (auto& [id, table] : tables_) {
        if (table.getClientName() == name) {
            table.leave(time, config_.hourly_rate);
            break;
        }
    }
    tables_[table_id].seat(name, time);
}

void ClubService::leaveClient(const std::string& name, const EventTime& time, std::vector<std::unique_ptr<Event>>& result) {
    for (auto& [id, table] : tables_) {
        if (table.getClientName() == name) {
            table.leave(time, config_.hourly_rate);

            if (!wait_queue_.empty()) {
                std::string next_client = wait_queue_.front();
                wait_queue_.pop();
                tables_[id].seat(next_client, time);
                result.push_back(std::make_unique<ClientSatByQueueEvent>(time, next_client, id));
            }

            break;
        }
    }
    present_clients_.erase(name);
}

