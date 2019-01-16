
#include <main.h>
#include <stdio.h>
#include <systick.h>
#include <serial.h>
#include <i2c.h>


void ledOn(void) {
	GPIO_WriteBit(LED_PORT, LED_PIN, Bit_RESET);
}

void ledOff(void) {
	GPIO_WriteBit(LED_PORT, LED_PIN, Bit_SET);
}

void ledToggle(void) {
	if (GPIO_ReadOutputDataBit(LED_PORT, LED_PIN)) {
		GPIO_WriteBit(LED_PORT, LED_PIN, Bit_RESET);
	} else {
		GPIO_WriteBit(LED_PORT, LED_PIN, Bit_SET);
	}
}


void systemInit(void) {
	systickInit();
	serialInit();
	i2cInit();

	LED_CLK;
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = LED_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(LED_PORT, &GPIO_InitStructure);

}

#ifdef USE_FULL_ASSERT
void assert_failed(uint8_t* file, uint32_t line) {
	printf("Wrong parameters value: file %s on line %d\r\n", file, line);
	while (1);
}
#endif
