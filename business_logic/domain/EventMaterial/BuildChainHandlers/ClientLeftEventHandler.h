#ifndef CLIENTLEFTEVENTHANDLER_H
#define CLIENTLEFTEVENTHANDLER_H
#include "ClientLeft.h"
#include "EventHandler.h"

class ClientLeftEventHandler : public EventHandler {
public:
    std::unique_ptr<Event> handle(EventTime& event_time, const int id, const std::vector<std::string>& tokens) override {
        if (id == 4) {
            if (tokens.size() < 3) {
                throw std::invalid_argument("Not enough arguments for ClientLeft event");
            }

            if (!std::regex_match(tokens[2], std::regex("^[a-z0-9_-]+$"))) {
                throw std::invalid_argument("Invalid client name format");
            }

            return std::make_unique<ClientLeftEvent>(event_time, tokens[2]);
        }

        return EventHandler::handle(event_time, id, tokens);
    }
};

#endif //CLIENTLEFTEVENTHANDLER_H
