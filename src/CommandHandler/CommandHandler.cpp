//
// Created by beafowl on 07/11/23.
//

#include "CommandHandler.hpp"
#include <iostream>
#include <string>
#include <tuple>
#include "Brain.hpp"
#include "Error.hpp"
#include "InfoClass.hpp"
#include "Values.hpp"
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
                        {"BOARD",
                         [this] {
                             try {
                                 CommandHandler::doBoard();
                             } catch (std::invalid_argument &e) {
                                 throw pbrain::Error(e.what());
                             }
                         }},
                        {"ABOUT",
                         [this] {
                             std::cout << R"(name="Agin", version="1.0", author="Beafowl & Kitetsuk")" << std::endl;
                         }},
                        {"INFO",
                         [this] {
                             try {
                                 CommandHandler::doInfo(_commands);
                             } catch (std::invalid_argument &e) {
                                 throw pbrain::Error(e.what());
                             }
                         }},
                        {"RECTSTART",
                         [this] {
                             try {
                                 CommandHandler::doRectStart(_commands);
                             } catch (std::invalid_argument &e) {
                                 throw pbrain::Error(e.what());
                             }
                         }},
                        {"RESTART",
                         [this] {
                             try {
                                 CommandHandler::doRestart();
                             } catch (std::invalid_argument &e) {
                                 throw pbrain::Error(e.what());
                             }
                         }},
                        {"TAKEBACK",
                         [this] {
                             try {
                                 CommandHandler::doTakeBack();
                             } catch (std::invalid_argument &e) {
                                 throw pbrain::Error(e.what());
                             }
                         }},
                        {"PLAY", [this] {
                             try {
                                 CommandHandler::doTurn(_commands);
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
                std::cout << "ERROR" << std::endl;
            }
        } else {
            std::cerr << "ERROR " << command << " not found" << std::endl;
        }
    }

    void CommandHandler::startGame(const std::string &command)
    {
        if (command.size() < START_LENGHT) {
            throw std::invalid_argument("Invalid size");
        }
        std::string size = command.substr(command.find(' ') + 1);
        if (std::stoi(size) > BOARD_SIZE_MAX || std::stoi(size) < BOARD_SIZE_MIN) {
            throw std::invalid_argument("Invalid size");
        } else {
            Brain::getInstance().setBoardSize(std::stoi(size));
            _gameStarted = true;
        }
        std::cout << "OK" << std::endl;
    }

    void CommandHandler::doTurn(const std::string &command)
    {
        if (!_gameStarted) {
            throw std::invalid_argument("Game not started");
        }
        if (!_turnStarted) {
            _turnStarted = true;
        }
        if (command.find(' ') == std::string::npos || command.find(',') == std::string::npos) {
            throw std::invalid_argument("Invalid coordinates");
        }
        std::size_t x = std::stoi(command.substr(command.find(' ') + 1, command.find(',') - command.find(' ') - 1));
        std::size_t y = std::stoi(command.substr(command.find(',') + 1));
        if (x < 0 || x > BOARD_SIZE_MAX || y < 0 || y > BOARD_SIZE_MAX) {
            throw std::invalid_argument("Invalid coordinates");
        }
        Position pos(x, y);
        Brain::getInstance().addMove(pos, ENEMY);
        Brain::getInstance().calculate();
    }

    void CommandHandler::doBegin()
    {
        if (!_gameStarted || _turnStarted) {
            throw std::invalid_argument("Game not started or a turn has already been played");
        }
        std::size_t x = Brain::getInstance().getBoardSize() / 2;
        std::size_t y = Brain::getInstance().getBoardSize() / 2;
        std::cout << x << "," << y << std::endl;
        Position pos(x, y);
        Brain::getInstance().addMove(pos, Cell::ALLY);
    }

    // Ici calculate un peu spéciale (faut recalculer les coups)
    void CommandHandler::doBoard()
    {
        std::string board;
        if (!_gameStarted) {
            throw std::invalid_argument("Game not started");
        }
        Brain::getInstance().clearBoard();
        while (std::getline(std::cin, board)) {
            if (board == "DONE") {
                break;
            }
            int x = std::stoi(board.substr(board.find(' ') + 1, board.find(',') - board.find(' ') - 1));
            int y = std::stoi(board.substr(board.find(',') + 1));
            int player = std::stoi(board.substr(board.find_last_of(',') + 1));
            if (x < 0 || x > BOARD_SIZE_MAX || y < 0 || y > BOARD_SIZE_MAX || player < 0 || player > 3) {
                throw std::invalid_argument("Invalid coordinates");
            }

            Position pos(x, y);
            Brain::getInstance().addMove(pos, static_cast<Cell>(player));
        }
        Brain::getInstance().calculate();
    }

    void CommandHandler::doInfo(const std::string &command)
    {
        Info info = {};
        if (command.find(' ') == std::string::npos || command.find_last_of(' ') == std::string::npos) {
            throw std::invalid_argument("Invalid info");
        }
        std::string infoName = command.substr(command.find(' ') + 1, command.find_last_of(' ') - command.find(' ') - 1);
        std::string infoValue = command.substr(command.find_last_of(' ') + 1);

        InfoHandler::getInstance().setInfo(infoName, infoValue);
    }

    void CommandHandler::doRectStart(const std::string &command)
    {
        std::string x = command.substr(command.find(' ') + 1, command.find(',') - command.find(' ') - 1);
        std::string y = command.substr(command.find(',') + 1);

        if (std::stoi(x) > BOARD_SIZE_MAX || std::stoi(x) < BOARD_SIZE_MIN || std::stoi(y) > BOARD_SIZE_MAX
            || std::stoi(y) < BOARD_SIZE_MIN) {
            throw std::invalid_argument("Invalid size");
        } else {
            std::cout << "OK" << std::endl;
            _gameStarted = true;
        }
    }

    void CommandHandler::doRestart()
    {
        _gameStarted = false;
        _turnStarted = false;
        Brain::getInstance().clearBoard();
    }

    void CommandHandler::doTakeBack()
    {
        if (!_gameStarted) {
            throw std::invalid_argument("Game not started");
        }
        if (_boardResult.empty()) {
            throw std::invalid_argument("No moves to take back");
        }
    }

} // namespace pbrain
