#ifndef CLIENTFINAL_H
#define CLIENTFINAL_H

#include "Event.h"
#include "EventTime.h"

class ClientFinalEvent : public Event {
public:
    explicit ClientFinalEvent(const EventTime& time, std::string name) : Event(time, 11, std::move(name)) {}

    [[nodiscard]] std::unique_ptr<Event> clone() const override {
        return std::make_unique<ClientFinalEvent>(*this);
    }
};

#endif //CLIENTFINAL_H
