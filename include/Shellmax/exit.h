#pragma once
#include <termios.h>

void exit_shell(const termios& original_settings, int code);
