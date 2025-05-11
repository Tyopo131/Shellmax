#include <nlohmann/json.hpp>
#include <iostream>
#include <termios.h>
#include "Shellmax/special_inputs.h"
#include "Shellmax/exit.h"
#include "Shellmax/buffer.h"

int main() {
    std::cout << "loading...\n";
    termios original_settings;
    tcgetattr(STDIN_FILENO, &original_settings); // Get current settings and store them
    termios raw_settings = original_settings;
    raw_settings.c_lflag &= ~(ECHO | ICANON | ISIG); // Settings for terminal raw mode
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw_settings); // Apply settings
    tcflush(STDIN_FILENO, TCIFLUSH);
    InputBuffer buffer;
    bool special_sequence_active = false;
    std::cout << "done.\n";
    while (true) {
        char inputted;
        read(STDIN_FILENO, &inputted, 1);
        SpecialInput special_input = process_special_input(inputted);
        // Escape sequence handling

        if (special_sequence_active) {
            switch (inputted) {
            case 'D': // Arrow left
                if (buffer.pos <= 0) {
                    break;
                    special_sequence_active = false;
                };
                std::cout << inputted << std::flush;
                buffer.pos -= 1;
                special_sequence_active = false;
                break;
            case 'C': // Arrow right
                if (buffer.pos <= 0) {
                    break;
                    special_sequence_active = false;
                };
                std::cout << inputted << std::flush;
                buffer.pos += 1;
                special_sequence_active = false;
                break;
            case '[':



                break;
            default: // Anything else
                std::cout << "Operation not supported.\n" << buffer.contents << std::flush;
                special_sequence_active = false;
            }
            continue;
        }
        // Detect special sequences (otherwise print and add to buffer normally)
        switch (special_input) {
        case SpecialInput::START_ESC_SEQUENCE: {
            special_sequence_active = true;
            break;
        }
        case SpecialInput::ENTER_COMMAND:
            std::cout << "btw here's what you typed: " << buffer.contents << "\n" << std::flush;
            buffer.contents.clear();
            buffer.pos = 0;
            break;
        case SpecialInput::NORMAL: {
            std::cout << inputted << std::flush;
            buffer.contents.insert(buffer.pos, 1 /* Insert one of `inputted` (the function needs this!) */, inputted);
            buffer.pos += 1;
        }
        break;
        case SpecialInput::BACKSPACE:
            if (buffer.pos <= 0) break;
            std::cout << "\b \b" << std::flush;
            buffer.contents.erase(buffer.pos - 1);
            buffer.pos -= 1;
            break;
        case SpecialInput::SEND_EOF:
            std::cout << "^D\n";
            std::cout << "Goodbye. AVADA KEDAVRA!" << std::flush;
            exit_shell(original_settings, 0);
            break;
        case SpecialInput::CLEAR_SCREEN:
            std::cout << "^L" << std::flush;
            std::cout << "\033c" << std::flush;
            break;
        case SpecialInput::SIGINT_PROGRAM:
            std::cout << "^C\n" << std::flush;
            buffer.contents.clear();
            buffer.pos = 0;
            break;
        default:
            std::cerr << "Unsupported Operation.\n";
            break;

        }
    }
}
