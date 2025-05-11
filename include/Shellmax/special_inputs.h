enum class SpecialInput {
    NORMAL,
    SIGINT_PROGRAM, SEND_EOF,
    START_ESC_SEQUENCE,
    CLEAR_CURRENT_LINE,
    DELETE_WORD,
    CLEAR_SCREEN,
    BACKSPACE,
    ENTER_COMMAND,
    MOVE_TO_LINE_BEGINNING,
    MOVE_TO_LINE_ENDING,
    DELETE_TO_END_OF_LINE
};
inline SpecialInput process_special_input(char input) {
    switch (input) {
    case 3: // Ctrl+C, Send SIGINT to program
        return SpecialInput::SIGINT_PROGRAM;
    case 4: // Ctrl+D, Send EOF to program
        return SpecialInput::SEND_EOF;
    case 21: // Ctrl+U, Clear current line
        return SpecialInput::CLEAR_CURRENT_LINE;
    case 23: // Ctrl+W, Delete current word
        return SpecialInput::DELETE_WORD;
    case 12:
        return SpecialInput::CLEAR_SCREEN;
    case 127:
    case 8:
        return SpecialInput::BACKSPACE;
    case 10:
    case 13:
        return SpecialInput::ENTER_COMMAND;
    case 1:
        return SpecialInput::MOVE_TO_LINE_BEGINNING;
    case 5:
        return SpecialInput::MOVE_TO_LINE_ENDING;
    case 11:
        return SpecialInput::DELETE_TO_END_OF_LINE;
    default:
        return SpecialInput::NORMAL;
    };


}
