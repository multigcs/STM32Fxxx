
#include <stm32f4xx_conf.h>
#include <systick.h>
#include <serial.h>
#include <i2c.h>
#include <spi.h>
#include <usb.h>

#define LED_CLK		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE)
#define LED_PORT	GPIOD
#define LED_PIN		GPIO_Pin_2

#define I2C_SPEED 50000
#define SSD1306ADDR 0x3C


void systemInit(void);
void ledOn(void);
void ledOff(void);
void ledToggle(void);
