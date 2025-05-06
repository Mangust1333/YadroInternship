#ifndef CLIENTWAITING_H
#define CLIENTWAITING_H

#include <Event.h>
#include <EventTime.h>

#include <utility>

class ClientWaitingEvent : public Event {
public:
    explicit ClientWaitingEvent(const EventTime& time, std::string name) : Event(time, 3, std::move(name)) {}

    [[nodiscard]] std::unique_ptr<Event> clone() const override {
        return std::make_unique<ClientWaitingEvent>(*this);
    }
};

#endif //CLIENTWAITING_H
