add_library(file_parser
        include/FileParser.h
        include/IFileParser.h
        src/FileParser.cpp
)

target_include_directories(file_parser PUBLIC include)
target_link_libraries(file_parser PUBLIC domain)
