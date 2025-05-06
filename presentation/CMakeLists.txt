add_library(presentation
        src/SimpleLogger.cpp
        include/SimpleLogger.h
)

target_include_directories(presentation
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(presentation
        PUBLIC
        domain
        file_parser
        argument_parser
        services
)