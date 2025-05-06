#ifndef ERROREVENT_H
#define ERROREVENT_H

#include "Event.h"
#include "EventTime.h"

class ErrorEvent : public Event {
public:
    explicit ErrorEvent(const EventTime& time, std::string error_name) : Event(time, 13, std::move(error_name)) {}

    [[nodiscard]] std::unique_ptr<Event> clone() const override {
        return std::make_unique<ErrorEvent>(*this);
    }
};

#endif //ERROREVENT_H
