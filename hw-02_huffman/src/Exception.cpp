#include "Exception.hpp"


const char* FileOpenException::what() const noexcept {
        return "Failed to open file";
    }

const char* IntegerOverflow::what() const noexcept {
        return "Code for this file is too big for integer";
    }

const char* WrongAmountOFArguments::what() const noexcept {
        return "Wrong amount of arguments";
    }

const char* WrongArgument::what() const noexcept {
        return "Wrong argument";
    }