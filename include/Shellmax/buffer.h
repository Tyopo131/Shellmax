#pragma once
#include <string>
#include <cstddef>

class InputBuffer {
public:
    std::string contents;
    std::size_t pos;
    InputBuffer() : pos(0), contents("") {}
    InputBuffer(std::string contents, std::size_t cursor_pos) : contents(contents), pos(cursor_pos) {}
    operator std::string&();
    operator const std::string&() const;
};
