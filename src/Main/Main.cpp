/*
** EPITECH PROJECT, 2023
** AGIN
** File description:
** Main
*/

#include "Main.hpp"
#include "CommandHandler.hpp"
#include "Error.hpp"

    namespace Main
{
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
