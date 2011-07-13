#define VRAM_BASE 0xb8000
#define LINE_SIZE 80
#define LINE_BYTES (LINE_SIZE * 2)
#define LINE_NUMBER 25
#define CONSOLE_BYTES (LINE_NUMBER * LINE_BYTES)

static unsigned char *videoram = (unsigned char *)VRAM_BASE;

struct _ConsoleBuffer
{
    unsigned int currentLine;
    unsigned int currentChar;
    char buffer[LINE_NUMBER][LINE_SIZE * 2];
};
typedef struct _ConsoleBuffer ConsoleBuffer;

ConsoleBuffer stdio;

void* memcpy(void* dest, const void* src, int count) {
        char* dst8 = (char*)dest;
        char* src8 = (char*)src;

        while (count--) {
            *dst8 = *src8;
	    dst8++;
	    src8++;
        }
        return dest;
}

void writeBufferToScreen(ConsoleBuffer *b){
    memcpy(videoram, b->buffer, LINE_NUMBER * LINE_SIZE * 2);
}

void clearLineOfBuffer(ConsoleBuffer *b, int line){
    int j;
    for (j = 0; j < (LINE_SIZE * 2); j += 2){
	b->buffer[line][j] = 0;
	b->buffer[line][j+1] = 0x80;
    }    
}

void clearBuffer(ConsoleBuffer *b){
    b->currentLine = b->currentChar = 0;
    int i;
    for (i = 0; i < LINE_NUMBER; i++){
	clearLineOfBuffer(b, i);
    }
    writeBufferToScreen(b);
}

void scrollBuffer(ConsoleBuffer *b){
    //pretty sure this requires internal knowledge
    //of memcpy this function isn't supposed to have,
    //but we can't even allocate memory, so what else?
    b->currentLine--;
    memcpy(b->buffer, &b->buffer[1][0], CONSOLE_BYTES - LINE_BYTES);
    clearLineOfBuffer(b, LINE_NUMBER - 1);
}

void printNewlineToBuffer(ConsoleBuffer *b){
    b->currentChar = 0;
    b->currentLine++;

    if(b->currentLine == LINE_NUMBER){
	scrollBuffer(b);
    }
}

void printCharToBuffer(ConsoleBuffer *b, char c){
    b->buffer[b->currentLine][b->currentChar * 2] = c;
    b->currentChar++;
    if(b->currentChar == LINE_SIZE){
	printNewlineToBuffer(b);
    }
}

void printStringToBuffer(ConsoleBuffer *b, char *str){
    int i;
    for (i = 0; str[i] != 0; i++){
	if (str[i] == '\n'){
	    printNewlineToBuffer(b);
	}else{
	    printCharToBuffer(b, str[i]);
	}
    }
}

void kmain( void* mbd, unsigned int magic )
{
   if ( magic != 0x2BADB002 )
   {
      /* Something went not according to specs. Print an error */
      /* message and halt, but do *not* rely on the multiboot */
      /* data structure. */
   }
 
   /* You could either use multiboot.h */
   /* (http://www.gnu.org/software/grub/manual/multiboot/multiboot.html#multiboot_002eh) */
   /* or do your offsets yourself. The following is merely an example. */ 
   char * boot_loader_name =(char*) ((long*)mbd)[16];

   ConsoleBuffer *io = &stdio;

   clearBuffer(io);
//   printNewlineToBuffer(io);
   printStringToBuffer(io, "The \n game\n+");
   printStringToBuffer(io, "And some more\n");
   printStringToBuffer(io, "The \n game\n+");
   printStringToBuffer(io, "And some more\n");
   scrollBuffer(io);
   
   /* int i = 0; */
   /* for(i = 0; i < LINE_SIZE * LINE_NUMBER; i++){ */
   /*     printCharToBuffer(io, '!'); */
   /* } */
   /* writeBufferToScreen(io); */

   //clearBuffer(io);
   writeBufferToScreen(io);
}
