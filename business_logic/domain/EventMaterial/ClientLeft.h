#ifndef CLIENTLEFT_H
#define CLIENTLEFT_H
#include "Event.h"
#include "EventTime.h"

class ClientLeftEvent : public Event {
public:
    explicit ClientLeftEvent(const EventTime& time, std::string name) : Event(time, 4, std::move(name)) {}


    [[nodiscard]] std::unique_ptr<Event> clone() const override {
        return std::make_unique<ClientLeftEvent>(*this);
    }
};

#endif //CLIENTLEFT_H
