//
// Created by beafowl on 07/11/23.
//

#ifndef AGIN_COMMANDHANDLER_HPP
#define AGIN_COMMANDHANDLER_HPP

#include <string>
#include <utility>

namespace pbrain {
    class CommandHandler
    {
        public:
            static CommandHandler &getInstance()
            {
                static CommandHandler instance;
                return instance;
            }

            CommandHandler() = default;

            ~CommandHandler() = default;

            static void checkCommand(const std::string &command);

            static void startGame(const std::string &command);
    };
} // namespace pbrain

#endif // AGIN_COMMANDHANDLER_HPP
