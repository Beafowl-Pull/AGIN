/*
** EPITECH PROJECT, 2023
** AGIN
** File description:
** Brain
*/

#pragma once

#include <vector>
#include "Values.hpp"
#include <boost/container/flat_map.hpp>

struct Position
{
        int _x;
        int _y;

        Position(int x, int y)
        {
            _x = x;
            _y = y;
        }

        bool operator==(const Position &pos)
        {
            return (pos._x == _x && pos._y == _y);
        }
};

using Moves = std::vector<Position>;

enum Direction
{
    VERTICAL,
    HORIZONTAL,
    DIAG_LEFT,
    DIAG_RIGHT
};

struct Neighboor
{
        Moves neighboorMoves;
        Direction dir;
};

namespace pbrain {
    class Brain
    {
        public:
            Brain(const Brain &other) = delete;

            Brain &operator=(const Brain &other) = delete;

            Brain(Brain &&other) noexcept = delete;

            Brain &operator=(Brain &&other) noexcept = delete;

            static Brain &getInstance()
            {
                static Brain instance;
                return instance;
            }

            void setBoardSize(const std::size_t &size);

            const std::size_t &getBoardSize();

            void addMove(const Position &pos, const std::size_t &state);

            void calculate();

            void clearBoard();

        private:
            Brain();
            ~Brain() = default;

            std::size_t _boardSize;
            std::vector<Neighboor> _allies;
            std::vector<Neighboor> _enemies;
    };
} // namespace pbrain
