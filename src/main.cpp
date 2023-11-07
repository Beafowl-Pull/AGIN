//
// Created by beafowl on 07/11/23.
//

#include "CommandHandler.hpp"
#include <iostream>
#include <string>

int main() {
  std::string s;
  while (std::cin >> s) {
    pbrain::commandHandler::getInstance().checkCommand(s);
  }
  return 0;
}
