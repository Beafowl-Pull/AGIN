find_package(Threads REQUIRED)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2")

add_executable(agin)

target_sources(agin PRIVATE
        main.cpp
)

target_link_libraries(agin
    PRIVATE
    Threads::Threads
)

target_include_directories(agin PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

set_target_properties(agin PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)
