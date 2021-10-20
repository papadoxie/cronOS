#include <kstdio.h>
#include <tty.h>

// void printk(const char *__str)
// {
//     // Cast buffer address to pointer for easier use
//     uint16_t *vidmem = (uint16_t *)VIDEO_MEMORY;
//     static char screen_buffer[(SCREEN_WIDTH * SCREEN_HEIGHT) + SCREEN_WIDTH];

//     // Cursor position
//     static uint8_t x = 0;
//     static uint8_t y = 0;

//     for (uint16_t i = 0; __str[i] != '\0'; i++)
//     {
//         if (__str[i] == '\n' || x == SCREEN_WIDTH)
//         {
//             x = 0;
//             y++;
//         }

//         if (y == SCREEN_HEIGHT)
//         {
//             y--;
//             shift_screen_buffer_up(screen_buffer);
//         }

//         screen_buffer[(SCREEN_WIDTH * y) + x] = __str[i];
//         x++;
//     }

//     // Move cursor to new line after printing
//     x = 0;
//     y++;

//     // Copy screen buffer to video memory
//     for (uint16_t i = 0; i < ((SCREEN_WIDTH * SCREEN_HEIGHT) + SCREEN_WIDTH); i++)
//     {
//         vidmem[i] = (vidmem[i] & 0xFF00) | screen_buffer[i];
//     }
// }