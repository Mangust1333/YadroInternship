#ifndef EVENTHANDLER_H
#define EVENTHANDLER_H

#include <memory>
#include <vector>
#include <string>
#include "Event.h"

class EventHandler : public std::enable_shared_from_this<EventHandler> {
protected:
    std::shared_ptr<EventHandler> next_;

public:
    virtual ~EventHandler() = default;

    std::shared_ptr<EventHandler> setNext(std::shared_ptr<EventHandler> next) {
        next_ = next;
        return next;
    }

    virtual std::unique_ptr<Event> handle(EventTime& event_time, const int id, const std::vector<std::string>& tokens) {
        if (next_) {
            return next_->handle(event_time, id, tokens);
        }

        throw std::runtime_error("Unknown event ID: " + std::to_string(id));
    }
};


#endif //EVENTHANDLER_H
