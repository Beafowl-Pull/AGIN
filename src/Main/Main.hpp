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

            MainClass(const MainClass &copy) = default;

            MainClass &operator=(const MainClass &other) = default;

            MainClass(MainClass &&) noexcept = default;

            MainClass &operator=(MainClass &&) noexcept = default;

            int operator()();

        protected:
        private:
            static int runApp();
    };
} // namespace Main
