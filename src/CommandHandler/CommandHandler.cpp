//
// Created by beafowl on 07/11/23.
//

#include <functional>
#include <iostream>
#include "CommandHandler.hpp"
#include <type_traits>
#include <unordered_map>
#include "Values.hpp"
#include "Error.hpp"

namespace pbrain {
    void commandHandler::checkCommand(const std::string &command)
    {
        std::unordered_map<std::string, std::function<void()>> commands = {
            {"START", [command] {
                try {
                    commandHandler::startGame(command);
                } catch (std::invalid_argument &e) {
                    std::cout << "ERROR" << std::endl;
                }
            }},
        };

        std::string parsedCommand = command.substr(0, command.find(' '));

        if (commands.find(parsedCommand) != commands.end()) {
            try {
                commands[parsedCommand]();
            }
            catch (pbrain::Error &e) {
                std::cout << "ERROR" << std::endl;
            }
        } else {
            std::cout << "ERROR" << std::endl;
        }
    }

    void commandHandler::startGame(const std::string &command)
    {
        std::string size = command.substr(6);
        if (std::stoi(size) > BOARD_SIZE_MAX || std::stoi(size) < BOARD_SIZE_MIN) {
            throw std::invalid_argument("ERROR Invalid size");
            return;
        } else {
            std::cout << "OK" << std::endl;
        }
    }
} // namespace pbrain