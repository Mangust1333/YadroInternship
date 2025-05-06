#ifndef IEVENT_H
#define IEVENT_H
#include "EventTime.h"
#include <memory>

class Event {
public:
    virtual ~Event() = default;
    [[nodiscard]] virtual std::string toString() const {
        return this->time_.toString() + " " + std::to_string(id_) + " " + name_;
    }
    [[nodiscard]] virtual std::unique_ptr<Event> clone() const = 0;
    [[nodiscard]] const EventTime& getTime() const { return time_; }
    [[nodiscard]] int getId() const { return id_; }
    [[nodiscard]] const std::string& getName() const { return name_; }

protected:
    Event(const EventTime& time, const int id, std::string name)
        : time_(time), id_(id), name_(std::move(name)) {}
    EventTime time_;
    int id_;
    std::string name_;
};

#endif //IEVENT_H
