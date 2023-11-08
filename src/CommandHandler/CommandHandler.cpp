//
// Created by beafowl on 07/11/23.
//

#include "CommandHandler.hpp"
#include <functional>
#include <iostream>
#include "Error.hpp"
#include "Values.hpp"
#include <type_traits>
#include <unordered_map>

namespace pbrain {
    void CommandHandler::checkCommand(const std::string &command)
    {
        std::unordered_map<std::string, std::function<void()>> commands = {
            {"START", [command] {
                try {
                    CommandHandler::startGame(command);
                } catch (std::invalid_argument &e) {
                    throw pbrain::Error(e.what());
                }
            }}
        };
        std::string parsedCommand = command.substr(0, command.find(' '));

        if (commands.find(parsedCommand) != commands.end()) {
            try {
                commands[parsedCommand]();
            } catch (pbrain::Error &e) {
                std::cerr << "ERROR " << e.what() << std::endl;
            }
        } else {
            std::cout << "ERROR Command not found" << std::endl;
        }
    }

    void CommandHandler::startGame(const std::string &command)
    {
        std::string size = command.substr(6);
        if (std::stoi(size) > BOARD_SIZE_MAX || std::stoi(size) < BOARD_SIZE_MIN) {
            throw std::invalid_argument("Invalid size");
            return;
        } else {
            std::cout << "OK" << std::endl;
        }
    }
} // namespace pbrain
