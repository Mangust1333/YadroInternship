#ifndef CLIENTARRIVEDHANDLER_H
#define CLIENTARRIVEDHANDLER_H

#include "ClientArrived.h"
#include "EventHandler.h"
#include <regex>

class ClientArrivedEventHandler : public EventHandler {
public:
    std::unique_ptr<Event> handle(EventTime& event_time, const int id, const std::vector<std::string>& tokens) override {
        if (id == 1) {
            if (tokens.size() < 3) {
                throw std::invalid_argument("Not enough arguments for ClientArrived event");
            }

            if (!std::regex_match(tokens[2], std::regex("^[a-z0-9_-]+$"))) {
                throw std::invalid_argument("Invalid client name format");
            }

            return std::make_unique<ClientArrivedEvent>(event_time, tokens[2]);
        }

        return EventHandler::handle(event_time, id, tokens);
    }
};

#endif //CLIENTARRIVEDHANDLER_H
