/*
** EPITECH PROJECT, 2023
** AGIN
** File description:
** Error
*/

#ifndef ERROR_HPP_
#define ERROR_HPP_

#include <exception>
#include <string>
#include <utility>

namespace pbrain {
    class Error : public std::exception
    {
        public:
            Error(const Error &other) = delete;

            Error &operator=(const Error &other) = delete;

            Error(Error &&other) noexcept = delete;

            Error &operator=(Error &&other) noexcept = delete;

            explicit Error(std::string message)
                : _message(std::move(message))
            {}

            ~Error() override = default;

            [[nodiscard]] const char *what() const noexcept override
            {
                return _message.c_str();
            }

        private:
            std::string _message;
    };
} // namespace pbrain

#endif /* !ERROR_HPP_ */
