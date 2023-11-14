/*
** EPITECH PROJECT, 2023
** AGIN
** File description:
** Values
*/

#pragma once

#include <vector>

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

        Position &operator*=(const Position &pos)
        {
            this->_x *= pos._x;
            this->_y *= pos._y;
            return *this;
        }
};

using Moves = std::vector<Position>;

enum Cell
{
    EMPTY = 0,
    ALLY,
    ENEMY,
    RENJU
};
