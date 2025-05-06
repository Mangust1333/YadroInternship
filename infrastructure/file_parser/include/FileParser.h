#ifndef FILEPARSER_H
#define FILEPARSER_H

#include <EventHandler.h>
#include <IFileParser.h>
#include <filesystem>
#include <string>


namespace FileParser {
    class FileParser : public IFileParser {
    public:
        FileParser(std::filesystem::path file_path, const std::shared_ptr<EventHandler>& handler_chain);

        ~FileParser() override = default;

        [[nodiscard]] ParseData parse() override;
    private:
        std::shared_ptr<EventHandler> handler_chain_;
        std::filesystem::path file_path_;

        static void validateHeader(const std::string& line1,
                                   const std::string& line2,
                                   const std::string& line3);

        std::unique_ptr<Event> parseLine(const std::string& line, size_t line_number);

        static std::vector<std::string> split(const std::string& line, char delimiter);
    };
} // FileParser
#endif //FILEPARSER_H
