/*
** EPITECH PROJECT, 2023
** AGIN
** File description:
** Brain
*/

#include "Brain.hpp"
#include "Values.hpp"

namespace pbrain {
    Brain Brain::Brain() : _actualBoardMoves(), 
    {

    }

    void Brain::setBoardSize(const std::size_t &size)
    {
        if (size > BOARD_SIZE_MAX || size < BOARD_SIZE_MIN) {
            _boardSize = size;
        }
    }
    
    void Brain::setBoard(const Moves &moves)
    {
        _actualBoardMoves = moves;
    }

    void Brain::addMove(const std::pair<std::size_t, std::size_t> &pos, const std::size_t &state)
    {
        _actualBoardMoves[pos] = state;
    }

    void Brain::calculate()
    {
        // for (auto &move : _actualBoardMoves) {
        // }
    }
}
