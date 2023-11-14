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
#include "Error.hpp"
#include "Values.hpp"

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
        if (checkPosOutBoard(pos)) {
            throw Error("Pos out of range : " + std::to_string(pos._x) + " " + std::to_string(pos._y));
        }
        _board[pos._y][pos._x] = state;
        _lastMove = pos;
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
        std::vector<Position> neighborPos = {{0, 1}, {1, 0}, {-1, -1}, {1, -1}};
        int fstSide = 0;
        int sndSide = 0;

        for (auto axis : neighborPos) {
            fstSide = checkAlignement(_lastMove, axis, 0);
            axis *= -1;
            scdSide = checkAlignement(_lastMove, axis, 0);
        }
    }

    int Brain::checkAlignement(const Position &pos, const Position &axis, const std::size_t &depth)
    {
        Position posCopy = pos;
        pos += axis;
        if (checkPosOutBoard(pos) || _board[pos._y][pos._x] != _board[posCopy._y][posCopy._x]) {
            return depth;
        }
        return checkAlignement(pos, axis, depth + 1);
    }

    int brain::checkEmptySpace(const Position &pos, const Position &axis)
    {
        _lastMove += (axis * (neighbors + 1));
    }

    bool Brain::checkPosOutBoard(const Position &pos)
    {
        return (pos._x < 0 || pos._x >= _boardSize || pos._y < 0 || pos._y >= _boardSize);
    }
} // namespace pbrain
