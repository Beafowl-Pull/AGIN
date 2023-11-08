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
    CommandHandler::CommandHandler() : _commands(" ")
    {
        _commandsMap = {
            {"START", [this] {
                try {
                    CommandHandler::startGame(_commands);
                } catch (std::invalid_argument &e) {
                    throw pbrain::Error(e.what());
                }
            }}
        };
    }

    void CommandHandler::checkCommand(const std::string &command)
    {
        _parsedCommand = command.substr(0, command.find(' '));
        _commands = command;

        if (_commandsMap.find(_parsedCommand) != _commandsMap.end()) {
            try {
                _commandsMap[_parsedCommand]();
            } catch (pbrain::Error &e) {
                std::cerr << "ERROR " << e.what() << std::endl;
            }
        } else {
            std::cout << "ERROR Command not found" << std::endl;
        }
    }

    void CommandHandler::startGame(const std::string &command)
    {
        std::string size = command.substr(START_LENGHT);
        if (std::stoi(size) > BOARD_SIZE_MAX || std::stoi(size) < BOARD_SIZE_MIN) {
            throw std::invalid_argument("Invalid size");
            return;
        } else {
            std::cout << "OK" << std::endl;
        }
    }
} // namespace pbrain
