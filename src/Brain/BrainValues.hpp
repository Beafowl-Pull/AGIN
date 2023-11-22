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
        Axis(int x_, int y_)
            : x(x_),
              y(y_)
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
        std::size_t x;
        std::size_t y;

        Position(std::size_t x_, std::size_t y_)
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
              afterSpaceAlign(0)
        {}
        Axis axis;
        std::size_t align;
        std::size_t emptyCells;
        std::size_t afterSpaceAlign;
};

struct Line
{
        std::pair<AxisDatas, AxisDatas> line;
        std::size_t total;

        bool operator==(const Line &line) const
        {
            if (this.line.first.align != line.line.first.align || this.line.second.align != line.line.second.align
                || this.line.first.emptyCells != line.line.first.emptyCells
                || this.line.second.emptyCells != line.line.second.emptyCells
                || this.line.first.afterSpaceAlign != line.line.first.afterSpaceAlign
                || this.line.second.afterSpaceAlign != line.line.second.afterSpaceAlign || this.total != line.total) {
                return false;
            }
            return true;
        }
};

using Moves = std::vector<Position>;
