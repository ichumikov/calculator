cmake_minimum_required(VERSION 3.14)

project(calculator)
set(CMAKE_BUILD_TYPE Debug)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

# --- libmath ---
FetchContent_Declare(
    libmath
    GIT_REPOSITORY https://github.com/ichumikov/libmath.git
    GIT_TAG main
)

FetchContent_MakeAvailable(libmath)

find_program(CLANG_TIDY_EXE NAMES "clang-tidy")
if(CLANG_TIDY_EXE)
    set(CMAKE_CXX_CLANG_TIDY "${CLANG_TIDY_EXE}" "-extra-arg=-Wno-unknown-warning-option" "-header-filter=.*")
    message(STATUS "Clang-tidy found: ${CLANG_TIDY_EXE}")
else()
    message(WARNING "Clang-tidy not found")
endif()

# --- nlohmann/json ---
FetchContent_Declare(
    nlohmann_json
    GIT_REPOSITORY https://github.com/nlohmann/json.git
    GIT_TAG v3.11.3
)
FetchContent_MakeAvailable(nlohmann_json)

# --- spdlog ---
FetchContent_Declare(
    spdlog
    GIT_REPOSITORY https://github.com/gabime/spdlog.git
    GIT_TAG v1.13.0
)
FetchContent_MakeAvailable(spdlog)

# --- googletest ---
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.14.0
)
FetchContent_MakeAvailable(googletest)
find_package(PostgreSQL REQUIRED)

add_executable(calculator
    src/main.cpp
    src/app.cpp
    src/logger.cpp
    src/database.cpp
)

target_include_directories(calculator
    PRIVATE
    ${PROJECT_SOURCE_DIR}/src
)

target_link_libraries(calculator
    PRIVATE
    libmath
    nlohmann_json::nlohmann_json
    spdlog::spdlog
    PostgreSQL::PostgreSQL
)

# --- tests ---
enable_testing()

add_executable(calculator_tests
    tests/calculator_test.cpp
    src/app.cpp
    src/logger.cpp
    src/database.cpp
)

target_include_directories(calculator_tests
    PRIVATE
    ${PROJECT_SOURCE_DIR}/src
)

target_link_libraries(calculator_tests
    PRIVATE
    libmath
    nlohmann_json::nlohmann_json
    spdlog::spdlog
    PostgreSQL::PostgreSQL
    GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(calculator_tests)