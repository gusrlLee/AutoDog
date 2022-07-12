cmake_minimum_required(VERSION 3.0)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
project(Auto)

find_package(OpenCV REQUIRED)

include_directories(
    ${OpenCV_INCLUDE_DIRS} 
    ${CMAKE_SOURCE_DIR}/include
)

add_executable(${PROJECT_NAME} 
    src/main.cpp
    src/MainSystem.cpp
    src/DogStatus.cpp
    src/VisualOdometry.cpp
)

target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS} -lpthread)


