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
          _lastMoveAlly({0, 0}),
          _lastMoveEnemy({0, 0}),
          _isAlly(false)
    {}
    static void printBoard(const std::vector<std::vector<Cell>> &board)
    {
        for (auto &it : board) {
            for (auto &it2 : it) {
                // std::cout << it2;
            }
            // std::cout << std::endl;
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
        // addMove(Position(0, 0), Cell::ALLY);
        // addMove(Position(1, 0), Cell::ALLY);
        // addMove(Position(3, 0), Cell::ALLY);
        // addMove(Position(4, 0), Cell::ALLY);

        // addMove(Position(0, 1), Cell::ENEMY);
        // addMove(Position(1, 1), Cell::ENEMY);
        // addMove(Position(3, 1), Cell::ENEMY);
        // addMove(Position(4, 1), Cell::ENEMY);
        printBoard(_board);
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
        if (state == Cell::ALLY) {
            _lastMoveAlly = pos;
        } else if (state == Cell::ENEMY) {
            _lastMoveEnemy = pos;
        }
    }

    bool Brain::isAlly()
    {
        return (_isAlly);
    }

    void Brain::setAlly(bool value)
    {
        _isAlly = value;
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
        Position pos(0, 0);

        srand(time(NULL));
        for (; _board[pos.y][pos.x] != Cell::EMPTY; pos.x = rand() % _boardSize, pos.y = rand() % _boardSize)
            ;
        addMove(pos, Cell::ALLY);
        return pos;
    }

    // Ici j ai changer en optionnel pour que ce soit le command handler qui print si notre IA a renvoyé un coup
    // Comme ca on calcule d'abord le lastMove allié puis on calcule le move enemy
    // Si on renvoit un coup pour allié pcq on est sur de gagner on print direct sans calculer pour l'enemy (pcq on a
    // gagné :/) Si le calculate(true) n'a rien revoyé alors on le lance avec false pour calculer avec l'enemy Je t ai
    // écrit ca pcq j ai fait des modifs dans le command handler
    std::optional<Position> Brain::calculate(bool ally)
    {
        std::vector<Axis> neighborAxis = {{0, 1}, {1, 0}, {-1, -1}, {1, -1}};
        std::vector<Line> lines;

        setAlly(ally);
        for (auto pos : neighborAxis) {
            Axis axis(pos.x, pos.y);
            std::pair<AxisDatas, AxisDatas> axisPair {
                getAxisDatas(axis, _isAlly ? _lastMoveAlly : _lastMoveEnemy),
                getAxisDatas(axis * -1, _isAlly ? _lastMoveAlly : _lastMoveEnemy)};

            auto total = axisPair.first.align + axisPair.second.align + 1;
            lines.push_back({axisPair, total});
            auto res = checkWin(axisPair.first, axisPair.second, total, _isAlly ? _lastMoveAlly : _lastMoveEnemy);
            if (!res.has_value()) {
                res = checkWin(axisPair.second, axisPair.first, total, _isAlly ? _lastMoveAlly : _lastMoveEnemy);
            }
            if (res.has_value()) {
                addMove(res.value(), Cell::ALLY);
                printBoard(_board);
                return res;
            }
        }
        printBoard(_board);
        return std::nullopt;
        // calculateNextMove(lines);
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

    Position Brain::calculateNextMove(std::vector<Line> lines)
    {
        auto &max = lines.front();
        for (auto &line : lines) {
            if (line.total > max.total) {
                max = line;
            }
        }
        return {0, 0};
    }

    bool Brain::checkPosOutBoard(const Position &pos)
    {
        return (static_cast<int>(pos.x) < 0 || pos.x >= _boardSize || static_cast<int>(pos.y) < 0
                || pos.y >= _boardSize);
    }
} // namespace pbrain
