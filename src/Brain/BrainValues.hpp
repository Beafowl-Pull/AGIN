/*
** EPITECH PROJECT, 2023
** AGIN
** File description:
** Values
*/

#pragma once

#include <vector>

enum Cell
{
    EMPTY = 0,
    ALLY,
    ENEMY
};

struct Axis
{
        Axis(int x_, int y_) : x(x_), y(y_)
            {}
        int x;
        int y;

        Axis operator*(int factor) const
        {
            return {this->x * factor, this->y * factor};
        }
};

struct Position
{
        int x;
        int y;

        Position(int x_, int y_)
        {
            x = x_;
            y = y_;
        }

        bool operator==(const Position &pos) const
        {
            return (pos.x == x && pos.y == y);
        }

        Position operator+(const Axis &axis) const
        {
            return {this->x + axis.x, this->y + axis.y};
        }

        Position operator+(const Position &pos) const
        {
            return {this->x + pos.x, this->y + pos.y};
        }

        Position &operator+=(const Position &pos)
        {
            this->x += pos.x;
            this->y += pos.y;
            return *this;
        }

        Position operator-(const Position &pos) const
        {
            return {this->x - pos.x, this->y - pos.y};
        }

        Position &operator-=(const Position &pos)
        {
            this->x -= pos.x;
            this->y -= pos.y;
            return *this;
        }

        Position &operator*=(const Position &pos)
        {
            this->x *= pos.x;
            this->y *= pos.y;
            return *this;
        }

        Position &operator*(const int value)
        {
            this->x = this->x * value;
            this->y = this->y * value;
            return *this;
        }
};

struct AxisDatas
{
        AxisDatas()
            : axis({0, 0}),
              align(0),
              emptyCells(0),
              blockCell(EMPTY),
              afterSpaceAlign(0)
        {}
        Axis axis;
        std::size_t align;
        std::size_t emptyCells;
        Cell blockCell;
        std::size_t afterSpaceAlign;
};

using Moves = std::vector<Position>;
