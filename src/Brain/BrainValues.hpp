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
        std::size_t x;
        std::size_t y;

        Position(std::size_t x, std::size_t y)
        {
            x = x;
            y = y;
        }

        bool operator==(const Position &pos) const
        {
            return (pos.x == x && pos.y == y);
        }

        Position operator+(const Axis &axis) const
        {
            return {this->x + axis.x, this->y + axis.y};
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

};

struct Axis {
    int x;
    int y;

    Axis &operator*(int factor)
    {
        return {this->x * factor, this->y * factor};
    }
};

struct AxisDatas
{
    AxisDatas::AxisDatas() : axis({0, 0}), align(0), emptyCells(0), blockCell(EMPTY), afterSpaceAlign(0) {}
    Axis axis;
    std::size_t align;
    std::size_t emptyCells;
    Cell blockCell;
    std::size_t afterSpaceAlign;
};

using Moves = std::vector<Position>;

enum Cell
{
    EMPTY = 0,
    ALLY,
    ENEMY
};
