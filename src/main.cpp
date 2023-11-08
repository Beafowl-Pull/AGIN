//
// Created by beafowl on 07/11/23.
//

#include <iostream>
#include <string>
#include "CommandHandler.hpp"

int main()
{
    std::string command;
    while (std::getline(std::cin, command)) {
        if (command == "END") {
            break;
        }
        pbrain::CommandHandler::getInstance().checkCommand(command);
    }
    return 0;
}
