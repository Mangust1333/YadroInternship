cmake_minimum_required(VERSION 3.27)
project(
        computer_club_system
        VERSION 0.0
        DESCRIPTION "A prototype of a system that monitors the work of a computer club, processes events and calculates the revenue for the day and the time of occupancy of each table."
        HOMEPAGE_URL "https://github.com/Mangust1333/YadroInternship"
        LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(task presentation/main.cpp)
add_subdirectory(business_logic/domain)
add_subdirectory(business_logic/services)
add_subdirectory(infrastructure/argument_parser)
add_subdirectory(infrastructure/file_parser)
add_subdirectory(presentation/)

target_link_libraries(task PRIVATE
        domain
        argument_parser
        file_parser
        services
        presentation
)

target_include_directories(task PRIVATE
        business_logic/domain
        infrastructure/argument_parser/include
        infrastructure/file_parser/include
)

enable_testing()
add_subdirectory(tests)