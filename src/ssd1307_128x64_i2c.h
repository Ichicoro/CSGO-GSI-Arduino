#include <Adafruit_SSD1306.h>

void drawOwO();
bool isNumber(String input);
void drawUI();
void drawHealthBar(int16_t color = WHITE);
void drawArmorBar(int16_t color = WHITE);
void drawAmmo(int16_t color = WHITE);
void drawBar(int16_t x, int16_t y, int16_t w, int16_t h, int16_t value, int16_t color);
void drawABar(int16_t x, int16_t y, int16_t w, int16_t h, int16_t value, int16_t color);
void drawCheckeredBar(int16_t x, int16_t y, int16_t w, int16_t h, int16_t value, int16_t color);
void fillCheckeredRect(int16_t x, int16_t y, int16_t w, int16_t h, int16_t color);
