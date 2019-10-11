
#define fb_COLOR_FG 255
#define fb_COLOR_BG 0
#define fb_TEXT_WIDTH 8
#define fb_TEXT_HEIGHT 16
#define fb_TEXT_STEP 16
#define fb_TEXT_FONT fbFont8x16
#define DISPLAY_WIDTH  128
#define DISPLAY_HEIGHT 128

extern uint8_t fb1Bit[DISPLAY_WIDTH / 8 * DISPLAY_HEIGHT];

uint8_t fbCharWidth(char ch);
uint16_t fbTextWidth(char *text);
void fbTextPos(uint8_t x, uint8_t y);
void fbInit(void);

void fbClear(void);
void fbSetPixel(uint8_t x, uint8_t y, uint8_t color);
void fbChar(char ch, uint8_t color);
void fbText(char *text, uint8_t color);
void fbLine(uint8_t X1, uint8_t Y1, uint8_t X2, uint8_t Y2, uint8_t color);
void fbCircle(uint8_t x, uint8_t y, uint8_t radius, uint8_t filled, uint8_t color);
void fbRect(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, uint8_t filled, uint8_t color);

