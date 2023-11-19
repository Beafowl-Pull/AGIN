find_package(Threads REQUIRED)

target_sources(pbrain-agin PRIVATE
        CommandHandler.cpp
)

target_include_directories(pbrain-agin PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
