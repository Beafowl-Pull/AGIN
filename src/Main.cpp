/*
** EPITECH PROJECT, 2023
** AGIN
** File description:
** Main
*/

#include "Main.hpp"
#include "CommandHandler.hpp"
#include "Error.hpp"

namespace Main {
    int Main::operator()()
    {
        return (runApp());
    }

    int Main::runApp()
    {
        std::string command;
        while (std::getline(std::cin, command)) {
            if (command == "END") {
                return (EXIT_SUCCESS);
            }
            try {
                pbrain::CommandHandler::getInstance().checkCommand(command);
            } catch (pbrain::Error &e) {
                return (EXIT_FAILURE);
            }
        }
        return (EXIT_SUCCESS);
    }
}