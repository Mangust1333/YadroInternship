#ifndef CLIENTARRIVED_H
#define CLIENTARRIVED_H

#include <Event.h>
#include <EventTime.h>

class ClientArrivedEvent : public Event {
public:
    explicit ClientArrivedEvent(const EventTime& time, std::string name) : Event(time, 1, std::move(name)) {}

    [[nodiscard]] std::unique_ptr<Event> clone() const override {
        return std::make_unique<ClientArrivedEvent>(*this);
    }
};

#endif //CLIENTARRIVED_H
