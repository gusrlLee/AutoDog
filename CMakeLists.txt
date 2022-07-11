cmake_minimum_required(VERSION 3.0)
project(Auto)

find_package(OpenCV REQUIRED)

include_directories(
    ${OpenCV_INCLUDE_DIRS} 
    ${CMAKE_SOURCE_DIR}/include
)

add_executable(${PROJECT_NAME} 
    src/main.cpp
    src/MainSystem.cpp
)

target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS})


