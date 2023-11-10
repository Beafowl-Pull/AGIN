/*
** EPITECH PROJECT, 2023
** AGIN
** File description:
** info
*/

#ifndef INFO_HPP_
#define INFO_HPP_

#include <string>

namespace pbrain {
    struct Info
    {
            std::size_t timeoutTurn;
            std::size_t timeoutMatch;
            std::size_t maxMemory;
            std::size_t timeLeft;
            std::size_t gameType;
            std::size_t rule;
            std::size_t evaluate;
            std::size_t folder;
    };

    class InfoHandler
    {
        public:
            InfoHandler(const InfoHandler &infoHandler) = delete;

            InfoHandler &operator=(const InfoHandler &infoHandler) = delete;

            InfoHandler(InfoHandler &&infoHandler) = delete;

            InfoHandler &operator=(InfoHandler &&infoHandler) = delete;

            static InfoHandler &getInstance()
            {
                static InfoHandler instance;
                return instance;
            }

            // NOLINTNEXTLINE
            void setInfo(const std::string &info, const std::string &value)
            {
                if (info == "timeout_turn") {
                    _info.timeoutTurn = std::stoi(value);
                } else if (info == "timeout_match") {
                    _info.timeoutMatch = std::stoi(value);
                } else if (info == "max_memory") {
                    _info.maxMemory = std::stoi(value);
                } else if (info == "time_left") {
                    _info.timeLeft = std::stoi(value);
                } else if (info == "game_type") {
                    _info.gameType = std::stoi(value);
                } else if (info == "rule") {
                    _info.rule = std::stoi(value);
                } else if (info == "evaluate") {
                    _info.evaluate = std::stoi(value);
                } else if (info == "folder") {
                    _info.folder = std::stoi(value);
                }
            }

            [[nodiscard]] Info getInfo() const
            {
                return _info;
            }

        private:
            InfoHandler() = default;

            ~InfoHandler() = default;

            Info _info;
    };
} // namespace pbrain

#endif /* !INFO_HPP_ */
