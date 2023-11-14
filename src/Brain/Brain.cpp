/*
** EPITECH PROJECT, 2023
** AGIN
** File description:
** Brain
*/

#include "Brain.hpp"
#include <iostream>
#include <string>
#include <vector>
#include "BrainValues.hpp"
#include "Values.hpp"
#include "Error.hpp"

namespace pbrain {
    Brain::Brain()
        : _boardSize(0)
    {}

    void Brain::setBoardSize(const std::size_t &size)
    {
        _boardSize = size < BOARD_SIZE_MAX || size > BOARD_SIZE_MIN ? BOARD_SIZE_MIN : size;
        for (std::size_t i = 0; i < _boardSize; i++) {
            for (std::size_t j = 0; j < _boardSize; j++) {
                _board[i][j] = Cell::EMPTY;
            }
        }
    }

    const std::size_t &Brain::getBoardSize()
    {
        return (_boardSize);
    }

    void Brain::addMove(const Position &pos, const Cell &state)
    {
        if (pos._x < 0 || pos._x >= _boardSize || pos._y < 0 || pos._y >= _boardSize) {
            throw Error("Pos out of range : " + std::to_string(pos._x) + " " + std::to_string(pos._y));
        }
        _board[pos._y][pos._x] = state;
    }

    void Brain::clearBoard()
    {
        for (auto &row : _board) {
            for (auto &cell : row) {
                cell = Cell::EMPTY;
            }
        }
    }

    void Brain::calculate()
    {
        std::cout << "Calculation" << std::endl;
    }
} // namespace pbrain

// std::vector<std::pair<Position, Position>> neighborPos = {{{0, 1}, {0, -1}},
//                                                                   {{1, 0}, {-1, 0}},
//                                                                   {{-1, -1}, {1, 1}},
//                                                                   {{1, -1}, {-1, 1}}};