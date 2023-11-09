/*
** EPITECH PROJECT, 2023
** AGIN
** File description:
** Brain
*/

#pragma once

#include "Values.hpp"
#include <unordered_map>

struct pair_hash
{
        template<class T1, class T2>
        std::size_t operator()(const std::pair<T1, T2> &pair) const
        {
            auto hash1 = std::hash<T1> {}(pair.first);
            auto hash2 = std::hash<T2> {}(pair.second);
            return hash1 ^ hash2; // XOR or other combination
        }
};

using Moves = std::unordered_map<std::pair<int, int>, int, pair_hash>;

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
} // namespace pbrain