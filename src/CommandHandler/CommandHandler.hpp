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

            void checkCommand(const std::string &command);

            void startGame(const std::string &command);

            void doTurn(const std::string &command) const;

            void doBegin() const;

        private:
            bool _gameStarted = false;
    };
} // namespace pbrain

#endif // AGIN_COMMANDHANDLER_HPP
