#include <exception>

#ifndef MYEXCEPT
#define MYEXCEPT

class Exception : public std::exception {};

class FileOpenException : public Exception {
    public:
    const char* what() const noexcept override;
};
class IntegerOverflow : public Exception {
    public:
    const char* what() const noexcept override;
};

class WrongAmountOFArguments : public Exception {
    public:
    const char* what() const noexcept override;
};

class WrongArgument : public Exception {
    public:
    const char* what() const noexcept override;
};
#endif