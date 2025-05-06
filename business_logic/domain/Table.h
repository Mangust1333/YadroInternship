#ifndef TABLE_H
#define TABLE_H

#include <string>
#include <utility>

#include "EventTime.h"

class Table {
public:
    Table() = default;
    explicit Table(int id) : id_(id) {}
    Table(const Table& other) = default;
    Table& operator=(const Table& other) {
        if(this == &other) {
            return *this;
        }

        id_ = other.id_;
        client_name_ = other.client_name_;
        session_start_ = other.session_start_;
        total_minutes_ = other.total_minutes_;
        total_income_ = other.total_income_;
        return *this;
    }
    Table(Table&& other) noexcept :
    id_(other.id_),
    client_name_(std::exchange(other.client_name_, "")),
    session_start_(other.session_start_),
    total_minutes_(other.total_minutes_),
    total_income_(other.total_income_) {}
    Table& operator=(Table&& other) noexcept {
        id_ = other.id_;
        client_name_ = std::move(other.client_name_);
        session_start_ = other.session_start_;
        total_minutes_ = other.total_minutes_;
        total_income_ = other.total_income_;
        return *this;
    }

    [[nodiscard]] bool isOccupied() const {
        return !client_name_.empty();
    }

    void seat(const std::string& name, const EventTime& start_time) {
        client_name_ = name;
        session_start_ = start_time;
    }

    void leave(const EventTime& end_time, const int hourly_rate) {
        if (client_name_.empty()) return;
        const int duration = end_time - session_start_;
        const int charge_hours = (duration + 59) / 60;
        total_minutes_ += duration;
        total_income_ += charge_hours * hourly_rate;
        client_name_.clear();
    }

    [[nodiscard]] int getId() const { return id_; }

    std::string getClientName() { return client_name_; }

    [[nodiscard]] int getTotalIncome() const { return total_income_; }

    [[nodiscard]] int getTotalMinutes() const { return total_minutes_; }
private:
    int id_;
    std::string client_name_;
    EventTime session_start_{"00:00"};
    int total_minutes_ = 0;
    int total_income_ = 0;
};

#endif // TABLE_H
