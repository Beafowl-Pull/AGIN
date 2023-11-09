/*
** EPITECH PROJECT, 2023
** AGIN
** File description:
** Values
*/

#ifndef VALUES_HPP_
#define VALUES_HPP_

#include <utility>
#include <unordered_map>

using Moves = std::unordered_map<std::pair<std::size_t, std::size_t>, std::size_t>;

constexpr int BOARD_SIZE_MAX = 100;
constexpr int BOARD_SIZE_MIN = 5;
constexpr int START_LENGHT = 6;

#endif /* !VALUES_HPP_ */
