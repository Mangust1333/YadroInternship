#ifndef CLIENTSATDOWNHANDLER_H
#define CLIENTSATDOWNHANDLER_H

#include "ClientSatDown.h"
#include "EventHandler.h"
#include <regex>

class ClientSatDownHandler : public EventHandler {
public:
    std::unique_ptr<Event> handle(EventTime& event_time, const int id, const std::vector<std::string>& tokens) override {
        if (id == 2) {
            if (tokens.size() < 4) {
                throw std::invalid_argument("Not enough arguments for ClientSatDown event");
            }

            if (!std::regex_match(tokens[2], std::regex("^[a-z0-9_-]+$"))) {
                throw std::invalid_argument("Invalid client name format");
            }

            try {
                int table_num = std::stoi(tokens[3]);

                if (table_num <= 0) {
                    throw std::invalid_argument("Table number must be positive");
                }

                return std::make_unique<ClientSatDownEvent>(event_time, tokens[2], table_num);
            }
            catch (const std::exception& e) {
                throw std::invalid_argument("Invalid table number format: " + std::string(e.what()));
            }
        }

        return EventHandler::handle(event_time, id, tokens);
    }
};

#endif //CLIENTSATDOWNHANDLER_H
