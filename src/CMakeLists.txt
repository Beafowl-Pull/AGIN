find_package(Threads REQUIRED)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2")

add_executable(pbrain-agin)

add_subdirectory(CommandHandler)
add_subdirectory(Main)

target_sources(pbrain-agin PRIVATE
        main.cpp
)

target_link_libraries(pbrain-agin
    PRIVATE
    Threads::Threads
)

target_include_directories(pbrain-agin PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

set_target_properties(pbrain-agin PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)
