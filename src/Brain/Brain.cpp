/*
** EPITECH PROJECT, 2023
** AGIN
** File description:
** Brain
*/

#include <iostream>
#include <string>
#include <vector>
#include "Brain.hpp"
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
        _boardSize = size < BOARD_SIZE_MAX || size > BOARD_SIZE_MIN ? size : BOARD_SIZE_MIN;
        for (std::size_t i = 0; i < _boardSize; i++) {
            _board.emplace_back();
            for (std::size_t j = 0; j < _boardSize; j++) {
                _board[i].push_back(Cell::EMPTY);
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
        std::vector<Axis> neighborAxis = {{0, 1}, {1, 0}, {-1, -1}, {1, -1}};
        std::vector<Line> lines;

        for (auto pos : neighborAxis) {
            Axis axis(pos.x, pos.y);
            std::pair<AxisDatas, AxisDatas> axisPair {getAxisDatas(axis), getAxisDatas(axis * -1)};
            auto total = axisPair.first.align + axisPair.second.align + 1;
            lines.push_back({axisPair, total});
            auto res = checkWin(axisPair.first, axisPair.second, total);
            if (!res.has_value()) {
                res = checkWin(axisPair.second, axisPair.first, total);
            }
            if (res.has_value()) {
                //cout
                return;
            }
        }
        calculateNextMove(lines);
    }

    std::size_t Brain::checkAlignement(const Position &pos, const Axis &axis, const std::size_t &depth)
    {
        if (checkPosOutBoard(pos) || _board[_lastMove.y][_lastMove.x] != _board[pos.y][pos.x]) {
            return depth;
        }
        return checkAlignement(pos + axis, axis, depth + 1);
    }

    std::size_t Brain::checkEmptySpace(const Position &pos, const Axis &axis, const std::size_t &depth)
    {
        if (checkPosOutBoard(pos) || _board[pos.y][pos.x] != Cell::EMPTY) {
            return depth;
        }
        return checkEmptySpace(pos + axis, axis, depth + 1);
    }

    AxisDatas Brain::getAxisDatas(const Axis &axis)
    {
        AxisDatas datas;
        Cell lastMoveCell = _board[_lastMove.y][_lastMove.x];

        datas.axis = axis;
        datas.align = checkAlignement(_lastMove + axis, axis, 0);
        datas.emptyCells = checkEmptySpace(_lastMove + (axis * (datas.align + 1)), axis, 0);
        if (datas.emptyCells > 0) {
            auto blockCellPos = _lastMove + (axis * (datas.align + 1 + datas.emptyCells));
            datas.afterSpaceAlign = checkAlignement(blockCellPos, axis, 0);
        }
        return datas;
    }

    std::optional<Position> Brain::checkWin(AxisDatas fstData, AxisDatas sndData, std::size_t total)
    {
        //prendre en compte si c enemy ou ally
        if (total == 4 && fstData.emptyCells > 0) {
            return _lastMove + (fstData.axis * (1 + fstData.align));
        } else if (fstData.emptyCells == 1) {
            auto minAfterSpace = 0;
            for (auto needTotal = 3; needTotal == 0; needTotal--) {
                if (total >= needTotal && fstData.afterSpaceAlign > minAfterSpace) {
                    return _lastMove + (fstData.axis * (1 + fstData.align));
                }
                minAfterSpace++;
            }
        }
        return  std::nullopt;
    }

    Position Brain::calculateNextMove(std::vector<Line> lines)
    {
        auto &max = lines.front();
        for (auto &line : lines) {
            if (line.total > max.total) {
                max = line;
            }
        }
        //
    }

    bool Brain::checkPosOutBoard(const Position &pos)
    {
        return (static_cast<int>(pos.x) < 0 || pos.x >= _boardSize || static_cast<int>(pos.y) < 0
                || pos.y >= _boardSize);
    }
} // namespace pbrain
