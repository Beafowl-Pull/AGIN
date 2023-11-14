/*
** EPITECH PROJECT, 2023
** AGIN
** File description:
** Values
*/

#pragma once

#include <vector>

#define ALLY  1
#define ENEMY 2

struct Position
{
        int _x;
        int _y;

        Position(int x, int y)
        {
            _x = x;
            _y = y;
        }

        bool operator==(const Position &pos) const
        {
            return (pos._x == _x && pos._y == _y);
        }

        Position operator+(const Position &pos) const
        {
            return {this->_x + pos._x, this->_y + pos._y};
        }

        Position &operator+=(const Position &pos)
        {
            this->_x += pos._x;
            this->_y += pos._y;
            return *this;
        }

        Position operator-(const Position &pos) const
        {
            return {this->_x - pos._x, this->_y - pos._y};
        }

        Position &operator-=(const Position &pos)
        {
            this->_x -= pos._x;
            this->_y -= pos._y;
            return *this;
        }
};

using Moves = std::vector<Position>;

enum Direction
{
    VERTICAL = 0,
    HORIZONTAL,
    DIAG_LEFT,
    DIAG_RIGHT,
    DIRECTION_MAX
};