/*
** EPITECH PROJECT, 2023
** AGIN
** File description:
** Brain
*/

#include "Brain.hpp"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>
#include <vector>
#include "BrainValues.hpp"
#include "Error.hpp"
#include "Values.hpp"

namespace pbrain {
    Brain::Brain()
        : _boardSize(0),
          _strongestLinePos({0, 0}),
          _lastMoveAlly({0, 0}),
          _lastMoveEnemy({0, 0}),
          _empty(true)
    {}

    static void printBoard(const std::vector<std::vector<Cell>> &board)
    {
        for (auto &it : board) {
            for (auto &it2 : it) {
                // std::cerr << it2;
            }
            // std::cerr << std::endl;
        }
    }

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
        if (_empty) {
            _empty = false;
        }
        if (checkPosOutBoard(pos)) {
            throw Error("Pos out of range : " + std::to_string(pos.x) + " " + std::to_string(pos.y));
        }
        _board[pos.y][pos.x] = state;
        if (state == Cell::ALLY) {
            _lastMoveAlly = pos;
        } else if (state == Cell::ENEMY) {
            _lastMoveEnemy = pos;
        }
    }

    void Brain::clearBoard()
    {
        for (auto &row : _board) {
            for (auto &cell : row) {
                cell = Cell::EMPTY;
            }
        }
    }

    Position Brain::getRandomMove()
    {
        Position pos(rand() % _boardSize, rand() % _boardSize);

        srand(time(NULL));
        for (; _board[pos.y][pos.x] != Cell::EMPTY; pos.x = rand() % _boardSize, pos.y = rand() % _boardSize)
            ;
        return pos;
    }

    void Brain::calculate()
    {
        if (_empty) {
            std::size_t x = _boardSize / 2;
            Position pos = {x, x};
            if (_lastMoveEnemy == pos) {
                pos += {0, 1};
            }
            addMove(pos, Cell::ALLY);
            std::cout << pos.x << "," << pos.y << std::endl;
            return;
        }
        std::optional<std::vector<Line>> allyLines = getLines(_lastMoveAlly);
        if (!allyLines.has_value()) {
            return;
        }
        std::optional<std::vector<Line>> enemyLines = getLines(_lastMoveEnemy);
        if (!enemyLines.has_value()) {
            return;
        }
        if (checkFork(allyLines.value(), _lastMoveAlly) || checkFork(enemyLines.value(), _lastMoveEnemy)) {
            return;
        }
        calculateNextMove(allyLines.value());
    }

    std::size_t Brain::checkAlignement(const Position &pos, const Axis &axis, const std::size_t &depth,
                                       const Position &posToCheck)
    {
        if (checkPosOutBoard(pos) || _board[posToCheck.y][posToCheck.x] != _board[pos.y][pos.x]) {
            return depth;
        }
        return checkAlignement(pos + axis, axis, depth + 1, posToCheck);
    }

    std::size_t Brain::checkEmptySpace(const Position &pos, const Axis &axis, const std::size_t &depth)
    {
        if (depth == 2 || checkPosOutBoard(pos) || _board[pos.y][pos.x] != Cell::EMPTY) {
            return depth;
        }
        return checkEmptySpace(pos + axis, axis, depth + 1);
    }

    AxisDatas Brain::getAxisDatas(const Axis &axis, const Position &pos)
    {
        AxisDatas datas;

        datas.axis = axis;
        datas.align = checkAlignement(pos + axis, axis, 0, pos);
        datas.emptyCells = checkEmptySpace(pos + (axis * (datas.align + 1)), axis, 0);
        if (datas.emptyCells > 0) {
            auto blockCellPos = pos + (axis * (datas.align + 1 + datas.emptyCells));
            datas.afterSpaceAlign = checkAlignement(blockCellPos, axis, 0, pos);
            if (datas.afterSpaceAlign == 0) {
                return datas;
            }
            datas.afterSpaceEmptyCells = checkEmptySpace(blockCellPos + (axis * (datas.afterSpaceAlign)), axis, 0);
        }
        return datas;
    }

    std::optional<Position> Brain::checkWin(AxisDatas fstData, AxisDatas sndData, std::size_t total,
                                            const Position &pos)
    {
        if (total == 4 && fstData.emptyCells > 0) {
            return pos + (fstData.axis * (1 + fstData.align));
        } else if (fstData.emptyCells == 1) {
            if (total + fstData.afterSpaceAlign > 3) {
                return pos + (fstData.axis * (1 + fstData.align));
            }
        }
        return std::nullopt;
    }

    std::optional<std::vector<Line>> Brain::getLines(const Position &pos, bool printable)
    {
        std::vector<Axis> neighborAxis = {{0, 1}, {1, 0}, {-1, -1}, {1, -1}};
        std::vector<Line> lines;

        for (auto axis : neighborAxis) {
            std::pair<AxisDatas, AxisDatas> axisPair {getAxisDatas(axis, pos), getAxisDatas(axis * -1, pos)};
            auto total = axisPair.first.align + axisPair.second.align + 1;
            lines.push_back({axisPair, total});

            auto res = checkWin(axisPair.first, axisPair.second, total, pos);
            if (!res.has_value()) {
                res = checkWin(axisPair.second, axisPair.first, total, pos);
            }
            if (res.has_value(), && printable) {
                addMove(res.value(), Cell::ALLY);
                std::cout << res.value().x << "," << res.value().y << std::endl;
                return std::nullopt;
            }
        }
        return lines;
    }

    bool Brain::checkInlineFork(AxisDatas fst, AxisDatas scd, int total, const Position &pos)
    {
        if ((total + fst.afterSpaceAlign == 3 && fst.emptyCells == 1 && scd.emptyCells > 0 && fst.afterSpaceEmptyCells > 0)
           || (total == 3 && fst.emptyCells > 1 && scd.emptyCells > 0)) {
            auto posToPlay = pos + (fst.axis * (1 + fst.align));
            addMove(posToPlay, Cell::ALLY);
            std::cout << posToPlay.x << "," << posToPlay.y << std::endl;
            return true;
        }
        return false;
    }

    bool Brain::checkForkDanger(AxisDatas fst, AxisDatas scd, int total)
    {
        if (total == 3 && fst.emptyCells > 1) {
            return true;
        } else if (total + fst.afterSpaceAlign == 3 && fst.emptyCells == 1 && (fst.afterSpaceEmptyCells > 0 || scd.emptyCells > 0)) {
            return true;
        } else if (total == 2 && fst.emptyCells > 2 && scd.emptyCells > 0) {
            return true;
        } else if (total + fst.afterSpaceAlign == 2 && fst.emptyCells == 1 && fst.afterSpaceEmptyCells > 0 && scd.emptyCells > 0) {
            if (fst.afterSpaceEmptyCells > 1 || scd.emptyCells > 1) {
                return true;
            }
        }
        return false;
    }

    bool Brain::checkCrossFork(AxisDatas fst, AxisDatas scd, int total, const Position &pos)
    {
        if (checkForkDanger(fst, scd, total)) {
            auto checkingPos = pos + (fst.axis * (1 + fst.align));
            _board[checkingPos.y][checkingPos.x] = _board[pos.y][pos.x];
            auto lines = getLines(checkingPos, false);
            _board[checkingPos.y][checkingPos.x] = Cell::EMPTY;
            for (auto line : lines) {
                if (line.first.axis == fst.axis || line.first.axis == scd.axis) {
                    continue;
                }
                line.total -= 1;
                if (checkForkDanger(line.line.first, line.line.second, line.total) ||
                    checkForkDanger(line.line.second, line.line.first, line.total)) {
                    addMove(checkingPos, Cell::ALLY);
                    std::cout << checkingPos.x << "," << checkingPos.y << std::endl;
                    return true;
                }
            }
        }
    }

    bool Brain::checkFork(std::vector<Line> lines, const Position &pos)
    {
        for (auto line : lines) {
            if (checkInlineFork(line.line.first, line.line.second, line.total, pos)
                || checkInlineFork(line.line.second, line.line.first, line.total, pos)) {
                return true;
            } else if (checkCrossFork(line.line.first, line.line.second, line.total, pos)
                       || checkCrossFork(line.line.second, line.line.first, line.total, pos)) {
                return true;
            }
        }
        return false;
    }

    Line &Brain::compareLines(Line &fstLine, Line &sndLine)
    {
        if (sndLine.line.first.emptyCells == 0 && sndLine.line.second.emptyCells == 0) {
            return fstLine;
        }
        auto sndLineFstAdd = sndLine.total + sndLine.line.first.afterSpaceAlign;
        if (sndLineFstAdd > fstLine.total + fstLine.line.first.afterSpaceAlign
            && sndLineFstAdd > fstLine.total + fstLine.line.second.afterSpaceAlign) {
            return sndLine;
        } else {
            return fstLine;
        }
    }

    std::optional<Position> Brain::checkMove(AxisDatas first, AxisDatas second, int total)
    {
        if (total + first.afterSpaceAlign == 3 && first.emptyCells > 0) {
            return _lastMoveAlly + (first.axis * (first.align + 1));
        } else if (total == 1 && first.afterSpaceAlign == 1) {
            Position afterData =
                _lastMoveAlly + (first.axis * (first.align + first.afterSpaceAlign + first.emptyCells + 1));
            if (checkPosOutBoard(afterData)) {
                return (std::nullopt);
            }
            Cell cellAfterData = _board[afterData.y][afterData.x];
            afterData + first.axis;
            Cell scdCellAfterData = _board[afterData.y][afterData.x];
            if (second.emptyCells > 0 && cellAfterData == Cell::EMPTY && scdCellAfterData == Cell::EMPTY
                || second.emptyCells > 1 && cellAfterData == Cell::EMPTY) {
                return _lastMoveAlly + (first.axis * (first.align + 1));
            }
        } else if (total == 1 && first.emptyCells > 3 && second.emptyCells > 0
                   || total == 1 && first.emptyCells > 2 && second.emptyCells > 1) {
            return _lastMoveAlly + (first.axis * (first.align + 2));
        } else if (first.emptyCells >= 1) {
            return _lastMoveAlly + (first.axis * (first.align + 1));
        }
        return std::nullopt;
    }

    std::optional<Axis> Brain::getAlignAxis()
    {
        Axis axis(0, 0);

        if (!checkPosOutBoard(_lastMoveAlly + _strongestLine.line.first.axis)
            && _board[_lastMoveAlly.y + _strongestLine.line.first.axis.y]
                     [_lastMoveAlly.x + _strongestLine.line.first.axis.x]
                   == Cell::ALLY) {
            axis = _strongestLine.line.first.axis;
            return axis;
        }
        if (!checkPosOutBoard(_lastMoveAlly + _strongestLine.line.second.axis)
            && _board[_lastMoveAlly.y + _strongestLine.line.second.axis.y]
                     [_lastMoveAlly.x + _strongestLine.line.second.axis.x]
                   == Cell::ALLY) {
            axis = _strongestLine.line.second.axis;
            return axis;
        }
        return std::nullopt;
    }

    std::optional<Position> Brain::checkSides()
    {
        Position pos(_strongestLinePos);
        std::optional<Axis> axis = getAlignAxis();

        if (axis == std::nullopt) {
            return std::nullopt;
        }
        Axis side(axis.value().y, axis.value().x * -1);
        std::pair<Axis, Axis> sides(side, side * -1);
        for (; _board[pos.y][pos.x] != Cell::ALLY; pos = pos + axis.value()) {
            auto tmpPos = pos + sides.first;
            if (_board[tmpPos.y][tmpPos.x] == Cell::EMPTY) {
                return tmpPos;
            }
            tmpPos = tmpPos + sides.second;
            if (_board[tmpPos.y][tmpPos.x] == Cell::EMPTY) {
                return tmpPos;
            }
        }
    }

    void Brain::calculateNextMove(std::vector<Line> lines)
    {
        std::optional<Position> res;
        auto &max = lines.front();
        for (auto &line : lines) {
            max = compareLines(max, line);
        }
        _strongestLine = compareLines(_strongestLine, max);
        if (_strongestLine == max) {
            _strongestLinePos = _lastMoveAlly;
        }
        if (_strongestLine.line.first.emptyCells == 0 && _strongestLine.line.second.emptyCells == 0) {
            res = checkSides();
        } else {
            res = checkMove(max.line.first, max.line.second, max.total);
            if (!res.has_value()) {
                res = checkMove(max.line.second, max.line.first, max.total);
                if (!res.has_value()) {
                    std::cerr << "WRONG NULLOPT" << std::endl;
                }
            }
        }
        if (res == std::nullopt) {
            res = getRandomMove();
        }
        addMove(res.value(), Cell::ALLY);
        std::cout << res.value().x << "," << res.value().y << std::endl;
    }

    bool Brain::checkPosOutBoard(const Position &pos)
    {
        return (static_cast<int>(pos.x) < 0 || pos.x >= _boardSize || static_cast<int>(pos.y) < 0
                || pos.y >= _boardSize);
    }
} // namespace pbrain
