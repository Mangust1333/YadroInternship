#ifndef CLIENTSATDOWN_H
#define CLIENTSATDOWN_H

#include <Event.h>
#include <EventTime.h>

class ClientSatDownEvent : public Event {
public:
    explicit ClientSatDownEvent(const EventTime& time, std::string name, const int table_id)
        : Event(time, 2, std::move(name)), table_id_(table_id) {}

    [[nodiscard]] std::string toString() const override {
        return Event::toString() + " " + std::to_string(table_id_);
    }

    [[nodiscard]] std::unique_ptr<Event> clone() const override {
        return std::make_unique<ClientSatDownEvent>(*this);
    }

    [[nodiscard]] int getTableId() const { return table_id_; };

private:
    int table_id_;
};

#endif //CLIENTSATDOWN_H
