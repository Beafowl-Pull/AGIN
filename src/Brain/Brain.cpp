/*
** EPITECH PROJECT, 2023
** AGIN
** File description:
** Brain
*/

#include "Brain.hpp"
#include <iostream>
#include <vector>
#include "Values.hpp"

namespace pbrain {
    Brain::Brain()
        : _boardSize(0)
    {}

    void Brain::setBoardSize(const std::size_t &size)
    {
        if (size < BOARD_SIZE_MAX || size > BOARD_SIZE_MIN) {
            _boardSize = size;
        }
    }

    const std::size_t &Brain::getBoardSize()
    {
        return (_boardSize);
    }

    void Brain::addNeighbor(const Position &pos, std::vector<Neighbor>::iterator fstIterator,
                            std::vector<Neighbor>::iterator scdIterator, Direction dir, bool ally)
    {
        if (fstIterator != _allies.end() && scdIterator == _allies.end()) {
            *fstIterator + pos;
        } else if (fstIterator == _allies.end() && scdIterator != _allies.end()) {
            *scdIterator + pos;
        } else if (fstIterator == _allies.end() && scdIterator == _allies.end()) {
            Neighbor nei(dir);
            nei + pos;
            (ally ? _allies : _enemies).push_back(nei);
        } else {
            *fstIterator + *scdIterator;
            *fstIterator + pos;
            (ally ? _allies : _enemies).erase(scdIterator);
        }
    }

    void Brain::checkNeighbor(const Position &pos, const Position &posNeighbor1, const Position &posNeighbor2,
                              Direction dir, bool ally)
    {
        std::vector<Neighbor>::iterator fstNeighborhood = _allies.end();
        std::vector<Neighbor>::iterator scdNeighborhood = _allies.end();
        std::vector<Neighbor> &neighbors = ally ? _allies : _enemies;

        for (auto it = neighbors.begin(); it != neighbors.end(); it++) {
            if (it->dir != dir) {
                continue;
            }
            for (auto &neighPos : it->neighborMoves) {
                if (neighPos == posNeighbor1) {
                    fstNeighborhood = it;
                } else if (neighPos == posNeighbor2) {
                    scdNeighborhood = it;
                }
            }
        }
        addNeighbor(pos, fstNeighborhood, scdNeighborhood, dir, ally);
    }

    void Brain::addMove(const Position &pos, const std::size_t &state)
    {
        std::vector<std::pair<Position, Position>> neighborPos = {{{0, 1}, {0, -1}},
                                                                  {{1, 0}, {-1, 0}},
                                                                  {{-1, -1}, {1, 1}},
                                                                  {{1, -1}, {-1, 1}}};

        for (std::size_t i = 0; i < DIRECTION_MAX; i++) {
            checkNeighbor(pos, pos + neighborPos[i].first, pos + neighborPos[i].second, static_cast<Direction>(i),
                          state == ALLY);
        }
    }

    void Brain::clearBoard()
    {
        _allies.clear();
        _enemies.clear();
    }

    void Brain::calculate()
    {
        std::cout << "Calculation" << std::endl;
    }
} // namespace pbrain
