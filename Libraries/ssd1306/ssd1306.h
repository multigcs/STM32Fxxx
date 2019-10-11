

void ssd1306GotoXY(uint8_t x, uint8_t y);
void ssd1306Home(void);
void ssd1306Clear(void);
void ssd1306Command(const uint8_t cmd);
void ssd1306Init(void);
void ssd1306Putc(char c);
void ssd1306PutcBig(char c, uint8_t mode);
void ssd1306Puts(const char* s);
void ssd1306PutsBig(const char* s);
void ssd1306Draw(uint16_t *data, uint8_t len, uint16_t offset, uint16_t scale, uint8_t dpos);


