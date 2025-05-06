add_library(services
        ClubService.cpp
        ClubService.h
)

target_include_directories(services PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)
target_link_libraries(services
        PUBLIC
        domain
)