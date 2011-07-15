#include "console.h"
#include "string.h"

ConsoleBuffer stdio;

void kmain(void *mbd, unsigned int magic)
{
   if ( magic != 0x2BADB002 )
   {
      /* Something went wrong! */
   }

   ConsoleBuffer *io = &stdio;

   clearBuffer(io);
   printStringToBuffer(io, "The \n game\n+");
   printStringToBuffer(io, "And some more\n");
   printStringToBuffer(io, "The \n game\n+");
   printStringToBuffer(io, "And some more\n");
   scrollBuffer(io);

   writeBufferToScreen(io);
}
