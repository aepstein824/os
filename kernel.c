#include "console.h"
#include "string.h"
#include "cursor.h"

void kmain(void *mbd, unsigned int magic)
{
    if ( magic != 0x2BADB002 )
    {
       /* Something went wrong! */
    }

    print("\r\n\r\nTesting the BIOS method...");
}
