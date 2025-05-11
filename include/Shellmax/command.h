#pragma once
#include <vector>
#include <string>
#include <filesystem>

class ParsedCommand {
private:
    std::vector<std::string> args;
    std::filesystem::path program;
public:
    std::filesystem::path getProgram();
    std::vector<std::string> getArgs();
};
