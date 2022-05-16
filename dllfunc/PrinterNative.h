#pragma once
#include <iostream>
namespace Native {
    class Printer {
    public:
        Printer() = default;
        auto print(std::string) -> void;
    };
};
