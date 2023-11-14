/*
** EPITECH PROJECT, 2023
** AGIN
** File description:
** Brain
*/

#pragma once

#include "BrainValues.hpp"
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

            void addMove(const Position &pos, const Cell &state);

            void calculate();

            void clearBoard();

        private:
            std::size_t checkAlignement(const Position &pos, const Axis &axis, const std::size_t &depth);

            std::size_t checkEmptySpace(const Position &pos, const Axis &axis, const std::size_t &depth);

            AxisDatas getAxisDatas(const Position &axis);

            bool checkPosOutBoard(const Position &pos);

            Brain();
            ~Brain() = default;

            std::size_t _boardSize;
            Position _lastMove;
            std::vector<std::vector<Cell>> _board;
    };
} // namespace pbrain
