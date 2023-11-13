/*
** EPITECH PROJECT, 2023
** AGIN
** File description:
** Neighbor
*/

#pragma once

#include "BrainValues.hpp"

namespace pbrain {
    struct Neighbor
    {
            Moves neighborMoves;
            Direction dir;

            Neighbor(Direction dir);

            bool exist(Position pos);
            Neighbor &operator+(Neighbor &neighbor);
            Neighbor &operator+(Position pos);
    };
} // namespace pbrain
