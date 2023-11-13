/*
** EPITECH PROJECT, 2023
** AGIN
** File description:
** Brain
*/

#include "Brain.hpp"
#include <iostream>
#include <vector>
#include "Values.hpp"

namespace pbrain {
    Brain::Brain()
        : _boardSize(0)
    {}

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

    void Brain::addMove(const Position &pos, const std::size_t &state)
    {
        // if (state == ALLY) {
        //     for (auto &neighboorMoves : _allies) {
        //         // Do things to check the neighboor
        //     }

        //     return;
        // }
        // _actualBoardMoves[pos] = state;
    }

    void Brain::clearBoard()
    {
        // _actualBoardMoves.clear();
    }

    void Brain::calculate()
    {
        std::cout << "Calculation" << std::endl;
    }
} // namespace pbrain
