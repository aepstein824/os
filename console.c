#include "console.h"
#include "string.h"

static unsigned char *videoram = (unsigned char *)VRAM_BASE;

void writeBufferToScreen(ConsoleBuffer *b) {
    memcpy(videoram, b->buffer, NUM_LINES * LINE_SIZE * 2);
}

void clearLineOfBuffer(ConsoleBuffer *b, int line) {
    int j;
    for (j = 0; j < (LINE_SIZE * 2); j += 2) {
        b->buffer[line][j] = 0;
        b->buffer[line][j+1] = 0x80;
    }    
}

void clearBuffer(ConsoleBuffer *b) {
    b->currentLine = b->currentChar = 0;
    int i;
    for (i = 0; i < NUM_LINES; i++)
        clearLineOfBuffer(b, i);
    writeBufferToScreen(b);
}

void scrollBuffer(ConsoleBuffer *b) {
    //pretty sure this requires internal knowledge
    //of memcpy this function isn't supposed to have,
    //but we can't even allocate memory, so what else?
    b->currentLine--;
    memcpy(b->buffer, &b->buffer[1][0], CONSOLE_BYTES - LINE_BYTES);
    clearLineOfBuffer(b, NUM_LINES - 1);
}

void printNewlineToBuffer(ConsoleBuffer *b) {
    b->currentChar = 0;
    b->currentLine++;

    if (b->currentLine == NUM_LINES)
        scrollBuffer(b);
}

void printCharToBuffer(ConsoleBuffer *b, char c) {
    b->buffer[b->currentLine][b->currentChar * 2] = c;
    b->currentChar++;
    if (b->currentChar == LINE_SIZE)
        printNewlineToBuffer(b);
}

void printStringToBuffer(ConsoleBuffer *b, const char *str) {
    int i;
    for (i = 0; str[i] != 0; i++){
        if (str[i] == '\n')
            printNewlineToBuffer(b);
        else
            printCharToBuffer(b, str[i]);
    }
}
