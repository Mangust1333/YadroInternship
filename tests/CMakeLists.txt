include(FetchContent)

FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG release-1.12.1
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(
        club_tests
        ClubServiceTests.cpp
)

target_link_libraries(
        club_tests
        domain
        file_parser
        argument_parser
        services
        GTest::gtest_main
)

target_include_directories(club_tests PUBLIC ${PROJECT_SOURCE_DIR})

include(GoogleTest)

gtest_discover_tests(club_tests)