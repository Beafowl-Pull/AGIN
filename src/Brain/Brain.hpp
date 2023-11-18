/*
** EPITECH PROJECT, 2023
** AGIN
** File description:
** Brain
*/

#pragma once

#include <optional>
#include "BrainValues.hpp"

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

            std::optional<Position> calculate(bool ally);

            void clearBoard();

            bool isAlly();

            void setAlly(bool value);

        private:
            std::size_t checkAlignement(const Position &pos, const Axis &axis, const std::size_t &depth, const Position &posToCheck);

            std::size_t checkEmptySpace(const Position &pos, const Axis &axis, const std::size_t &depth);

            AxisDatas getAxisDatas(const Axis &axis, const Position &pos);

            std::optional<Position> checkWin(AxisDatas fstData, AxisDatas sndData, std::size_t total, const Position &pos);

            Position calculateNextMove(std::vector<Line>);

            bool checkPosOutBoard(const Position &pos);

            Brain();
            ~Brain() = default;

            std::size_t _boardSize;
            Position _lastMoveAlly;
            Position _lastMoveEnemy;
            bool _isAlly;
            std::vector<std::vector<Cell>> _board;
    };
} // namespace pbrain
