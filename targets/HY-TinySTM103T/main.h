
#include <stm32f10x_conf.h>
#include <systick.h>
#include <serial.h>
#include <i2c.h>


#define LED_CLK		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE)
#define LED_PORT	GPIOA
#define LED_PIN		GPIO_Pin_1

#define I2C_SPEED 50000
#define SSD1306ADDR 0x3C


void systemInit(void);
void ledOn(void);
void ledOff(void);
void ledToggle(void);
