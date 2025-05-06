#include <EventTime.h>
#include <regex>
#include <stdexcept>

EventTime::EventTime(const std::string& EventTime_string) {
    if (!parse(EventTime_string)) {
        throw std::invalid_argument("Invalid EventTime format");
    }
}

bool EventTime::operator<(const EventTime& other) const {
    return toMinutes() < other.toMinutes();
}

bool EventTime::operator>(const EventTime& other) const {
    return toMinutes() > other.toMinutes();
}

bool EventTime::operator==(const EventTime& other) const {
    return toMinutes() == other.toMinutes();
}

int EventTime::operator-(const EventTime &other) const {
    return this->toMinutes() - other.toMinutes();
}

[[nodiscard]] std::string EventTime::toString() const {
    return std::to_string(hour_) + ":" + (minute_ < 10 ? "0" : "") + std::to_string(minute_);
}

bool EventTime::isEventTimeFormat(const std::string& EventTime_string) {
    static const std::regex EventTime_re(R"((?:[01]\d|2[0-3]):[0-5]\d)");
    return std::regex_match(EventTime_string, EventTime_re);
}

bool EventTime::parse(const std::string& EventTime_string) {
    if (EventTime_string.size() != 5 || EventTime_string[2] != ':') {
        return false;
    }

    try {
        hour_ = std::stoi(EventTime_string.substr(0, 2));
        minute_ = std::stoi(EventTime_string.substr(3, 2));

        if (hour_ < 0 || hour_ >= 24 || minute_ < 0 || minute_ >= 60) {
            return false;
        }

        return true;
    } catch (const std::exception&) {
        return false;
    }
}

int EventTime::toMinutes() const {
    return hour_ * 60 + minute_;
}