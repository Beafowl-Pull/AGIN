/*
** EPITECH PROJECT, 2023
** AGIN
** File description:
** Main
*/

#include "Main.hpp"
#include <bitset>
#include <ctime>
#include <iostream>
#include <vector>
#include "CommandHandler.hpp"
#include "Error.hpp"

namespace Main {
    int MainClass::operator()()
    {
        return (runApp());
    }

    enum Tristate
    {
        empty,
        ally,
        enemy
    };

    int MainClass::runApp()
    {
        std::bitset<20> bitset;
        std::vector<Tristate> tristate;
        for (int i = 0; i < 20; i++) {
            tristate[i] = empty;
        }
        auto timestamp = std::chrono::high_resolution_clock::now();
        for (auto bit : bitset) {
            if (bit == 0) {
            }
        }
        std::cout << "bitset : " << std::chrono::high_resolution_clock::now() - timestamp << std::endl;
        auto timestamp = std::chrono::high_resolution_clock::now();
        for (auto state : tristate) {
            if (state == empty) {
            }
        }
        std::cout << "tristate : " << std::chrono::high_resolution_clock::now() - timestamp << std::endl;
        return 0;
        std::string command;
        while (std::getline(std::cin, command)) {
            if (command == "END") {
                return (EXIT_SUCCESS);
            }
            try {
                pbrain::CommandHandler::getInstance().checkCommand(command);
            } catch (pbrain::Error &e) {
                std::cerr << e.what() << std::endl;
            }
        }
        return (EXIT_SUCCESS);
    }
} // namespace Main
