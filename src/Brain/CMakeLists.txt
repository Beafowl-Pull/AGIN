find_package(Threads REQUIRED)

target_sources(agin PRIVATE
        Brain.cpp
        Neighbor.cpp
)

target_include_directories(agin PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
