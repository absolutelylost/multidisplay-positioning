cmake_minimum_required(VERSION 3.20)

project(MonitorChanges)

add_executable(MonitorChanges main.cpp)
target_link_libraries(MonitorChanges user32)

add_executable(PerformPlacementChanges changes.cpp)
target_link_libraries(PerformPlacementChanges user32)