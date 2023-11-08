//
// Created by beafowl on 07/11/23.
//

#include <iostream>
#include <string>
#include "CommandHandler.hpp"

int main()
{
    std::string s;
    while (std::getline(std::cin, s)) {
        if (s == "END") {
            break;
        }
        pbrain::commandHandler::getInstance().checkCommand(s);
    }
    return 0;
}
