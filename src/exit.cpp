#include <termios.h>
#include <unistd.h>
#include <cstdlib>
#include <Shellmax/exit.h>

void exit_shell(const termios& original_settings, int code) {
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &original_settings);
    std::exit(code);
}
