cmake_minimum_required(VERSION 3.14)

project(calculator)

include(FetchContent)

add_executable(calculator
       	src/main.cpp
	src/app.cpp
)

find_program(CLANG_TIDY_EXE NAMES "clang-tidy")
if(CLANG_TIDY_EXE)
    set(CMAKE_CXX_CLANG_TIDY "${CLANG_TIDY_EXE}" "-extra-arg=-Wno-unknown-warning-option" "-header-filter=.*")
    message(STATUS "Clang-tidy found: ${CLANG_TIDY_EXE}")
else()
    message(WARNING "Clang-tidy not found")
endif()

target_include_directories(calculator
	PRIVATE
	${PROJECT_SOURCE_DIR}/src
)

FetchContent_Declare(
	libmath
	GIT_REPOSITORY https://github.com/ichumikov/libmath.git
	GIT_TAG main
)

FetchContent_GetProperties(libmath)
if(NOT libmath_POPULATED)
	FetchContent_Populate(libmath)
	add_subdirectory(${libmath_SOURCE_DIR} ${libmath_BINARY_DIR})
endif()

target_link_libraries(calculator PRIVATE libmath)
