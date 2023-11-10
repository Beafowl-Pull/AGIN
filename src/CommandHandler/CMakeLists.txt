find_package(Threads REQUIRED)

target_sources(pbrain_agin PRIVATE
        CommandHandler.cpp
)

target_include_directories(pbrain_agin PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
