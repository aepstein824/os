global printCharacter
global moveCursor

printCharacter:
push EBP
mov ESP,EBP
mov AH,0Ah
mov AL,[EBP+8]
mov BH,0
mov CX,1
int 10h
pop EBP
ret

moveCursor:
push EBP
mov ESP,EBP
mov AH,2               ;Move Cursor
mov EAX,[EBP+8]
mov DH,AL         ;row.
mov EAX,[EBP+12]       ; col
mov DL,AL         ;column.
mov BH,0               ;page number.
int 10h
pop EBP
ret



