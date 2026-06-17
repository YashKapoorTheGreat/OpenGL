#pragma once

#define W_PRESSED (0b00000001 << 0)
#define A_PRESSED (0b00000001 << 1)
#define S_PRESSED (0b00000001 << 2)
#define D_PRESSED (0b00000001 << 3)
#define Q_PRESSED (0b00000001 << 4)
#define E_PRESSED (0b00000001 << 5)
#define LEFT_MOUSE_PRESSED (0b00000001 << 6)
#define RIGHT_MOUSE_PRESSED (0b00000001 << 7)

extern unsigned char keyPressed;
extern int mouseX;
extern int mouseY;
