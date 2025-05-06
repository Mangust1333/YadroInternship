#include "FileParser.h"
#include "EventHandler.h"
#include <fstream>
#include <sstream>
#include <regex>
#include <stdexcept>

namespace FileParser {
FileParser::FileParser(std::filesystem::path file_path, const std::shared_ptr<EventHandler>& handler_chain)
    : file_path_(std::move(file_path)), handler_chain_(handler_chain) {}

ParseData FileParser::parse() {
    std::ifstream input_file(file_path_);
    if (!input_file.is_open()) {
        throw std::runtime_error("Cannot open file: " + file_path_.string());
    }

    std::string line1, line2, line3;
    if (!std::getline(input_file, line1)
        || !std::getline(input_file, line2)
        || !std::getline(input_file, line3)) {
        throw std::runtime_error("Header is incomplete");
    }

    ParseData data;
    validateHeader(line1, line2, line3);

    data.config.table_count = std::stoi(line1);
    const auto tokens2 = split(line2, ' ');
    data.config.open_time = EventTime(tokens2[0]);
    data.config.close_time = EventTime(tokens2[1]);
    data.config.hourly_rate = std::stoi(line3);

    std::string line;
    size_t line_number = 4;
    EventTime prev_time = EventTime("00:00");

    while (std::getline(input_file, line)) {
        if (line.empty()) continue;
        auto event = parseLine(line, line_number);
        EventTime current_time = event->getTime();

        if (current_time < prev_time) {
            throw std::runtime_error("Line " + std::to_string(line_number) +
                                   ": Event time must be non-decreasing. Previous time: " +
                                   prev_time.toString() + ", current time: " +
                                   current_time.toString());
        }

        prev_time = current_time;
        data.events.push_back(std::move(event));
        ++line_number;
    }

    return data;
}

void FileParser::validateHeader(const std::string& line1,
                                const std::string& line2,
                                const std::string& line3) {
    static const std::regex num_re("^[0-9]+$");

    if (!std::regex_match(line1, num_re)) {
        throw std::runtime_error("Invalid tables count: " + line1);
    }

    const auto tokens = split(line2, ' ');
    if (tokens.size() != 2 || !EventTime::isEventTimeFormat(tokens[0]) || !EventTime::isEventTimeFormat(tokens[1])) {
        throw std::runtime_error("Invalid working time format: " + line2);
    }

    if (!std::regex_match(line3, num_re)) {
        throw std::runtime_error("Invalid price format: " + line3);
    }
}

    std::unique_ptr<Event> FileParser::parseLine(const std::string& line, const size_t line_number) {
        auto tokens = split(line, ' ');
        if (tokens.size() < 2) {
            throw std::runtime_error("Line " + std::to_string(line_number) + ": malformed");
        }
        if (!EventTime::isEventTimeFormat(tokens[0])) {
            throw std::runtime_error("Line " + std::to_string(line_number) + ": invalid time format");
        }
        auto time = EventTime(tokens[0]);
        const int id = std::stoi(tokens[1]);
        try {
            return handler_chain_->handle(time, id, tokens);
        } catch (const std::exception& ex) {
            throw std::runtime_error("Line " + std::to_string(line_number) + ": " + ex.what());
        }
    }

    std::vector<std::string> FileParser::split(const std::string& line, const char delimiter) {
        std::vector<std::string> result;
        std::istringstream ss(line);
        std::string item;
        while (std::getline(ss, item, delimiter)) {
            result.push_back(item);
        }
        return result;
    }
} // namespace FileParser
