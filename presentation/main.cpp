#include <ArgumentParser.h>
#include <FileParser.h>
#include <iostream>

#include "ClientArrivedHandler.h"
#include "ClientLeftEventHandler.h"
#include "ClientSatDownHandler.h"
#include "ClientWaitingHandler.h"
#include "ClubService.h"
#include <SimpleLogger.h>

struct Options {
    std::string input_file;
};

int main(int argc, char** argv) {
    Options opt;
    ArgumentParser::ArgParser parser("Program");

    parser.AddStringArgument('f', "file", "path to input file")
    .Default("../input/test_file.txt")
    .StoreValue(opt.input_file);
    parser.AddHelp('h', "help", "Program accumulate arguments");

    if(!parser.Parse(argc, argv)) {
        std::cout << "Wrong argument" << std::endl;
        std::cout << parser.HelpDescription() << std::endl;
        return 1;
    }

    if(parser.Help()) {
        std::cout << parser.HelpDescription() << std::endl;
        return 0;
    }

    if(opt.input_file.empty()) {
        std::cout << "Not a single file has been transferred" << std::endl;
        std::cout << parser.HelpDescription();
        return 1;
    }

    auto event_handler_chain = std::make_shared<ClientArrivedEventHandler>();
    event_handler_chain
    ->setNext(std::make_shared<ClientLeftEventHandler>())
    ->setNext(std::make_shared<ClientWaitingEventHandler>())
    ->setNext(std::make_shared<ClientSatDownHandler>());

    auto* file_parser = new FileParser::FileParser(opt.input_file, event_handler_chain);

    auto [config, events] = file_parser->parse();

    auto sevice = ClubService(config);

    auto result = sevice.run(events);

    SimpleLogger::log(result);

    return 0;
}
