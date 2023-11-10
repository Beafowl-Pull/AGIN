/*
** EPITECH PROJECT, 2023
** AGIN
** File description:
** Brain
*/

#pragma once

#include "Values.hpp"
#include <boost/container/flat_map.hpp>


using MovePos = std::pair<std::size_t, std::size_t>;

using Moves = boost::container::flat_map<MovePos, std::size_t>;

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

            void setBoard(const Moves &moves);

            void addMove(const MovePos &pos, const std::size_t &state);

            void calculate();

            void clearBoard();

            void initBoard();

        private:
            Brain();
            ~Brain() = default;

            std::size_t _boardSize;
            Moves _actualBoardMoves;
    };
} // namespace pbrain