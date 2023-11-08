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
                static commandHandler instance;
                return instance;
            }

            commandHandler() = default;

            ~commandHandler() = default;

            static void checkCommand(const std::string &command);

            static void startGame(const std::string &command);

            static void doTurn(const std::string &command);
    };
} // namespace pbrain

#endif // AGIN_COMMANDHANDLER_HPP
