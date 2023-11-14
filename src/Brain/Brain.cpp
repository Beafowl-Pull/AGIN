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
        : _boardSize(0),
          _lastMove({0, 0})
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
            throw Error("Pos out of range : " + std::to_string(pos.x) + " " + std::to_string(pos.y));
        }
        _board[pos.y][pos.x] = state;
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
        std::vector<std::pair<AxisDatas, AxisDatas>> axisDatas;

        for (auto axis : neighborPos) {
            std::pair<AxisDatas, AxisDatas> axisPair{getAxisDatas(axis), getAxisDatas(axis * -1)};
            axisDatas.push_back(axisPair);
            //checkWin
            //return
        }
    }

    std::size_t Brain::checkAlignement(const Position &pos, const Position &axis, const std::size_t &depth)
    {
        if (checkPosOutBoard(pos)
            || _board[_lastMove.y][_lastMove.x] != _board[pos.y][pos.x]) {
            return depth;
        }
        return checkAlignement(pos + axis, axis, depth + 1);
    }

    std::size_t Brain::checkEmptySpace(const Position &pos, const Axis &axis, const std::size_t &depth)
    {
        if (_board[pos.y][pos.x] != Cell::EMPTY) {
            return depth;
        }
        return checkEmptySpace(pos + axis, axis, depth + 1);
    }

    AxisDatas Brain::getAxisDatas(const Axis &axis)
    {
        AxisDatas datas;
        Cell lastMoveCell = board[_lastMove.y][_lastMove.x]:

        datas.axis = axis;
        datas.align = checkAlignement(_lastMove + axis, axis, 0);
        datas.emptyCells = checkEmptySpace(_lastMove + (axis * (datas.align + 1)), axis, 0);

        if (datas.emptyCells > 0) {
            auto blockCellPos = _lastMove + (axis * (datas.align + 1 + datas.emptyCells));
            datas.afterSpaceAlign = checkAlignement(blockCellPos, axis, 0);
        }
    }

    bool Brain::checkPosOutBoard(const Position &pos)
    {
        return (static_cast<int>(pos.x) < 0 || pos.x >= _boardSize || static_cast<int>(pos.y) < 0 || pos.y >= _boardSize);
    }
} // namespace pbrain
