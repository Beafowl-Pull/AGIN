/*
** EPITECH PROJECT, 2023
** AGIN
** File description:
** Main
*/

#pragma once

#include <iostream>
#include <vector>

namespace Main {
    class MainClass
    {
        public:
            MainClass() = default;
            ~MainClass() = default;

            int operator()();

        protected:
        private:
            int runApp();
    };
} // namespace Main
