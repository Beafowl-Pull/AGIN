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

            void calculate();

            void clearBoard();

            Position getRandomMove();

        private:
            std::size_t checkAlignement(const Position &pos, const Axis &axis, const std::size_t &depth,
                                        const Position &posToCheck);

            std::size_t checkEmptySpace(const Position &pos, const Axis &axis, const std::size_t &depth);

            AxisDatas getAxisDatas(const Axis &axis, const Position &pos);

            std::optional<Position> checkWin(AxisDatas fstData, AxisDatas sndData, std::size_t total,
                                             const Position &pos);

            std::optional<std::vector<Line>> getLines(const Position &pos);

            bool checkForkInAxis(AxisDatas fst, AxisDatas scd, int total, const Position &pos);

            bool checkSplittedForkInAxis(AxisDatas fst, AxisDatas scd, int total, const Position &pos);

            bool checkFork(std::vector<Line> lines, const Position &pos);

            Line &compareLines(Line &fstLine, Line &sndLine);

            std::optional<Position> checkMove(AxisDatas first, AxisDatas second, int total);

            void calculateNextMove(std::vector<Line>);

            bool checkPosOutBoard(const Position &pos);

            Brain();
            ~Brain() = default;

            std::size_t _boardSize;
            Position _lastMoveAlly;
            Position _lastMoveEnemy;
            std::vector<std::vector<Cell>> _board;
    };
} // namespace pbrain
