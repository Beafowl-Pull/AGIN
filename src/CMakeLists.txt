find_package(Threads REQUIRED)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2")

add_executable(pbrain_agin)

add_subdirectory(CommandHandler)
add_subdirectory(Main)
add_subdirectory(Brain)

target_sources(pbrain_agin PRIVATE
        main.cpp
)

find_package(Boost 1.75.0 REQUIRED COMPONENTS container)

if (Boost_FOUND)
        target_link_libraries(pbrain_agin PRIVATE ${Boost_LIBRARIES})
endif()

target_link_libraries(pbrain_agin
    PRIVATE
    Threads::Threads
)

target_include_directories(pbrain_agin PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

set_target_properties(pbrain_agin PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)
