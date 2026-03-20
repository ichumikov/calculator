cmake_minimum_required(VERSION 3.5)

project(calculator)

add_executable(calculator
    src/main.cpp
    src/app.cpp
    src/math.cpp
)

target_include_directories(calculator 
	PRIVATE
        ${PROJECT_SOURCE_DIR}/src
)
