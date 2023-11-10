//
// Created by beafowl on 07/11/23.
//

#include "CommandHandler.hpp"
#include <iostream>
#include <string>
#include "Error.hpp"
#include "Brain.hpp"
#include <type_traits>

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
                        {"BEGIN",
                         [this] {
                             try {
                                 CommandHandler::doBegin();
                             } catch (std::invalid_argument &e) {
                                 throw pbrain::Error(e.what());
                             }
                         }},
                        {"BOARD", [this] {
                             try {
                                 CommandHandler::doBoard();
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
        if (command.size() < START_LENGHT) {
            throw std::invalid_argument("Invalid size");
        }
        std::string size = command.substr(START_LENGHT);
        if (std::stoi(size) > BOARD_SIZE_MAX || std::stoi(size) < BOARD_SIZE_MIN) {
            throw std::invalid_argument("Invalid size");
        } else {
            Brain::getInstance().setBoardSize(std::stoi(size));
            _gameStarted = true;
        }
    }

    void CommandHandler::doTurn(const std::string &command)
    {
        if (!_gameStarted) {
            throw std::invalid_argument("Game not started");
        }
        if (!_turnStarted) {
            _turnStarted = true;
        }
        if (command.find(' ') == std::string::npos || command.find(",") == std::string::npos) {
            throw std::invalid_argument("Invalid coordinates");
        }
        std::size_t x = std::stoi(command.substr(command.find(' ') + 1, command.find(',') - command.find(' ') - 1));
        std::size_t y = std::stoi(command.substr(command.find(',') + 1));
        if (x < 0 || x > BOARD_SIZE_MAX || y < 0 || y > BOARD_SIZE_MAX) {
            throw std::invalid_argument("Invalid coordinates");
        }
        Brain::getInstance().addMove(std::make_pair(x, y), 2);
        Brain::getInstance().calculate();
    }

    void CommandHandler::doBegin() const
    {
        if (!_gameStarted || _turnStarted) {
            throw std::invalid_argument("Game not started or a turn has already been played");
        }
        std::size_t x = Brain::getInstance().getBoardSize() / 2;
        std::size_t y = Brain::getInstance().getBoardSize() / 2;
        std::cout << x << ", " << y << std::endl;
        Brain::getInstance().addMove(std::make_pair(x, y), 1);
    }

    void CommandHandler::doBoard()
    {
        std::string board;
        if (!_gameStarted) {
            throw std::invalid_argument("Game not started or a turn has not been played");
        }
        Brain::getInstance().clearBoard();
        while (std::getline(std::cin, board)) {
            if (board == "DONE") {
                break;
            }
            std::size_t x = std::stoi(board.substr(board.find(' ') + 1, board.find(',') - board.find(' ') - 1));
            std::size_t y = std::stoi(board.substr(board.find(',') + 1));
            std::size_t player = std::stoi(board.substr(board.find_last_of(',') + 1));
            if (x < 0 || x > BOARD_SIZE_MAX || y < 0 || y > BOARD_SIZE_MAX || player <= 0 || player > 3) {
                throw std::invalid_argument("Invalid coordinates or player number.");
            }
            Brain::getInstance().addMove(std::make_pair(x, y), player);
        }
        Brain::getInstance().calculate();
    }
} // namespace pbrain
