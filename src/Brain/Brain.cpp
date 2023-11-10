/*
** EPITECH PROJECT, 2023
** AGIN
** File description:
** Brain
*/

#include "Brain.hpp"
#include "Values.hpp"
#include <vector>
#include <iostream>

namespace pbrain {
    Brain::Brain()
        : _boardSize(0)
    {
    }

    void Brain::setBoardSize(const std::size_t &size)
    {
        if (size < BOARD_SIZE_MAX || size > BOARD_SIZE_MIN) {
            _boardSize = size;
        }
    }

    const std::size_t &Brain::getBoardSize()
    {
        return (_boardSize);
    }

    void Brain::setBoard(const Moves &moves)
    {
        _actualBoardMoves = moves;
    }

    void Brain::addMove(const MovePos &pos, const std::size_t &state)
    {
        if (_actualBoardMoves.find(pos) != _actualBoardMoves.end()) {
            return;
        }
        _actualBoardMoves[pos] = state;
    }

    void Brain::clearBoard()
    {
        _actualBoardMoves.clear();
    }

    void Brain::calculate()
    {
        std::cout << "Calculation" << std::endl;
    }
} // namespace pbrain
