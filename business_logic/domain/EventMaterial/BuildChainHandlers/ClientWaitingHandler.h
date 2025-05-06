#ifndef CLIENTWAITINGHANDLER_H
#define CLIENTWAITINGHANDLER_H

#include "ClientWaiting.h"
#include "EventHandler.h"

class ClientWaitingEventHandler : public EventHandler {
public:
    std::unique_ptr<Event> handle(EventTime& event_time, const int id, const std::vector<std::string>& tokens) override {
        if (id == 3) {
            if (tokens.size() < 3) {
                throw std::invalid_argument("Not enough arguments for ClientWaiting event");
            }

            if (!std::regex_match(tokens[2], std::regex("^[a-z0-9_-]+$"))) {
                throw std::invalid_argument("Invalid client name format");
            }

            return std::make_unique<ClientWaitingEvent>(event_time, tokens[2]);
        }

        return EventHandler::handle(event_time, id, tokens);
    }
};

#endif //CLIENTWAITINGHANDLER_H
