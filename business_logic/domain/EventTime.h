#ifndef TIME_H
#define TIME_H

#include <string>

class EventTime {
public:
    explicit EventTime(const std::string& time_string);

    bool static isEventTimeFormat(const std::string& time_string);

    bool operator<(const EventTime& other) const;

    bool operator>(const EventTime& other) const;

    bool operator==(const EventTime& other) const;

    int operator-(const EventTime& other) const;

    [[nodiscard]] std::string toString() const;

private:
    int hour_{};
    int minute_{};

    bool parse(const std::string& time_string);

    [[nodiscard]] int toMinutes() const;
};

#endif //TIME_H
