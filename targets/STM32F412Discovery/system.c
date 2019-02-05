
#include <main.h>
#include <stdio.h>
#include <systick.h>
#include <serial.h>
#include <i2c.h>
#include <usb.h>


void ledOn(void) {
	GPIO_WriteBit(LED_PORT, LED_PIN, Bit_RESET);
}

void ledOff(void) {
	GPIO_WriteBit(LED_PORT, LED_PIN, Bit_SET);
}

void ledToggle(void) {
	GPIO_ToggleBits(LED_PORT, LED_PIN);
}


void systemInit(void) {
	systickInit();
	serialInit();
//	i2cInit();
//	spiInit();
//	usbInit();

	LED_CLK;
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = LED_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(LED_PORT, &GPIO_InitStructure);

}

#ifdef USE_FULL_ASSERT
void assert_failed(uint8_t* file, uint32_t line) {
//	printf("Wrong parameters value: file %s on line %d\r\n", file, line);
	while (1);
}
#endif
