#ifndef _CONSOLE_H
#define _CONSOLE_H

#define VRAM_BASE 0xB8000
#define LINE_SIZE 80
#define LINE_BYTES (LINE_SIZE * 2)
#define NUM_LINES 25
#define CONSOLE_BYTES (NUM_LINES * LINE_BYTES)

struct _ConsoleBuffer
{
    unsigned int currentLine;
    unsigned int currentChar;
    char buffer[NUM_LINES][LINE_SIZE * 2];
};
typedef struct _ConsoleBuffer ConsoleBuffer;

void writeBufferToScreen(ConsoleBuffer *b);
void clearLineOfBuffer(ConsoleBuffer *b, int line);
void clearBuffer(ConsoleBuffer *b);
void scrollBuffer(ConsoleBuffer *b);
void printNewlineToBuffer(ConsoleBuffer *b);
void printCharToBuffer(ConsoleBuffer *b, char c);
void printStringToBuffer(ConsoleBuffer *b, const char *str);

#endif
