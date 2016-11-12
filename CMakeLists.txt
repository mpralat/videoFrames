cmake_minimum_required(VERSION 3.6)
project(videoFrames)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -lboost_system -lboost_filesystem")

find_package( OpenCV REQUIRED )
include_directories("/usr/include/opencv2")

add_executable(main main.cpp)
include_directories(${OpenCV_INCLUDE_DIRS})
target_link_libraries(main ${OpenCV_LIBS})