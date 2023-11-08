//
// Created by beafowl on 07/11/23.
//

#include <functional>
#include <iostream>
#include "CommandHandler.hpp"
#include "Error.hpp"
#include "Values.hpp"
#include <type_traits>
#include <unordered_map>

namespace pbrain {
    CommandHandler::CommandHandler()
        : _commands(" ")
    {
        _commandsMap = {{"START",
                         [this] {
                             try {
                                 CommandHandler::startGame(_commands);
                             } catch (std::invalid_argument &e) {
                                 throw pbrain::Error(e.what());
                             }
                         }},
                        {"TURN",
                         [this] {
                             try {
                                 CommandHandler::doTurn(_commands);
                             } catch (std::invalid_argument &e) {
                                 throw pbrain::Error(e.what());
                             }
                         }},
                        {"BEGIN", [this] {
                             try {
                                 CommandHandler::doBegin();
                             } catch (std::invalid_argument &e) {
                                 throw pbrain::Error(e.what());
                             }
                         }}};
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
            std::cerr << "ERROR Command not found" << std::endl;
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
            _gameStarted = true;
        }
    }

    void CommandHandler::doTurn(const std::string &command)
    {
        if (!_gameStarted) {
            throw std::invalid_argument("Game not started");
            return;
        }
        if (!_turnStarted) {
            _turnStarted = true;
        }
        std::string x =
            command.substr(command.find(' ') + 1, command.find(' ', command.find(' ') + 1) - command.find(' ') - 1);
        std::string y = command.substr(command.find(' ', command.find(' ') + 1) + 1);
        std::cout << x << " " << y << std::endl;
    }

    void CommandHandler::doBegin() const
    {
        if (!_gameStarted || _turnStarted) {
            throw std::invalid_argument("Game not started or a turn has already been played");
            return;
        }
        std::cout << "BEGIN" << std::endl;
    }
} // namespace pbrain
