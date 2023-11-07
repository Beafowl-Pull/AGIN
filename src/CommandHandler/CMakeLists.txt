find_package(Threads REQUIRED)

target_sources(agin PRIVATE
        CommandHandler.cpp
)

target_include_directories(agin PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
