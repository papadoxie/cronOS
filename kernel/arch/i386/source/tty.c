#include <tty.h>
#include <kstring.h>

static const size_t SCREEN_WIDTH = 80;
static const size_t SCREEN_HEIGHT = 25;
static uint16_t *const VIDEO_MEMORY = (uint16_t *)0xB8000;

static size_t row;
static size_t column;
static uint8_t tty_color;
static uint16_t *buffer;

void tty_init(void)
{
    row = 0;
    column = 0;
    tty_color = tty_entry_color(VGA_COLOR_LIGHT_GREEN, VGA_COLOR_BLACK);
    buffer = VIDEO_MEMORY;

    for (size_t y = 0; y < SCREEN_HEIGHT; y++)
    {
        for (size_t x = 0; x < SCREEN_WIDTH; x++)
        {
            const size_t index = y * SCREEN_WIDTH + x;
            buffer[index] = tty_entry(' ', tty_color);
        }
    }
}

void tty_setcolor(uint8_t color)
{
    tty_color = color;
}

// Shift the screen buffer up by one line
void shift_buffer_up(char *__buffer)
{
    for (uint16_t i = 0; i < SCREEN_HEIGHT; i++)
    {
        for (uint16_t j = 0; j < SCREEN_WIDTH; j++)
        {
            buffer[(SCREEN_WIDTH * i) + j] = __buffer[(SCREEN_WIDTH * (i + 1)) + j];
        }
    }
}

void tty_putchar_at(unsigned char uchar, uint8_t color, size_t x, size_t y)
{
    const size_t index = (y * SCREEN_WIDTH) + x;
    buffer[index] = tty_entry(uchar, color);
}

void tty_putchar(char __c)
{
    unsigned char uchar = __c;
    tty_putchar_at(uchar, tty_color, column, row);
    if(++column ==  SCREEN_WIDTH)
    {
        column = 0;
        if(++row == SCREEN_HEIGHT)
        {
            row--;
            shift_buffer_up(buffer);
        }
    }
}

void tty_write(const char *__str, size_t __size)
{
    for (size_t i = 0; i < __size; i++)
    {
        tty_putchar(__str[i]);
    }
}

void tty_writestr(const char *__str)
{
    tty_write(__str, strlen(__str));
}