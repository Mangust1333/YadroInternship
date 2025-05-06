add_library(argument_parser STATIC
        include/ArgumentParser.h
        src/ArgumentParser.cpp
)

target_include_directories(argument_parser PUBLIC include)