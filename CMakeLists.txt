cmake_minimum_required(VERSION 3.0)
add_compile_options( -g )
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(Auto)

add_subdirectory(lib)
find_package(OpenCV REQUIRED)


set ( SDK_INCLUDE_DIR 
    ${CMAKE_SOURCE_DIR}/lib/sdk/include
    ${CMAKE_SOURCE_DIR}/lib/sdk/src
    ${CMAKE_SOURCE_DIR}/lib/sdk/src/hal
)

include_directories(
    ${OpenCV_INCLUDE_DIRS} 
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/config
    ${SDK_INCLUDE_DIR}
)

if ( UNIX ) 
    include_directories(${CMAKE_SOURCE_DIR}/lib/sdk/src/linux)
elseif ( APPLE )
    include_directories(${CMAKE_SOURCE_DIR}/lib/sdk/src/macOS)
endif()

add_executable(${PROJECT_NAME} 
    src/main.cpp
    src/DogStatus.cpp
    src/VisualOdometry.cpp
    src/MainSystem.cpp
    src/lidar.cpp
)

target_link_libraries(${PROJECT_NAME} 
    ${OpenCV_LIBS} 
    ${SDK_LIBRARY}
    -lpthread
)


