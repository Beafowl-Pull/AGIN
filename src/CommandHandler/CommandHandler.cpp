//
// Created by beafowl on 07/11/23.
//

#include "CommandHandler.hpp"
#include <functional>
#include <iostream>
#include <unordered_map>

namespace pbrain {
void commandHandler::checkCommand(const std::string &command) {
  std::unordered_map<std::string, std::function<void()>> commands = {
      {"START", []() { std::cout << "OK" << std::endl; }},
      {"TURN", []() { std::cout << "OK" << std::endl; }},
      {"BEGIN", []() { std::cout << "OK" << std::endl; }},
      {"BOARD", []() { std::cout << "OK" << std::endl; }},
      {"INFO", []() { std::cout << "OK" << std::endl; }},
      {"END", []() { std::cout << "OK" << std::endl; }},
      {"ABOUT",
       []() {
         std::cout << "name=\"Agin\", version=\"1.0\", author=\"beafowl\""
                   << std::endl;
       }},
      {"RESTART", []() { std::cout << "OK" << std::endl; }},
      {"TAKEBACK", []() { std::cout << "OK" << std::endl; }},
      {"PLAY", []() { std::cout << "OK" << std::endl; }},
      {"SET", []() { std::cout << "OK" << std::endl; }},
      {"UNDO", []() { std::cout << "OK" << std::endl; }},
  };
  if (commands.find(command) != commands.end()) {
    commands[command]();
  } else {
    std::cout << "ERROR" << std::endl;
  }
}
} // namespace pbrain