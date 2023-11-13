/*
** EPITECH PROJECT, 2023
** AGIN
** File description:
** Neighbor
*/

#include "Neighbor.hpp"

namespace pbrain {
    Neighbor::Neighbor(Direction dir_)
        : dir(dir)
    {}

    bool Neighbor::exist(Position pos)
    {
        for (auto pos_ : neighborMoves) {
            if (pos_ == pos) {
                return true;
            }
        }
        return false;
    }

    Neighbor &Neighbor::operator+(Neighbor &neighbors)
    {
        for (auto &pos : neighbors.neighborMoves) {
            *this + pos;
        }
        return *this;
    }

    Neighbor &Neighbor::operator+(Position pos)
    {
        neighborMoves.push_back(pos);
        return *this;
    }
} // namespace pbrain