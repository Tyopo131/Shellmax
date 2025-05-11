#include "Shellmax/buffer.h"
#include <string>

InputBuffer::operator std::string&() {
    return this->contents;
}
InputBuffer::operator const std::string&() const {
    return this->contents;
}
