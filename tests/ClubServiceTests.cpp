#include <gtest/gtest.h>
#include "ClientArrivedHandler.h"
#include "ClientLeftEventHandler.h"
#include "ClientSatDownHandler.h"
#include "ClientWaitingHandler.h"
#include "ClubService.h"

#include <memory>
#include <string>
#include "FileParser.h"


class BaseMockFileParser : public FileParser::FileParser {
protected:
    ClubConfig config;
    std::vector<std::unique_ptr<Event>> events;

public:
    BaseMockFileParser(const std::string& file_path, std::shared_ptr<EventHandler> handler)
        : FileParser::FileParser(file_path, handler) {
        config.table_count = 3;
        config.open_time = EventTime("09:00");
        config.close_time = EventTime("19:00");
        config.hourly_rate = 10;
    }

    ParseData parse() override {
        return {config, std::move(events)};
    }

protected:
    void addEvent(std::unique_ptr<Event> event) {
        events.push_back(std::move(event));
    }
};


class RevenueMockParser : public BaseMockFileParser {
public:
    RevenueMockParser(const std::string& file_path, std::shared_ptr<EventHandler> handler)
        : BaseMockFileParser(file_path, handler) {
        addEvent(std::make_unique<ClientArrivedEvent>(EventTime("09:00"), "client1"));
        addEvent(std::make_unique<ClientSatDownEvent>(EventTime("09:10"), "client1", 1));
        addEvent(std::make_unique<ClientLeftEvent>(EventTime("10:10"), "client1"));
    }
};


TEST(ClubServiceTest, CorrectRevenueCalculation) {
    auto h1 = std::make_shared<ClientArrivedEventHandler>();
    auto h2 = std::make_shared<ClientLeftEventHandler>();
    auto h3 = std::make_shared<ClientWaitingEventHandler>();
    auto h4 = std::make_shared<ClientSatDownHandler>();
    h1->setNext(h2)->setNext(h3)->setNext(h4);

    RevenueMockParser file_parser("revenue.txt", h1);
    auto [config, events] = file_parser.parse();

    ClubService service(config);
    auto result = service.run(events);

    int expected_revenue = 10 * 1;
    ASSERT_EQ(result.table_stats[0].getRevenue(), expected_revenue);
}

class OccupiedTableParser : public BaseMockFileParser {
public:
    OccupiedTableParser(const std::string& file_path, std::shared_ptr<EventHandler> handler)
        : BaseMockFileParser(file_path, handler) {
        addEvent(std::make_unique<ClientArrivedEvent>(EventTime("09:00"), "client1"));
        addEvent(std::make_unique<ClientSatDownEvent>(EventTime("09:05"), "client1", 1));
        addEvent(std::make_unique<ClientArrivedEvent>(EventTime("09:10"), "client2"));
        addEvent(std::make_unique<ClientSatDownEvent>(EventTime("09:15"), "client2", 1));
    }
};

TEST(ClubServiceTest, ClientTakesAlreadyOccupiedTable) {
    auto h1 = std::make_shared<ClientArrivedEventHandler>();
    auto h2 = std::make_shared<ClientLeftEventHandler>();
    auto h3 = std::make_shared<ClientWaitingEventHandler>();
    auto h4 = std::make_shared<ClientSatDownHandler>();
    h1->setNext(h2)->setNext(h3)->setNext(h4);

    OccupiedTableParser file_parser("occupied.txt", h1);
    auto [config, events] = file_parser.parse();

    ClubService service(config);
    auto result = service.run(events);

    // Ищем нужный ErrorEvent
    bool found_error = false;

    for (const auto& event_ptr : result.events) {
        if (event_ptr->getId() == 13 && event_ptr->getName() == "PlaceIsBusy" &&
            event_ptr->getTime() == EventTime("09:15")) {
            found_error = true;
            break;
            }
    }

    ASSERT_TRUE(found_error) << "ErrorEvent с id=13, name='PlaceIsBusy' и временем 09:15 не найден.";
}
