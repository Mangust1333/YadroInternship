#ifndef CLIENTSATBYQUEUE_H
#define CLIENTSATBYQUEUE_H

#include "Event.h"
#include "EventTime.h"

class ClientSatByQueueEvent : public Event {
public:
    explicit ClientSatByQueueEvent(const EventTime& time, std::string name, int table_id)
        : Event(time, 12, std::move(name)), table_id_(table_id) {}


    [[nodiscard]] std::unique_ptr<Event> clone() const override {
        return std::make_unique<ClientSatByQueueEvent>(*this);
    }

    [[nodiscard]] std::string toString() const override {
        return Event::toString() + " " + std::to_string(table_id_);
    }

private:
    int table_id_;
};

#endif //CLIENTSATBYQUEUE_H
