
#include <main.h>
#include <ssd1351.h>
#include <framebuffer.h>

#define ssd1351_RST GPIO_Pin_2
#define ssd1351_DC  GPIO_Pin_3
#define ssd1351_CS  GPIO_Pin_4


void ssd1351Command(uint8_t cmd) {
	GPIO_WriteBit(GPIOA, ssd1351_CS, Bit_RESET);
  	GPIO_WriteBit(GPIOA, ssd1351_DC, Bit_RESET);
	spiWrite(&cmd, 1);
	GPIO_WriteBit(GPIOA, ssd1351_CS, Bit_SET);
}

void ssd1351DataN(uint8_t *data, uint16_t len) {
	GPIO_WriteBit(GPIOA, ssd1351_CS, Bit_RESET);
  	GPIO_WriteBit(GPIOA, ssd1351_DC, Bit_SET);
	spiWrite(data, len);
	GPIO_WriteBit(GPIOA, ssd1351_CS, Bit_SET);
}

void ssd1351Data(uint8_t cmd) {
	GPIO_WriteBit(GPIOA, ssd1351_CS, Bit_RESET);
  	GPIO_WriteBit(GPIOA, ssd1351_DC, Bit_SET);
	spiWrite(&cmd, 1);
	GPIO_WriteBit(GPIOA, ssd1351_CS, Bit_SET);
}


void ssd1351RamAddress(void)  {
	ssd1351Command(0x15);
	ssd1351Data(0x00);
	ssd1351Data(0x7f);
	ssd1351Command(0x75);
	ssd1351Data(0x00);
	ssd1351Data(0x7f);
}

void ssd1351FillColor(uint16_t color)  {
	uint16_t i = 0;
	uint16_t j = 0;
	ssd1351RamAddress();
	ssd1351Command(0x5C);
	for (i = 0; i < 128; i++)  {
		for (j = 0; j < 128; j++)  {
			ssd1351Data((uint8_t)(color >> 8));
			ssd1351Data((uint8_t)(color & 0x00ff));
		}
	}
}

void ssd1351Update(void)  {
	uint16_t i = 0;
	uint16_t b = 0;
	ssd1351RamAddress();
	ssd1351Command(0x5C);
	for (i = 0; i < DISPLAY_WIDTH / 8 * DISPLAY_HEIGHT; i++)  {
		for (b = 0; b < 8; b++)  {
			if (fb1Bit[i] & (1<<b)) {
				ssd1351Data(255);
				ssd1351Data(255);
			} else {
				ssd1351Data(0);
				ssd1351Data(0);
			}
		}
	}
}

uint8_t ssd1351Initseq[] = {
	0xFD, 1, 0x12,				// command lock
	0xFD, 1, 0xB1,				// command lock
	0xAE, 0,					// display off
	0xA4, 0, 					// Normal display mode
	0x15, 2, 0x00, 0x7F, 		// set column address (00, 90)
	0x75, 2, 0x00, 0x7F, 		// set row address (00, 63)
	0x3B, 1, 0xF1,
	0xCA, 1, 0x7F,
	0xA0, 1, 0x74,				// set re-map & data format (Horizontal address increment)
	0xA1, 1, 0x00,				// set display start line (start 00 line)
	0xA2, 1, 0x00,				// set display offset
	0xAB, 1, 0x01,
	0xB4, 3, 0xA0, 0xB5, 0x55,
	0xC1, 3, 0xC8, 0x80, 0xC0,
	0xC7, 1, 0x0F,
	0xB1, 1, 0x32,
	0xB2, 3, 0xA4, 0x00, 0x00,
	0xBB, 1, 0x17,
	0xB6, 1, 0x01,
	0xBE, 1, 0x05,
	0xA6, 0,
	0xAF, 0						// display on
};

void ssd1351Init(void) {
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	delay(500000);

	// HW-Reset
	GPIO_WriteBit(GPIOA, ssd1351_RST, Bit_RESET);
	delay(50000);
	GPIO_WriteBit(GPIOA, ssd1351_RST, Bit_SET);
	delay(50000);

	// init sequence
	uint16_t n = 0;
	uint16_t i = 0;
	for (n = 0; n < sizeof(ssd1351Initseq); n++) {
		ssd1351Command(ssd1351Initseq[n]);
		n++;
		for (i = 0; i < ssd1351Initseq[n]; i++) {
			ssd1351Data(ssd1351Initseq[n + 1 + i]);
		}
		n += i;
	}


}


