//
// Created by beafowl on 07/11/23.
//

#ifndef AGIN_COMMANDHANDLER_HPP
#define AGIN_COMMANDHANDLER_HPP

#include <string>
#include <utility>

namespace pbrain {
    class commandHandler
    {
        public:
            static commandHandler &getInstance()
            {
                static commandHandler instance("command");
                return instance;
            }

            commandHandler() = default;

            explicit commandHandler(std::string command)
                : command(std::move(command)) {};

            ~commandHandler() = default;

            static void checkCommand(const std::string &command);

        private:
            std::string command;
    };
} // namespace pbrain

#endif // AGIN_COMMANDHANDLER_HPP
