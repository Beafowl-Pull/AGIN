//
// Created by beafowl on 07/11/23.
//

#ifndef AGIN_COMMANDHANDLER_HPP
#define AGIN_COMMANDHANDLER_HPP

#include <functional>
#include <string>
#include <utility>
#include <unordered_map>

namespace pbrain {
    class CommandHandler
    {
        public:
            CommandHandler(const CommandHandler &other) = delete;

            CommandHandler &operator=(const CommandHandler &other) = delete;

            CommandHandler(CommandHandler &&other) noexcept = delete;

            CommandHandler &operator=(CommandHandler &&other) noexcept = delete;

            static CommandHandler &getInstance()
            {
                static CommandHandler instance;
                return instance;
            }

            void checkCommand(const std::string &command);

            void startGame(const std::string &command);

            void doTurn(const std::string &command) const;

            void doBegin() const;

        private:
            CommandHandler();
            ~CommandHandler() = default;
            bool _gameStarted = false;
            std::unordered_map<std::string, std::function<void()>> _commandsMap;
            std::string _parsedCommand;
            std::string _commands;
    };
} // namespace pbrain

#endif // AGIN_COMMANDHANDLER_HPP
