/*
** EPITECH PROJECT, 2023
** AGIN
** File description:
** Brain
*/

#pragma once

#include "Values.hpp"

namespace pbrain {
    class Brain {
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

            void setBoard(const Moves &moves);

            void addMove(const std::pair<std::size_t, std::size_t> &pos, const std::size_t &state);

            void calculate();

        protected:
        private:

            Brain();
            ~Brain() = default;

            std::size_t _boardSize;
            Moves _actualBoardMoves;
            Moves _possibleMoves;
    };
}