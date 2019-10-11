
#include <main.h>
#include <string.h>
#include <ili9163.h>
#include <framebuffer.h>



void ili9163Command(uint8_t cmd) {
	GPIO_WriteBit(GPIOA, ili9163_CS, Bit_RESET);
  	GPIO_WriteBit(GPIOA, ili9163_A0, Bit_RESET);
	spiWrite(&cmd, 1);
	GPIO_WriteBit(GPIOA, ili9163_CS, Bit_SET);
}

void ili9163DataN(uint8_t *data, uint16_t len) {
	GPIO_WriteBit(GPIOA, ili9163_CS, Bit_RESET);
  	GPIO_WriteBit(GPIOA, ili9163_A0, Bit_SET);
	spiWrite(data, len);
	GPIO_WriteBit(GPIOA, ili9163_CS, Bit_SET);
}

void ili9163Data(uint8_t cmd) {
	GPIO_WriteBit(GPIOA, ili9163_CS, Bit_RESET);
  	GPIO_WriteBit(GPIOA, ili9163_A0, Bit_SET);
	spiWrite(&cmd, 1);
	GPIO_WriteBit(GPIOA, ili9163_CS, Bit_SET);
}


void ili9163RamAddress(void)  {
    ili9163Command(SET_COLUMN_ADDRESS);
    ili9163Data(0x00);
    ili9163Data(0x00);
    ili9163Data(0x00);
    ili9163Data(0x7f);
    ili9163Command(SET_PAGE_ADDRESS);
    ili9163Data(0x00);
    ili9163Data(0x00);
    ili9163Data(0x00);
    ili9163Data(0x7f);
}

void ili9163FillColor(uint16_t color)  {
	uint16_t i = 0;
	uint16_t j = 0;
	ili9163RamAddress();
	ili9163Command(WRITE_MEMORY_START);
	for (i = 0; i < 128; i++)  {
		for (j = 0; j < 128; j++)  {
			ili9163Data((uint8_t)(color >> 8));
			ili9163Data((uint8_t)(color & 0x00ff));
		}
	}
}

void ili9163Update(void) {
	uint16_t i = 0;
	uint16_t b = 0;
	ili9163RamAddress();
	ili9163Command(WRITE_MEMORY_START);
	for (i = 0; i < DISPLAY_WIDTH / 8 * DISPLAY_HEIGHT; i++)  {
		for (b = 0; b < 8; b++)  {
			if (fb1Bit[i] & (1<<b)) {
				ili9163Data(255);
				ili9163Data(255);
			} else {
				uint8_t c = i / DISPLAY_WIDTH;
				ili9163Data(0);
				ili9163Data(c);
			}
		}
	}
}

uint8_t ili9163Initseq[] = {
	SET_PIXEL_FORMAT, 1, 0x05,
	SET_GAMMA_CURVE, 1, 0x04,
	GAM_R_SEL, 1, 0x01,
	POSITIVE_GAMMA_CORRECT, 15, 0x3f, 0x25, 0x1c, 0x1e, 0x20, 0x12, 0x2a, 0x90, 0x24, 0x11, 0x00, 0x00, 0x00, 0x00, 0x00, 
	NEGATIVE_GAMMA_CORRECT, 15, 0x20, 0x20, 0x20, 0x20, 0x05, 0x00, 0x15, 0xa7, 0x3d, 0x18, 0x25, 0x2a, 0x2b, 0x2b, 0x3a,
    FRAME_RATE_CONTROL1, 2, 0x11, 0x14, 
	DISPLAY_INVERSION, 1, 0x07, 
	POWER_CONTROL1, 2, 0x0a, 0x02, 
	POWER_CONTROL2, 1, 0x02, 
	VCOM_CONTROL1, 2, 0x50, 0x5b, 
	VCOM_OFFSET_CONTROL, 1, 0x40, 
	SET_COLUMN_ADDRESS, 4, 0x00, 0x00, 0x00, 0x7f, 
	SET_PAGE_ADDRESS, 4, 0x00, 0x00, 0x00, 0x7f, 
	SET_ADDRESS_MODE, 1, LCD_ORIENTATION1,
	SET_DISPLAY_ON, 0, 
	WRITE_MEMORY_START, 0
};

void ili9163Init(void) {
	GPIO_InitTypeDef GPIO_InitStructure;

#ifdef RCC_AHB1Periph_GPIOA
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
#else
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
#endif

	delay(500000);

#ifdef ili9163_RST
	// HW-Reset
	GPIO_WriteBit(GPIOA, ili9163_RST, Bit_RESET);
	delay(5000);
	GPIO_WriteBit(GPIOA, ili9163_RST, Bit_SET);
	delay(5000);
#endif

	ili9163Command(EXIT_SLEEP_MODE);
	delay(5000);

	// init sequence
	uint16_t n = 0;
	uint16_t i = 0;
	for (n = 0; n < sizeof(ili9163Initseq); n++) {
		ili9163Command(ili9163Initseq[n]);
		n++;
		for (i = 0; i < ili9163Initseq[n]; i++) {
			ili9163Data(ili9163Initseq[n + 1 + i]);
		}
		n += i;
	}





	ili9163FillColor(Red);



}


