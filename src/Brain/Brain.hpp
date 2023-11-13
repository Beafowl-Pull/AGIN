/*
** EPITECH PROJECT, 2023
** AGIN
** File description:
** Brain
*/

#pragma once

#include "BrainValues.hpp"
#include "Neighbor.hpp"
#include <boost/container/flat_map.hpp>

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
            void checkNeighbor(const Position &pos, const Position &posNeighbor1, const Position &posNeighbor2,
                               Direction dir, bool ally = false);

            void addNeighbor(const Position &pos, std::vector<Neighbor>::iterator fstIterator,
                             std::vector<Neighbor>::iterator scdIterator, Direction dir, bool ally = false);

            Brain();
            ~Brain() = default;

            std::size_t _boardSize;
            std::vector<Neighbor> _allies;
            std::vector<Neighbor> _enemies;
    };
} // namespace pbrain
